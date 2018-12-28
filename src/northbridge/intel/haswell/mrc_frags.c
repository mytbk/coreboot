// other random frags extracted from mrc
//
#include <device/pci_ops.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <console/console.h>
#include "mrc_utils.h"
#include "mrc_pei.h"

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

void frag_fffa1e83(void *ebx, void *esi, uint8_t v);
void frag_fffa1e83(void *ebx, void *esi, uint8_t v)
{
#ifndef T8
#undef T8
#endif
#define T8(d,s) do { *(u8*)(ebx + d) = *(u8*)(esi + s); } while (0);

	u8 tmp;

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
