// other random frags extracted from mrc
//
#include <device/pci_ops.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <console/console.h>
#include "mrc_utils.h"
#include "mrc_pei.h"
#include "mrc_sku.h"
#include <cpu/intel/haswell/haswell.h>

void frag_fffa0ff3(void);
void frag_fffa0ff3(void)
{
	pci_update_config16(PCI_DEV(0, 2, 0), 4, 0xfff9, 0);
	pci_read_config32(PCI_DEV(0, 2, 0), 0x10);
	pci_write_config32(PCI_DEV(0, 2, 0), 0x10, 0);
	pci_read_config32(PCI_DEV(0, 2, 0), 0x14);
	pci_write_config32(PCI_DEV(0, 2, 0), 0x14, 0);
}

static inline u8 shupd(u8 a, u8 b, int sh)
{
	a &= (0xff - (1 << sh));
	a |= ((b & 1) << sh);
	return a;
}

void frag_fffa1e83(void *ebx, void *esi, void *edi);
void frag_fffa1e83(void *ebx, void *esi, void *edi)
{
#ifndef T8
#undef T8
#endif
#define T8(d,s) do { *(u8*)(ebx + d) = *(u8*)(esi + s); } while (0);
#define SW16(d, s) do { T8(d + 1, s); T8(d, s + 1); } while (0);

	u8 tmp;
	uint8_t v = *(u8*)edi;

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
		void *p1 = *(void**)(edi + 1);
		*(u32*)(ebx + 0x83) = (*(u32*)(p1 + 0x2b)) >> 0x14;
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
}

void frag_fffa5d3c(void *bar, uint32_t offset);
void frag_fffa5d3c(void *bar, uint32_t offset)
{
	/* [ebx + 0x103f] is 0xfed10000 (DEFAULT_MCHBAR)
	printk(BIOS_DEBUG, "[ebx + 0x103f] is 0x%08x.\n",
			(uint32_t)bar);
			*/
	write32(bar + offset, 0x200c040);
	write32(bar + offset + 0x10, 0x88888888);
	write32(bar + offset + 0x20, 0x3b08060);
	write32(bar + offset + 0x30, 0x88888888);
}

void frag_fffa627c(void *mchbar, uint32_t eax, void * edx);
void frag_fffa627c(void *mchbar, uint32_t eax, void * edx)
{
	/* mchbar, edx is 0xff7fd266, 0xff7fe5ad (in stack)
	printk(BIOS_DEBUG, "[ebx + 0x103f] is 0x%08x, edx is 0x%08x.\n",
			(uint32_t)mchbar, (uint32_t)edx);
			*/

	write32(mchbar + eax, 0xc183060);
	write32(mchbar + eax + 0x2210, 0x8102040);
	write32(mchbar + eax + 0x604, 0x8102040);
	write8(edx + 0x2fd, 0x40);
	write8(edx + 0x2fe, 0x40);
	write8(edx + 0x2ff, 0x40);
	write8(edx + 0x300, 0x40);
	write32(mchbar + eax + 0x1ffc, 0);
	write32(mchbar + eax + 0x220c, 0);
	write32(mchbar + eax + 0x600, 0);
}

void frag_fffa9029(void *bar);
void frag_fffa9029(void *bar)
{
	/* bar is 0xf0000000 (PCIEXBAR)
	printk(BIOS_DEBUG, "[edi + 0x103b] is 0x%08x.\n", (u32)bar);
	*/

	bar_or32(bar, 0xa0, 1);
	bar_or32(bar, 0xbc, 1);
	bar_or32(bar, 0xa8, 1);
	bar_or32(bar, 0x90, 1);
	bar_or32(bar, 0x98, 1);
	bar_or32(bar, 0x5c, 1);
	bar_or32(bar, 0xb0, 1);
	bar_or32(bar, 0xb4, 1);
	bar_or32(bar, 0x78, 0x0400);
	bar_or32(bar, 0x50, 1);
}

void frag_fffba1df(void *edx);
void frag_fffba1df(void *edx)
{
	uint32_t pciexbar = read32((void*)0xf0000060) & 0xfc000000;
	uint32_t bus = *(uint8_t*)(edx + 1);

	/* well, bus is just 0...
	printk(BIOS_DEBUG, "frag_fffba1df: bus = %d.\n", bus);
	*/

	void * bbar = (void*)(pciexbar + (bus << 20));
	read32((void*)0xf0000060);
	void *p1 = *(void**)(edx + 0xe);
	uint8_t *pp = *(uint8_t**)p1;
	p1 = *(void**)(edx + 0x26);
	void *p2 = *(void**)(p1 + 1);
	write32(bbar + 0xfe040, (u32)p2);
	write32(bbar + 0xfe044, 0);
	u32 tmp = read32(bbar + 0xfe040);
	tmp |= 1;
	write32(bbar + 0xfe040, tmp);
	write16(p2 + 0x10, 0x154);
	write8(p2 + 6, 0xff);
	write8(p2 + 0x80, 0xff);
	write8(p2 + 0x84, 0);
	write8(p2 + 0x82, 0);

	RCBA32_AND_OR(0x38b0, 0xffff8003, 0x403c);
	tmp = RCBA32(0x38b4);
	tmp &= 0xffff40ff;
	if (tmp != 0) {
		*(u8*)(p2 + 0xa) = 1;
	}
	tmp = read32(bbar + 0xfe040);
	tmp &= 0xfffffffe;
	write32(bbar + 0xfe040, tmp);
	write32(bbar + 0xfe040, 0);

	if ((pp[0] & 1) == 0)
		return;

	u8 bl = pp[1]; u8 cl = pp[2];
	tmp = (u32)bl << 30;
	tmp &= 0x40000000;
	if (cl & 1) tmp |= 0x80000000;
	if (bl & 2) tmp |= 0x4000;
	if (cl & 2) tmp |= 0x8000;

	void *bar1 = *(void**)(edx + 2);
	bar_update32(bar1, 0x33d4, 0x0fff0fff, tmp);
	tmp = ((u32)pp[1] << 8) & 0x400;
	if (pp[2] & 4) tmp |= 0x0800;
	bar_update32(bar1, 0x33c8, 0xfffff0ff, tmp);
}

void frag_fffba341(void *rcba, u8 *data);
void frag_fffba341(void *rcba, u8 *data)
{
	u16 tmp;

	/* rcba = fed1c000, data = ff7ff98b (stack)
	printk(BIOS_DEBUG, "frag_fffba341 rcba = %p, data = %p.\n", rcba, data);
	*/

	if (read8(rcba + 0x31fe) != data[1]) {
		tmp = read16(rcba + 0x31fe);
		tmp &= 0xfeff;
		write16(rcba + 0x31fe, tmp);

		u32 t2 = data[1];
		tmp = read16(rcba + 0x31fe);
		tmp &= 0xff00;
		tmp |= t2;
		write16(rcba + 0x31fe, tmp);
	}
	tmp = read16(rcba + 0x31fe);
	tmp |= 0x0100;
	write16(rcba + 0x31fe, tmp);

	tmp = read16(rcba + 0x31fe);

	u32 t3 = read8(rcba + 0x31fe) << 0xc;
	void *r = (void*)(t3 | 0xfec00000);
	write8(r, 0);
	tmp = data[0];
	void *r2 = (void*)(t3 | 0xfec00010);
	u32 tmp2 = read32(r2) >> 0x18;
	if (tmp != tmp2 && tmp <= 0xf) {
		write8(r, 0);
		write32(r2, ((u32)data[0]) << 0x18);
	}

	if (mrc_sku_type() == 2 && (data[2] & 1) == 0) {
		tmp = read16(rcba + 0x31fe);
		tmp |= 0x0800;
		write16(rcba + 0x31fe, tmp);
	}
}

int freq_sel(int freq);
int freq_sel(int freq)
{
	if (freq <= 800)
		return 10;
	if (freq <= 1067)
		return 13;
	if (freq <= 1333)
		return 16;
	if (freq <= 1600)
		return 20;
	if (freq <= 1867)
		return 23;
	if (freq <= 2133)
		return 26;
	if (freq < 2401)
		return 29;
	return 32;
}

void xhci_setup_ss_route(void);
void xhci_setup_ss_route(void)
{
	u32 tmp;
	tmp = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xdc) & 0x3f;
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd8, 0xffffffc0, tmp); /* USB3 SuperSpeed Enable */
	tmp = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xd4) & 0x7fff;
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd0, 0xffff8000, tmp); /* USB2 Port Routing */
}
