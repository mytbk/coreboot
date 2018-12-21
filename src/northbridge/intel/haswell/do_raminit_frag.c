#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include "mrc_smbus.h"

// loc_fffa3c2e
//
void io_fffa3c2e(void);
void io_fffa3c2e(void)
{
	u32 reg3410;
	u8 t1, t2, tmp;

	RCBA32_OR(0x3410, 0x10);
	reg3410 = RCBA32(0x3410);
	t1 = inb(0x70) & 0x80;
	t2 = t1 | 0xa;
	RCBA32_AND_OR(0x3410, 0xffffffef, 0);
	reg3410 = RCBA32(0x3410);
	outb(t2, 0x70);
	tmp = (inb(0x71) & 0x8f) | 0x60;
	outb(tmp, 0x71);
	t1 |= 0xb;
	outb(t1, 0x70);
	tmp = inb(0x71) | 0x80;
	outb(tmp, 0x71);
	outb(t2, 0x70);
	tmp = (inb(0x71) & 0x8f) | 0x20;
	outb(tmp, 0x71);
	outb(t1, 0x70);
	tmp = inb(0x71) & 0x7f;
	outb(tmp, 0x71);
}

static const EFI_PEI_SERVICES ***gpPei = (const EFI_PEI_SERVICES***)0xff7d7538;
void __attribute((regparm(2))) fcn_fffc5bf6(const EFI_PEI_SERVICES **ps, void *);

void mrc_frag_smbus(void);
void mrc_frag_smbus(void)
{
	const EFI_PEI_SERVICES **pps = *gpPei;
	void *mem = mrc_alloc(0x10f);
	if (mem == NULL)
		return;
	fcn_fffc5bf6(pps, mem);
	pci_update_config32(PCI_DEV(0, 0x1f, 3), 0x20, 0xffe0, *(u32*)(mem + 0xc));
	pci_or_config8(PCI_DEV(0, 0x1f, 3), 4, 1);
	pci_or_config8(PCI_DEV(0, 0x1f, 3), 0x40, 8);
	pci_update_config32(PCI_DEV(0, 0x1f, 3), 0x40, 0xfffffff8, 1);
	mrc_smbus_outb(0, 0xff);

	(*pps)->InstallPpi(pps, mem + 0x10);
	(*pps)->NotifyPpi(pps, mem + 0x2c);
}
