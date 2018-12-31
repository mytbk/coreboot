#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_sku.h"
#include "mrc_misc.h"
#include "mrc_utils.h"
#include <arch/io.h>
#include <arch/pci_ops.h>
#include <console/console.h>

int dummy_func(void)
{
	return 0;
}

void dmi_check_link(void)
{
	if (mrc_sku_type() == 1) {
		uint32_t lcap = RCBA32(0x21a4);
		uint32_t max_link_speed = lcap & 0xf;
		if (max_link_speed == 2) {
			RCBA8_AND_OR(0x21b0, 0xf0, 2);
		}
	}
}

void __attribute((regparm(2))) rtc_wait(void *ram_data, uint16_t val)
{
	uint16_t t1, t2;
	*(uint16_t*)(ram_data + 0xfee) = val;
	outw(val, 0x80);

	do {
		outb(0x48, 0x74);
		t1 = inb(0x75);
		outb(0x49, 0x74);
		t2 = inb(0x75);
		t2 = (t2 << 8) | t1;
	} while (t2 == val);
}

uint8_t __attribute((regparm(1))) pci_setup_bridge(uint8_t bus)
{
	uint8_t a = bus;
	uint8_t r = 0;
	for (int i = 0; i < 0x20; i++) {
		uint32_t dev = PCI_DEV(bus, i, 0);
		uint16_t vid = pci_read_config16(dev, 0);
		if (vid == 0xffff) continue;
		uint16_t cls = pci_read_config16(dev, 0xa);
		if (cls != 0x604) continue; // PCI_CLASS_BRIDGE_PCI
		/* primary bus number */
		pci_write_config8(dev, 0x18, bus);
		a++;
		/* secondary bus number */
		pci_write_config8(dev, 0x19, a);
		/* subordinate bus number */
		pci_write_config8(PCI_DEV(a, i, 0), 0x1a, 0xff);
		pci_write_config16(PCI_DEV(a, 0, 0), 0, 0);
		r = pci_setup_bridge(a);
		pci_write_config8(dev, 0x1a, r);
		a = r;
	}
	return (r == 0)?bus:r;
}

int fcn_fffbd29a(u32 a0, void * a1, void * a2);
int fcn_fffbd29a(u32 a0, void * a1, void * a2)
{
	u32 b1 = (*(u8*)(a1 + 5) >> 3) & 7;
	u32 *wb = (u32*)(a2 + 0xd5);

	switch (b1) {
		case 0:
			*wb = 0x1000;
			return 1;
		case 1:
			*wb = 0x2000;
			return 1;
		case 2:
			*wb = 0x4000;
			return 1;
		case 3:
			*wb = 0x8000;
			return 1;
		case 4:
			*wb = 0x10000;
			return 1;
		default:
			*wb = 0;
			return 0;
	}
}

int fcn_fffaa884(void *ram_data);
int fcn_fffaa884(void *ram_data)
{
	void *bar = *(void**)(ram_data + 0x103b);

	/* this function is not called!!! */
	printk(BIOS_DEBUG, "fcn_fffaa884: bar is %p.\n", bar);

	u32 reg_e4 = read32(bar + 0xe4);
	u32 reg_e8 = read32(bar + 0xe8);
	if (reg_e8 != *(u32*)(ram_data + 0xc))
		return 0x17;

	if (reg_e4 != *(u32*)(ram_data + 8))
		return 0x17;

	void *base = ram_data + 8;
	u16 tmp;

	for (int i = 0; i < 2; i++) {
		int i1 = i * 0x2e6;
		int i2 = i * 0x2fa;
		for (int j = 0; j < 2; j++) {
			void * local_2ch = base + j * 0xfb + i1 + 0xa80 + 0x13;
			int idx2 = j * 0x14f + i2;
			if (*(u32*)((ram_data + idx2 + 0x10c4)) == 1) {
				tmp = 0;
			} else {
				crc16(ram_data + idx2 + 0x115d, 0xb, &tmp);
			}
			if (tmp != *(u16*)(local_2ch + 0xdb))
				return 0x17;
		}
	}
	*(u8*)(ram_data + 0x1742) = 1;
	return 0;
}

int fcn_fffa782c(void *ram_data);
int fcn_fffa782c(void *ram_data)
{
	u32 reg;
	u16 v1, v2;
	u8 wb;

	*(u8*)(ram_data + 0x173f) = 0;
	*(u8*)(ram_data + 0x1740) = *(u8*)(ram_data + 0x102b);
	*(u8*)(ram_data + 0x173c) = *(u8*)(ram_data + 0x16b0);

	void *p1 = *(void**)(ram_data + 0x1047);

	/* p1 is fed84000 (GDXC_BASE_ADDRESS)
	printk(BIOS_DEBUG, "fcn_fffa782c: p1 is %p.\n", p1);
	*/

	reg = read32(p1 + 0x18);
	v1 = reg;
	v2 = reg >> 16;
	if (v1 == 0 && v2 > 1) {
		wb = v2;
	} else {
		wb = *(u8*)(ram_data + 0x16b2);
	}
	*(u8*)(ram_data + 0x173e) = wb;

	reg = read32(p1 + 0x28);
	v1 = reg;
	v2 = reg >> 16;
	if (v1 == 0 && v2 > 1) {
		wb = v2;
	} else {
		wb = *(u8*)(ram_data+ 0x16b1);
	}
	*(u8*)(ram_data + 0x173d) = wb;

	return 0;
}

void __attribute((regparm(2))) fcn_fffb2d76(void *, int);
void __attribute((regparm(3))) fcn_fffb1d24(void *, u32, u32, u32, u32);
void __attribute((regparm(2))) fcn_fffb2062(void *, u8*);

static const u32 gdata1[9] = {
	0x86186186,
	0x18618618,
	0x30c30c30,
	0xa28a28a2,
	0x8a28a28a,
	0x14514514,
	0x28a28a28,
	0x92492492,
	0x24924924
};
static const uint8_t gdata2[12] = {
	0xa1, 0x0c, 0xa1, 0x00, 0x08, 0x0d, 0xef, 0x00, 0x1e, 0x0a, 0xad, 0x00
};

int fcn_fffb8c0b(void *ram_data);
int fcn_fffb8c0b(void *ram_data)
{
	u32 data1[9]; // ebp - 0x3c
	u8 data2[12]; // ebp - 0x48

	/* fcn_fffb8c0b : bar is fed10000. (MCHBAR)
	   printk(BIOS_DEBUG, "%s : bar is %p.\n", __func__, *((void**) (ram_data + 0x103f)));
	   */

	if (*((int32_t*) (ram_data + 0x297c)) == 2 &&
			*((int8_t*) (ram_data + 0x1740)) == 1) {
		void *bar = *((void**) (ram_data + 0x103f));
		bar_update32(bar, 0x5004, 0xfcffffff, 0x1000000);
		fcn_fffb2d76 (ram_data, 0x3c);
	}
	if (*((int32_t*) (ram_data + 0x3cc3)) == 2 &&
			*((int8_t*) (ram_data + 0x1740)) == 1) {
		void *bar = *((void**) (ram_data + 0x103f));
		bar_update32(bar, 0x5008, 0xfcffffff, 0x1000000);
		fcn_fffb2d76 (ram_data, 0x3c);
	}
	memcpy(data1, gdata1, 36);
	memcpy(data2, gdata2, 12);

	fcn_fffb1d24 (ram_data, 0, 0x1010101, 8, 0);
	for (int i = 0; i < 9; i++) {
		fcn_fffb1d24 (ram_data, data1[i], 0x41041041, 6, 8 + i * 6);
	}
	fcn_fffb2062 (ram_data, data2);
	if (*((int32_t*) (ram_data + 0x297c)) == 2) {
		void *bar = *((void**) (ram_data + 0x103f));
		write32(bar + 0x4078, 0xa010102);
	}
	if (*((int32_t*) (ram_data + 0x3cc3)) == 2) {
		void *bar = *((void**) (ram_data + 0x103f));
		write32(bar + 0x4478, 0xa010102);
	}
	return 0;
}

static inline u32
movebits(u32 dst, u32 src, u8 nbits, u8 shift)
{
	u32 v0 = src & ((1 << nbits) - 1);
	v0 <<= shift;
	dst &= ~(((1 << nbits) - 1) << shift);
	dst |= v0;
	return dst;
}

int __attribute((regparm(2))) fcn_fffc6438(void *eax, int vv);
int __attribute((regparm(2))) fcn_fffc6438(void *eax, int vv)
{
#define V(x) (*(u8*)(eax + (x)))

	vv -= 0xd;
	u32 edi = *(u32*)(eax + 0x1749);
	void *mchbar = *(void**)(eax + 0x103f);
	u32 edx, esi, ebx, ecx;
	u16 tmp16;
	u32 t32;

	switch (vv) {
		case 0:
			if (edi == 2)
				return 0;
			return (~V(0x16b4)) & 1;
		case 1:
			return (edi == 2)? 1:0;
		case 2:
			return ((V(0x16b4) >> 1) ^ 1) & 1;
		case 3:
			return ((V(0x16b4) >> 2) ^ 1) & 1;
		case 4:
			return ((V(0x16b4) >> 3) ^ 1) & 1;
		case 5:
			return ((V(0x16b4) >> 4) ^ 1) & 1;
		case 6:
			return ((V(0x16b4) >> 5) ^ 1) & 1;
		case 7:
			return ((V(0x16b4) >> 6) ^ 1) & 1;
		case 8:
			return ((V(0x16b4) >> 7) ^ 1) & 1;
		case 9:
			return ((V(0x16b7) >> 5) ^ 1) & 1;
		case 10:
			return (~V(0x16b5)) & 1;
		case 11:
			return ((V(0x16b7) >> 3) ^ 1) & 1;
		case 12:
			return ((V(0x16b5) >> 1) ^ 1) & 1;
		case 13:
			return ((V(0x16b7) >> 4) ^ 1) & 1;
		case 14:
			return ((V(0x16b5) >> 2) ^ 1) & 1;
		case 15:
			return ((V(0x16b5) >> 4) ^ 1) & 1;
		case 16:
			return ((V(0x16b5) >> 5) ^ 1) & 1;
		case 17:
			return ((V(0x16b5) >> 6) ^ 1) & 1;
		case 20:
			return ((V(0x16b5) >> 7) ^ 1) & 1;
		case 21:
			return (~V(0x16b6)) & 1;
		case 22:
			return ((V(0x16b6) >> 1) ^ 1) & 1;
		case 23:
			return ((V(0x16b6) >> 2) ^ 1) & 1;
		case 24:
			return ((V(0x16b6) >> 3) ^ 1) & 1;
		case 25:
			return ((V(0x16b6) >> 6) ^ 1) & 1;
		case 26:
			return ((V(0x16b6) >> 7) ^ 1) & 1;
		case 27:
			if ((V(0x16b7) & 1) == 0) {
				return 1;
			} else {
				if (edi == 2)
					return 1;
				else
					return 0;
			}
		case 28:
			if ((V(0x16b5) & 8) == 0) {
				return 1;
			} else {
				if (edi != 2)
					return 1;
				else
					return 0;
			}
		case 30:
			return ((V(0x16b7) >> 1) ^ 1) & 1;
		case 31:
			return ((V(0x16b7) >> 2) ^ 1) & 1;
		case 35:
			return ((V(0x16b7) >> 6) ^ 1) & 1;
		case 37:
			return (edi == 2)? 1:0;
		case 44:
			if (V(0x107d) != 0) {
				write32(mchbar + 0x5884, ((u32)V(0x107e)) & 7);
				tmp16 = V(0x1080);
				tmp16 = (tmp16 << 8) | (V(0x107f));
				write32(mchbar + 0x5888, tmp16);
			}
			// loc_fffc6622:
			edx = (u32)(V(0x1087) & 3) << 0x16;
			esi = (u32)(V(0x1088) & 0x1f) << 0x11;
			esi |= edx;
			edx = (u32)(V(0x1089) & 1) << 0xf;
			edx |= esi;
			esi = (u32)(*(u16*)(eax + 0x108a)) & 0x7fff;
			ecx = edx;
			edx = (u32)V(0x1081) << 0x1f;
			ecx |= esi;
			ebx = edx;
			ebx = movebits(ebx, V(0x1082), 2, 0x16);
			ebx = movebits(ebx, V(0x1083), 5, 0x11);
			ebx = movebits(ebx, V(0x1084), 1, 15);
			ebx = movebits(ebx, *(u16*)(eax + 0x1085), 15, 0);
			write32(mchbar + 0x58e0, ecx);
			write32(mchbar + 0x58e4, ebx);
			tmp16 = V(0x108d);
			tmp16 = (tmp16 << 8) | V(0x108c);
			write32(mchbar + 0x5890, tmp16);
			tmp16 = V(0x108f);
			tmp16 = (tmp16 << 8) | V(0x108e);
			write32(mchbar + 0x5894, tmp16);
			tmp16 = V(0x1091);
			tmp16 = (tmp16 << 8) | V(0x1090);
			write32(mchbar + 0x5898, tmp16);
			tmp16 = V(0x1093);
			tmp16 = (tmp16 << 8) | V(0x1092);
			write32(mchbar + 0x589c, tmp16);
			tmp16 = V(0x1095);
			tmp16 = (tmp16 << 8) | V(0x1094);
			write32(mchbar + 0x58d0, tmp16);
			tmp16 = V(0x1097);
			tmp16 = (tmp16 << 8) | V(0x1096);
			write32(mchbar + 0x58d4, tmp16);
			tmp16 = V(0x1099);
			tmp16 = (tmp16 << 8) | V(0x1098);
			write32(mchbar + 0x58d8, tmp16);
			tmp16 = V(0x109b);
			tmp16 = (tmp16 << 8) | V(0x109a);
			write32(mchbar + 0x58dc, tmp16);

			for (int i = 0; i < 2; i++) {
				void *ptr1 = eax + 0x16be + 0x1347 * i;
				u8 *ptr2= eax + 0x109d + 2 * i;
				u32 offs = 0x4328 + 0x400 * i;

				if (*(u32*)(ptr1 + 0x12be) != 2)
					continue;

				if (V(0x107d) != 0) {
					write32(mchbar + (offs - 0x3c),
							((u16)(ptr2[0] & 0x3f) << 8) | (ptr2[-1] & 0x3f));

					write32(mchbar + (offs - 0x38),
							((u16)(ptr2[4] & 0x3f) << 8) | (ptr2[3] & 0x3f));

					write32(mchbar + (offs - 0x34),
							((u16)ptr2[8] << 8) | ptr2[7]);

					write32(mchbar + (offs - 0x30),
							((u16)ptr2[12] << 8) | ptr2[11]);

					write32(mchbar + (offs - 0x2c),
							((u16)ptr2[16] << 8) | ptr2[15]);
				}
				if (edi == 2) {
					t32 = V(0x10b5) & 1;
					t32 <<= 8;
					t32 |= V(0x10b6);
				} else {
					t32 = V(0x10b3) & 1;
					t32 <<= 8;
					t32 |= V(0x10b4);
				}
				write32(mchbar + offs, t32);
			}

			t32 = V(0x10b0) & 1;
			t32 = (t32 << 16) | (*(u16*)(eax + 0x10b1));
			write32(mchbar + 0x5060, t32);

			t32 = read32(mchbar + 0x5880);
			t32 &= 0xfffffffc;
			t32 = t32 | ((V(0x1076) & 1) << 1) | (V(0x1077) & 1);
			t32 &= 0xffffffe3;
			t32 = t32 | ((V(0x1075) & 1) << 4) | ((V(0x107a) & 3) << 2);

			if (edi == 2) {
				t32 &= 0xffffffbf;
				t32 |= ((V(0x1079) & 1) << 6);
				if (V(0x1070) != 0) {
					write32(mchbar + 0x5880, t32);
					return 0;
				}
				t32 &= 0xffffff7f;
				t32 |= (((V(0x107b) == 0)?1:0) << 7);
			} else {
				t32 &= 0xffffffbf;
				t32 |= ((V(0x1078) & 1) << 6);
			}
			write32(mchbar + 0x5880, t32);
			return 0;

		case 46:
			return ((V(0x16b6) >> 4) ^ 1) & 1;

		default:
			return 0;
	}
}
