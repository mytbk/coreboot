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

void frag_fffa1e83(void *ebx, void *esi);
void frag_fffa1e83(void *ebx, void *esi)
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
