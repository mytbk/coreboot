#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include "mrc_smbus.h"
#include "mrc_pch_init.h"
#include <console/console.h>

static void io_fffa3c2e(void)
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
void fcn_fffb9720(const EFI_PEI_SERVICES **ps, int, int);

void mrc_frag_smbus(void);
void mrc_frag_smbus(void)
{
	const EFI_PEI_SERVICES **pps = *gpPei;

	fcn_fffb9720(pps, 0, 0);
	mrc_printk("System Agent: Initializing PCH (SMBUS)\n");

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

static const uint32_t ref_fffcc8dc[] = {
	0, 1, 2, 0, 0, 0, 0, 3, 0x01010001, 0x07010201
};
extern EFI_GUID gPchDmiTcVcPpiGuid;
extern EFI_PEI_PPI_DESCRIPTOR ref_fffcc97c;
extern EFI_PEI_NOTIFY_DESCRIPTOR ref_fffcca30;
extern EFI_PEI_NOTIFY_DESCRIPTOR ref_fffcd560;

void mrc_frag_pch(void);
void mrc_frag_pch(void)
{
	const EFI_PEI_SERVICES **pps = *gpPei;

	mrc_printk("System Agent: Initializing PCH\n");

	RCBA16(DISPBDF) = 0x0010;
	RCBA32_OR(FD2, PCH_ENABLE_DBDF);
	u16 tmp = pci_read_config16(PCH_LPC_DEV, GEN_PMCON_3);
	if (tmp & 4) {
		io_fffa3c2e();
	}
	RCBA32(0x3310) = 0x10;
	mrc_pch_init();

	EFI_PEI_PPI_DESCRIPTOR *desc = mrc_alloc(sizeof(EFI_PEI_PPI_DESCRIPTOR));
	if (desc == NULL)
		return;

	void *ppi = mrc_alloc(0x28);
	if (ppi == NULL)
		return;

	mrc_memcpy(ppi, ref_fffcc8dc, 0x28);
	desc->Flags = 0x80000010;
	desc->Guid = &gPchDmiTcVcPpiGuid;
	desc->Ppi = ppi;

	(*pps)->InstallPpi(pps, desc);
	(*pps)->InstallPpi(pps, &ref_fffcc97c);
	(*pps)->NotifyPpi(pps, &ref_fffcca30);
	(*pps)->NotifyPpi(pps, &ref_fffcd560);
}

void io_fffa4188(void);
void io_fffa4188(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x904, 0xffffffe0, 2);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x924, 0xffffffe0, 2);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x904, 0xfffffc1f, 0x60);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x924, 0xfffffc1f, 0x60);
}

void io_fffa4235(void);
void io_fffa4235(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x90c, 0xfffff81f, 0x120);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x92c, 0xfffff81f, 0x120);
}

void io_fffa42c3(void);
void io_fffa42c3(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x904, 0xfe3fffff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x924, 0xfe3fffff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x904, 0x9fffffff, 0x20000000);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x924, 0x9fffffff, 0x20000000);
}

void io_fffa43e1(void);
void io_fffa43e1(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x90c, 0xfff1ffff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x92c, 0xfff1ffff, 0);
}

void io_fffa445e(void);
void io_fffa445e(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x910, 0xffffc3ff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x930, 0xffffc3ff, 0);
}

void io_fffa44ad(void);
void io_fffa44ad(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x90c, 0xfe1fffff, 0xa00000);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x92c, 0xfe1fffff, 0xa00000);
}

void io_fffa4575(void);
void io_fffa4575(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x80c, 0xffe3ffff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x82c, 0xffe3ffff, 0);
}

void io_fffa45f1(void);
void io_fffa45f1(void)
{
	pci_update_config32(PCI_DEV(0, 0, 0), 0x910, 0x1fffffff, 0x80000000);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x930, 0x1fffffff, 0x80000000);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x80c, 0xfffffe7f, 1);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x82c, 0xfffffe7f, 1);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x80c, 0xffffcfff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x82c, 0xffffcfff, 0);
}

void io_fffa476b(void);
void io_fffa476b(void)
{
	pci_or_config32(PCI_DEV(0, 0, 0), 0x80c, 0x600000);
	pci_or_config32(PCI_DEV(0, 0, 0), 0x82c, 0x600000);
}

void __attribute((regparm(1))) io_fffa49a0(uint32_t v);
void __attribute((regparm(1))) io_fffa49a0(uint32_t v)
{
	pci_update_config16(PCI_DEV(0, 1, 0), 0xc38, 0xffbf, v);
	pci_update_config16(PCI_DEV(0, 1, 1), 0xc38, 0xffbf, v);
	pci_update_config16(PCI_DEV(0, 1, 2), 0xc38, 0xffbf, v);

	pci_update_config16(PCI_DEV(0, 1, 0), 0x260, 0xfffc, 2);
	pci_update_config16(PCI_DEV(0, 1, 1), 0x260, 0xfffc, 2);
	pci_update_config16(PCI_DEV(0, 1, 2), 0x260, 0xfffc, 2);

	pci_update_config32(PCI_DEV(0, 0, 0), 0x900, 0xf3ffffff, 0);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x920, 0xf3ffffff, 0);

	pci_or_config32(PCI_DEV(0, 0, 0), 0x904, 0x0c00);
	pci_or_config32(PCI_DEV(0, 0, 0), 0x924, 0x0c00);

	pci_update_config32(PCI_DEV(0, 0, 0), 0x90c, 0xc1ffffff, 0xe000000);
	pci_update_config32(PCI_DEV(0, 0, 0), 0x92c, 0xc1ffffff, 0xe000000);
}

void io_fffa4c0d(void);
void io_fffa4c0d(void)
{
	pci_update_config32(PCI_DEV(0, 1, 0), 0x91c, 0xc7ffffff, 0x28000000);
	pci_update_config32(PCI_DEV(0, 1, 0), 0x93c, 0xc7ffffff, 0x28000000);
}
