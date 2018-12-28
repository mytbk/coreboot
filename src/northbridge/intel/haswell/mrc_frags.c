// other random frags extracted from mrc
//
#include <arch/pci_ops.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <console/console.h>
#include "mrc_utils.h"
#include "mrc_pei.h"

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
