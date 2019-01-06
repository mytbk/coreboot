#include <southbridge/intel/lynxpoint/pch.h>
#include <device/pci_ops.h>
#include <cpu/intel/haswell/haswell.h>
#include "mrc_sku.h"
#include "mrc_misc.h"
#include "mrc_utils.h"
#include <arch/io.h>
#include <arch/pci_ops.h>
#include <console/console.h>
#include "mrc_pei.h"
#include "pei_ram.h"

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

/* this function is called multiple times */
int __attribute((regparm(2))) fcn_fffc6438(void *ram_data, int vv);
int __attribute((regparm(2))) fcn_fffc6438(void *ram_data, int vv)
{
#define V(x) (*(u8*)(ram_data + (x)))

	vv -= 0xd;
	u32 edi = *(u32*)(ram_data + 0x1749);
	void *mchbar = *(void**)(ram_data + 0x103f);
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
			esi = (u32)(*(u16*)(ram_data + 0x108a)) & 0x7fff;
			ecx = edx;
			edx = (u32)V(0x1081) << 0x1f;
			ecx |= esi;
			ebx = edx;
			ebx = movebits(ebx, V(0x1082), 2, 0x16);
			ebx = movebits(ebx, V(0x1083), 5, 0x11);
			ebx = movebits(ebx, V(0x1084), 1, 15);
			ebx = movebits(ebx, *(u16*)(ram_data + 0x1085), 15, 0);
			write32(mchbar + 0x58e0, ecx);
			write32(mchbar + 0x58e4, ebx);

			for (int i = 0; i < 4; i++) {
				tmp16 = V(0x108d + i * 2);
				tmp16 = (tmp16 << 8) | V(0x108c + i * 2);
				write32(mchbar + 0x5890 + i * 4, tmp16);
			}
			for (int i = 0; i < 4; i++) {
				tmp16 = V(0x1095 + i * 2);
				tmp16 = (tmp16 << 8) | V(0x1094 + i * 2);
				write32(mchbar + 0x58d0 + i * 4, tmp16);
			}

			for (int i = 0; i < 2; i++) {
				void *ptr1 = ram_data + 0x16be + 0x1347 * i;
				u8 *ptr2= ram_data + 0x109d + 2 * i;
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
			t32 = (t32 << 16) | (*(u16*)(ram_data + 0x10b1));
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

void __attribute((regparm(3))) fcn_fffc8290(void *, void *, void *,
		void *, void *, void *);
void __attribute((regparm(2))) fcn_fffa91af(u32, void *);
void __attribute((regparm(2))) fcn_fffa0020(void *, void *);

static inline u8 shupd(u8 a, u8 b, int sh)
{
	a &= (0xff - (1 << sh));
	a |= ((b & 1) << sh);
	return a;
}

static void frag_fffa1e83(void *ebx, void *esi, pei_raminit_ppi *ppi)
{
#ifndef T8
#undef T8
#endif
#define T8(d,s) do { *(u8*)(ebx + d) = *(u8*)(esi + s); } while (0);
#define SW16(d, s) do { T8(d + 1, s); T8(d, s + 1); } while (0);

	u8 tmp;
	uint8_t v = ppi->v;

	*(u32*)(ebx + 0x8b) = *(u32*)(esi + 0x4e);
	*(u16*)(ebx + 0x8f) = 0x3e8;
	*(u8*)(ebx + 0x54) = 0;
	T8(0x57, 0x2e);
	T8(0x6d8, 0x2f); T8(0x6d9, 0x30); T8(0x6da, 0x31);
	T8(0x6db, 0x6b);

	tmp = *(u8*)(ebx + 0x6dc);
	for (int i = 0; i < 8; i++) {
		tmp = shupd(tmp, *(u8*)(esi + 0x32 + i), i);
	}
	*(u8*)(ebx + 0x6dc) = tmp;

	tmp = *(u8*)(ebx + 0x6dd);
	for (int i = 0; i < 8; i++) {
		if (i == 3) continue;
		tmp = shupd(tmp, *(u8*)(esi + 0x3a + i), i);
	}
	*(u8*)(ebx + 0x6dd) = tmp;

	tmp = *(u8*)(ebx + 0x6de);
	tmp = shupd(tmp, *(u8*)(esi + 0x42), 0);
	tmp = shupd(tmp, *(u8*)(esi + 0x43), 2);
	tmp = shupd(tmp, *(u8*)(esi + 0x44), 3);
	tmp = shupd(tmp, *(u8*)(esi + 0x47), 6);
	tmp = shupd(tmp, *(u8*)(esi + 0x48), 7);
	*(u8*)(ebx + 0x6de) = tmp;

	tmp = *(u8*)(ebx + 0x6df);
	tmp = shupd(tmp, *(u8*)(esi + 0x49), 0);
	tmp = shupd(tmp, *(u8*)(esi + 0x4a), 1);
	tmp = shupd(tmp, *(u8*)(esi + 0x4b), 2);

	if (v > 1) {
		tmp = shupd(tmp, *(u8*)(esi + 0x58), 3);
		tmp = shupd(tmp, *(u8*)(esi + 0x59), 4);
		tmp = shupd(tmp, *(u8*)(esi + 0x5a), 5);
	} else {
		tmp = (tmp & 0xe7) | 0x20;
	}
	*(u8*)(ebx + 0x6df) = tmp;

	tmp = *(u8*)(ebx + 0x6de);
	if (v > 3) {
		tmp = shupd(tmp, *(u8*)(esi + 0x5c), 1);
		*(u8*)(ebx + 0x6de) = tmp;

		for (int i = 0; i < 7; i++) {
			T8(0x91 + i, 0x5d + i);
		}
	} else {
		*(u8*)(ebx + 0x6de) = tmp | 2;
		*(u8*)(ebx + 0x91) = 0xff;
		*(u8*)(ebx + 0x92) = 0x40;
		*(u8*)(ebx + 0x93) = 1;
		*(u8*)(ebx + 0x94) = 1;
		*(u8*)(ebx + 0x95) = 0;
		*(u8*)(ebx + 0x96) = 7;
		*(u8*)(ebx + 0x97) = 0;
	}

	if (v > 4) {
		u32 v64 = *(u32*)(esi + 0x64);
		if (v64 > 89999999) {
			*(u32*)(ebx + 0x21) = (v64 / 1000000) * 1000000;
		} else {
			*(u32*)(ebx + 0x21) = 100000000;
		}
	} else {
		*(u32*)(ebx + 0x21) = 100000000;
	}

	tmp = *(u8*)(ebx + 0x6df);
	if (v > 5) {
		tmp = shupd(tmp, *(u8*)(esi + 0x6a), 6);
	} else {
		tmp |= 0x40;
	}
	*(u8*)(ebx + 0x6df) = tmp;

	if (v > 8) {
		*(u32*)(ebx + 0x83) = ppi->ram_data->ied_region_size >> 0x14;
		T8(0x98, 0x6c); T8(0x99, 0x6d);
		*(u16*)(ebx + 0x9a) = *(u16*)(esi + 0x6e);
		T8(0x9c, 0x70);
	} else {
		*(u32*)(ebx + 0x83) = 4;
		*(u8*)(ebx + 0x98) = 0;
		*(u8*)(ebx + 0x99) = 1;
		*(u16*)(ebx + 0x9a) = 0x30ce;
		*(u8*)(ebx + 0x9c) = 1;
	}

	if (v > 9) {
		for (int i = 0; i < 4; i++) {
			T8(0x9d + i, 0x71 + i);
		}
		int is_ult = (*(u32*)(ebx + 0x2d) == HASWELL_FAMILY_ULT);
		if (is_ult) {
			T8(0xa1, 0x75);
		}
		for (int i = 0; i < 5; i++) {
			T8(0xa2 + i, 0x76 + i);
		}
		T8(0xa8, 0x7b); T8(0xa7, 0x7c);
		for (int i = 0; i < 5; i++) {
			T8(0xa9 + i, 0x7d + i);
		}
		for (int i = 0; i < 4; i++) {
			T8(0xaf + i, 0x83 + i);
		}
		for (int i = 0; i < 16; i++) {
			T8(0xb4 + i, 0x88 + i);
		}
		/* 0xc4, 0xc5, ..., 0xd6, 0xd7 */
		for (int i = 0; i < 5; i++) {
			SW16(0xc4 + i * 4, 0x98 + i * 2);
			SW16(0xc6 + i * 4, 0xa2 + i * 2);
		}
		T8(0xd8, 0xac); T8(0xd9, 0xad);
		T8(0xdb, 0xaf); T8(0xdc, 0xb0);
		if (is_ult) {
			T8(0xdd, 0xb1); T8(0xde, 0xb2);
		}
	} else {
		int is_ult = (*(u32*)(ebx + 0x2d) == HASWELL_FAMILY_ULT);
		*(u8*)(ebx + 0x9d) = 0;
		*(u8*)(ebx + 0x9e) = 0;
		*(u8*)(ebx + 0x9f) = 0;
		*(u8*)(ebx + 0xa0) = 1;
		if (is_ult) {
			*(u8*)(ebx + 0xa1) = 0;
		}
		*(u8*)(ebx + 0xa2) = 0;
		*(u8*)(ebx + 0xa3) = 1;
		*(u8*)(ebx + 0xa4) = 0;
		*(u8*)(ebx + 0xa6) = 3;
		for (int i = 0; i < 5; i++) {
			*(u8*)(ebx + 0xa9) = 0;
		}
		for (int i = 0; i < 4; i++) {
			*(u8*)(ebx + 0xaf) = 0;
		}
		for (int i = 0; i < 2; i++) {
			u8 *b1 = ebx + i * 2;
			*(u8*)(ebx + i + 0xa7) = 0;
			for (int j = 0; j < 4; j++) {
				*(u8*)(b1 + 0xb4 + j * 4) = 0xff;
			}
			for (int j = 0; j < 5; j++) {
				*(u8*)(b1 + 0xc4 + j * 4) = 0;
			}
			for (int j = 0; j < 4; j++) {
				*(u8*)(b1 + 0xb5 + j * 4) = 0xff;
			}
			for (int j = 0; j < 5; j++) {
				*(u8*)(b1 + 0xc5 + j * 4) = 0;
			}
		}
		*(u8*)(ebx + 0xd8) = 1;
		*(u16*)(ebx + 0xd9) = 0x200;
		*(u8*)(ebx + 0xdb) = 0;
		*(u8*)(ebx + 0xdc) = 0x30;
		if (is_ult) {
			*(u8*)(ebx + 0xdd) = 1;
			*(u8*)(ebx + 0xde) = 0x40;
		}
	}

	if (v > 10) {
		T8(0x59, 0xc2); T8(0x5a, 0xc3); T8(0x6e5, 0xc4);
	} else {
		*(u8*)(ebx + 0x59) = 1;
		*(u8*)(ebx + 0x5a) = 1;
		*(u8*)(ebx + 0x6e5) = 0;
	}

	tmp = *(u8*)(ebx + 0x6dd);
	if (v > 11) {
		tmp = shupd(tmp, *(u8*)(esi + 0xc5), 3);
	} else {
		tmp |= 8;
	}
	*(u8*)(ebx + 0x6dd) = tmp;

	tmp = *(u8*)(ebx + 0x6de);
	if (v > 0xe) {
		tmp = shupd(tmp, *(u8*)(esi + 0xc7), 4);
	} else {
		tmp = shupd(tmp, 1, 4);
	}
	*(u8*)(ebx + 0x6de) = tmp;

	*(u32*)(ebx + 0x41) = 0;
	*(u8*)(ebx + 0x40) = 0;
	T8(0x56, 0x11);
	T8(0x58, 0x2c);
	T8(0x53, 0);
	T8(0x6e1, 0x52);

	if (*(u32*)(ebx + 0x2d) == HASWELL_FAMILY_ULT) {
		*(u8*)(ebx + 0x6e3) = 0;
		T8(0x6e2, 0x57);
	}

	/* record for DIMMs starting at offset 0xdf:
	 * 0x00: u32
	 * 0x04: u8 number of enabled channels
	 *
	 * 0x05: per channel structures, each has 0x2fa bytes
	 *       0x00: u32 channel enabled (2: enabled, 1: disabled)
	 *       0x04: u32 enabled DIMMs (0, 1, 2)
	 *       0x08: per DIMM structures, each has 0x14f bytes
	 *             0x00: u32 DIMM disabled (0: enabled, 1: disabled)
	 *             0x24: u8[256] SPD
	 *             0x14e: u8 SPD address
	 */
	void *ptr0 = ebx + 0xdf;
	*(u8*)(ebx + 0xe3) = 0;
	for (int i = 0; i < 2; i++) {
		void *ptr1 = ptr0 + i * 0x2fa;
		void *ptr2 = ptr1 + 5;
		/* ram_param + 0x2a: channel i disabled */
		tmp = *(u8*)(esi + i + 0x2a);
		printk(BIOS_DEBUG, "dimm_channel%d_disabled = %hhd\n", i, tmp);

		if (tmp == 2) { /* disable DIMM 1 */
			*(u32*)(ptr2 + 8) = 0;
			*(u32*)(ptr2 + 0x157) = 1;
			*(u32*)(ptr2) = 2;
			(*(u8*)(ptr0 + 4))++;
			*(u32*)(ptr2 + 4) = 1;
		} else if (tmp == 3) { /* disable DIMM 0+1 */
			*(u32*)(ptr2 + 8) = 1;
			*(u32*)(ptr2 + 0x157) = 1;
			*(u32*)(ptr2) = 1;
			*(u32*)(ptr2 + 4) = 0;
		} else if (tmp != 1) { /* 0: enable channel */
			*(u32*)(ptr2 + 8) = 0;
			*(u32*)(ptr2 + 0x157) = 0;
			*(u32*)(ptr2) = 2;
			(*(u8*)(ptr0 + 4))++;
			*(u32*)(ptr2 + 4) = 2;
		} else { /* tmp == 1: disable DIMM 0 */
			*(u32*)(ptr2 + 8) = 1;
			*(u32*)(ptr2 + 0x157) = 0;
			*(u32*)(ptr2) = 2;
			(*(u8*)(ptr0 + 4))++;
			*(u32*)(ptr2 + 4) = 1;
		}
	}

	u8 *spd_addr = ppi->ram_data->spd_addresses;

	printk(BIOS_DEBUG, "SPD addresses:");
	for (int i = 0; i < 4; i++) {
		printk(BIOS_DEBUG, " 0x%02hhx", spd_addr[i]);
	}
	printk(BIOS_DEBUG, "\n");

	*(u8*)(ebx + 0x23a) = spd_addr[0];
	*(u8*)(ebx + 0x389) = spd_addr[1];
	*(u8*)(ebx + 0x534) = spd_addr[2];
	*(u8*)(ebx + 0x683) = spd_addr[3];
}

static void copy_spd(void *ebx)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(**gpPei);
	struct pei_data *pd = pei->pei_data;

	for (int i = 0; i < 2; i++) {
		int idxi = i * 0x2fa;
		for (int j = 0; j < 2; j++) {
			void *edx = ebx + (idxi + j * 0x14f + 0xd0);
			void *ptr = edx + 0x1c;
			if (*(u8*)(edx + 0x16a) == 0xff &&
					*(u32*)(edx + 0x1c) == 0) {
				printk(BIOS_DEBUG, "Copy SPD for Channel %d Dimm %d\n", i, j);
				/* FIXME: looks like mrc.bin only copies channel 0 slot 0??? */
				mrc_memcpy(edx + 0x40, pd->spd_data, 0x100);
				*(u8*)(ptr + 0x14e) = 0;
			}
		}
	}
}

int __attribute((regparm(3))) fcn_fffa1d20(int bootmode, int v, void *addr,
		EFI_PEI_SERVICES **pps /* not used */, pei_raminit_ppi *ppi);
int __attribute((regparm(3))) fcn_fffa1d20(int bootmode, int v, void *addr,
		EFI_PEI_SERVICES **pps /* not used */, pei_raminit_ppi *ppi)
{
	void *ebx = addr;
	void *esi = (void*)ppi->ram_param;

	*(u32*)(addr + 0x5f) = 0xc8;
	*(u32*)(addr + 0x5b) = (u32)ppi->ram_param;
	*(u32*)(addr + 0x1d) = 0;
	*(u8*)(addr + 0x1c) = 0;
	*(u32*)(addr + 0x45) = 0;

	u32 edx = ppi->ram_param->v04;
	if (edx == 2) {
		*(u32*)(ebx + 0x49) = (bootmode != 4)? 2:0;
	} else if (edx == 3) {
		*(u32*)(ebx + 0x49) = (bootmode != 4)? 3:0;
	} else if (edx != 1) {
		*(u32*)(addr + 0x49) = 0;
	} else {
		if (bootmode == 4) {
			*(u32*)(addr + 0x49) = 0;
		} else {
			*(u32*)(addr + 0x49) = 1;
			*(u32*)(addr + 0x1d) = *(u8*)(esi + 0x53);
			*(u8*)(addr + 0x1c) = *(u8*)(esi + 0x54);
			*(u32*)(addr + 0x45) = *(u16*)(esi + 0x4c);
		}
	}

	/* mchbar: 0xfd8 + 0x67 = 0x103f */
	*(u32*)(addr + 0x67) = (u32)ppi->ram_data->mchbar;
	/* pciexbar: 0x103b */
	*(u32*)(addr + 0x63) = (u32)ppi->ram_data->pciexbar;
	/* smbusbar: 0x1043 */
	*(u32*)(addr + 0x6b) = (u32)ppi->ram_data->smbusbar;
	/* gdxcbar: 0x1047 */
	*(u32*)(addr + 0x6f) = (u32)ppi->ram_data->gdxcbar;
	/* HPET: 0x104b */
	*(u32*)(addr + 0x73) = 0xfed00000;
	*(u32*)(addr + 0x7b) = *(u16*)(ppi->cfg0);

	printk(BIOS_DEBUG, "Max DDR3 frequency: %hd\n", *(u16*)(esi + 1));

	*(u32*)(addr + 0x18) = ppi->ram_param->max_ddr3_freq;
	*(u32*)(addr + 0x7f) = ppi->ram_data->tseg_size >> 0x14;
	*(u32*)(addr + 0x35) = *(u16*)(ppi->cfg0 + 2);
	u32 eax = *(u8*)(ppi->cfg0 + 4);
	if (eax == 0x11) {
		*(u32*)(addr + 0x31) = 0x400;
	} else {
		*(u32*)(addr + 0x31) = eax << 5;
	}

	*(u8*)(addr + 0x55) = 0;
	fcn_fffc8290(addr + 0x39, addr + 0x3a, addr + 0x3b,
			addr + 0x3c, addr + 0x3d, addr + 0x3e);

	*(u32*)(addr + 0x25) = ppi->ram_data->system_type;
	u16 ax = pci_read_config32(PCI_DEV(0, 0, 0), 2);

	u8 dl;
	if (ax == 0xa04 || ax == 0xc04 || ax == 0xa0c || ax == 0xd04) {
		dl = 1;
	} else {
		dl = 0;
	}
	*(u8*)(addr + 0x52) = dl;

	frag_fffa1e83(addr, ppi->ram_param, ppi);
	copy_spd(addr);

	int ret;

	if (v == 2) {
		ret = 2;
	} else if (v == 3) {
		fcn_fffa91af(3, addr); // 2 reg params
		ret = 3;
	} else if (v == 1) {
		ret = 1;
		if (*(u32*)(addr + 0x49) == 1) {
			fcn_fffa0020(addr, ppi); // 2 reg params
			ret = v;
		}
		return ret;
	} else {
		fcn_fffa91af(v, addr);
		ret = 0;
	}

	printk(BIOS_DEBUG, "SPD for all slots:\n\n");
	void *chan_record = addr + 0xdf + 5;
	for (int i = 0; i < 2; i++) {
		void *current_channel = chan_record + i * 0x2fa;
		void *slot_record = current_channel + 8;
		for (int j = 0; j < 2; j++) {
			void *current_slot = slot_record + j * 0x14f;
			u8 *spd = (u8*)(current_slot + 0x24);
			printk(BIOS_DEBUG, "Channel %d DIMM %d:", i, j);
			for (int k = 0; k < 0x100; k++) {
				char delim = ((k % 16) == 0)? '\n':' ';
				printk(BIOS_DEBUG, "%c%02hhx", delim, spd[k]);
			}
			printk(BIOS_DEBUG, "\n");
		}
	}

	if (*(u32*)(addr + 0x49) == 1) {
		fcn_fffa0020(addr, ppi);
	}
	return ret;
}

int MRCABI do_smbus_op(EFI_SMBUS_OPERATION op, u32 addr_desc, void *buf, int *retcode)
{
	EFI_PEI_SMBUS_PPI *smbus;
	u32 length = 1;
	EFI_SMBUS_DEVICE_ADDRESS sa = { .SmbusDeviceAddress = (addr_desc >> 1) & 0x7f };
	EFI_SMBUS_DEVICE_COMMAND cmd = (u8)(addr_desc >> 8);
	int PecCheck = (addr_desc >> 22) & 1;

	const EFI_PEI_SERVICES **pps = *gpPei;
	(*pps)->LocatePpi(pps, &gEfiPeiSmbusPpiGuid, 0, NULL, (void**)&smbus);

	printk(BIOS_DEBUG, "do_smbus_op: op = %d, addr = 0x%02x, cmd = 0x%x.\n",
			(u32)op, (u32)sa.SmbusDeviceAddress, (u32)cmd);

	int ret = smbus->Execute((EFI_PEI_SERVICES**)pps, smbus,
			sa, cmd, op, PecCheck,
			&length, buf);

	if (op == EfiSmbusReadByte) {
		printk(BIOS_DEBUG, "do_smbus_op: reads 0x%02hhx.\n", *(u8*)buf);
	}

	if (retcode != NULL)
		*retcode = ret;

	return length;
}
