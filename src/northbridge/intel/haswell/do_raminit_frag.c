#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include "mrc_smbus.h"
#include "mrc_pch_init.h"
#include <console/console.h>
#include "pei_data.h"
#include "pei_usb.h"
#include "pei_ram.h"
#include "mrc_sku.h"

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

void load_usb(PEI_USB *pusb, struct pei_data *pd);
void load_usb(PEI_USB *pusb, struct pei_data *pd)
{
	memset(pusb, 0, sizeof(pusb));

	pusb->v0 = 1;

	for (int i = 0; i < 14; i++) {
		pusb->ehci_settings[i].enable = pd->usb2_ports[i].enable;
		pusb->ehci_settings[i].location = pd->usb2_ports[i].location;
		pusb->ehci_settings[i].length = pd->usb2_ports[i].length;
	}

	for (int i = 0; i < 14; i++)
		pusb->ehci_oc[i] = pd->usb2_ports[i].over_current_pin;

	for (int i = 0; i < 6; i++)
		pusb->xhci_oc[i] = pd->usb3_ports[i].over_current_pin;

	for (int i = 0; i < 6; i++)
		pusb->xhci_en[i] = pd->usb3_ports[i].enable;

	pusb->xhci_resume_info[0] = 1;
	pusb->xhci_resume_info[1] = 1;
	pusb->xhci_resume_info[2] = 2;
}

void fill_pei_ram_data(pei_ram_data *r, struct pei_data *pd);
void fill_pei_ram_data(pei_ram_data *r, struct pei_data *pd)
{
	int i;
	for (i = 0; i < 4; i++) {
		r->spd_addresses[i] = pd->spd_addresses[i];
	}
	r->mchbar = pd->mchbar;
	r->dmibar = pd->dmibar;
	r->epbar = pd->epbar;
	r->pciexbar = pd->pciexbar;
	r->smbusbar = pd->smbusbar;
	r->gdxcbar = 0xfed84000;
	r->tseg_size = pd->tseg_size;
	r->system_type = pd->system_type;
	r->v1 = 1;
	r->edrambar = 0xfed80000;
	r->ied_region_size = 0x400000;
	for (i = 0; i < 5; i++) {
		r->padding[i] = 0;
	}
}

int haswell_family_model(void);
int haswell_stepping(void);

#define HASWELL_FAMILY_MOBILE 0x306c0
#define HASWELL_FAMILY_ULT 0x40650
#define HASWELL_FAMILY_GT3E 0x40660

void mrc_set_bars(pei_ram_data *r);
void mrc_set_bars(pei_ram_data *r)
{
	int model = haswell_family_model();

	pci_write_config32(PCI_DEV(0, 0, 0), 0x48, r->mchbar | 1);
	pci_write_config32(PCI_DEV(0, 0, 0), 0x4c, 0);

	pci_write_config32(PCI_DEV(0, 0, 0), 0x68, r->dmibar | 1);
	pci_write_config32(PCI_DEV(0, 0, 0), 0x6c, 0);

	pci_write_config32(PCI_DEV(0, 0, 0), 0x40, r->epbar | 1);
	pci_write_config32(PCI_DEV(0, 0, 0), 0x44, 0);

	write32((void*)r->mchbar + 0x5420, r->gdxcbar | 1);
	write32((void*)r->mchbar + 0x5424, 0);

	if (model == HASWELL_FAMILY_GT3E) {
		write32((void*)r->mchbar + 0x5408, r->edrambar | 1);
		write32((void*)r->mchbar + 0x540c, 0);
	}
}

extern EFI_GUID ref_fffcd4a4;
extern EFI_GUID ref_fffcc8bc;
void* frag_fffa3eec(void *raminit_ppi);
void* frag_fffa3eec(void *raminit_ppi)
{
	const EFI_PEI_SERVICES **pps = *gpPei;
	EFI_HOB_DATA *hob;

	(*pps)->CreateHob(pps, 4, 0x6d, (void**)&hob);
	memcpy((void*)hob + 8, &ref_fffcd4a4, 16);
	mrc_zeromem((void*)hob + 0x18, 8);
	mrc_zeromem((void*)hob + 0x20, 8);
	mrc_zeromem((void*)hob + 0x29, 0x1e);
	*(uint8_t*)((void*)hob + 0x28) = 0;
	*(uint8_t*)((void*)hob + 0x6c) = 0;

	if (*(uint8_t*)raminit_ppi > 1) {
		void *p1 = *(void**)(raminit_ppi + 0xd);
		*(uint16_t*)((void*)hob + 0x47) = *(uint16_t*)(p1 + 0x4a);
		*(uint8_t*)((void*)hob + 0x49) = *(uint8_t*)(p1 + 0x49);
	} else {
		*(uint16_t*)((void*)hob + 0x47) = 0;
		*(uint8_t*)((void*)hob + 0x49) = 0;
	}
	return hob;
}

void* frag_fffa3f8c(void *hob);
void* frag_fffa3f8c(void *hob)
{
	const EFI_PEI_SERVICES **pps = *gpPei;
	void *ppi;

	(*pps)->LocatePpi(pps, &ref_fffcc8bc, 0, NULL, &ppi);

	*(uint8_t*)(hob + 0x20) = 2;
	void *p2 = *((void**)(ppi + 1));
	if ((*(uint8_t*)p2 & 0x10) != 0) {
		void *p3 = *((void**)(ppi + 9));
		void *p4 = *((void**)p3);
		*(uint8_t*)((void*)hob + 0x21) = *(uint8_t*)(p4 + 0x301);
	}
	return ppi;
}

extern EFI_PEI_PPI_DESCRIPTOR ref_fffcc910;
extern EFI_PEI_PPI_DESCRIPTOR PchMeUmaDesc;
extern void __attribute((regparm(1))) mrc_init_memory(const EFI_PEI_SERVICES **pps);
extern EFI_GUID mEfiMemoryRestoreDataGuid;

void frag_fffa54e7(int bootmode, struct pei_data *pd);
void frag_fffa54e7(int bootmode, struct pei_data *pd)
{
	const EFI_PEI_SERVICES **pps = *gpPei;

	(*pps)->InstallPpi(pps, &ref_fffcc910);
	mrc_printk("System Agent: Initializing PCH (Me UMA)\n");
	(*pps)->InstallPpi(pps, &PchMeUmaDesc);
	mrc_printk("System Agent: Initializing Memory\n");
	mrc_init_memory(pps);

	void *hob = locate_hob(&mEfiMemoryRestoreDataGuid, 0xfffe);
	if (hob == NULL) {
		if (bootmode != 0x11)
			mrc_printk("System Agent: failed to locate restore data hob!\n");

		pd->mrc_output_len = 0;
		pd->mrc_output = NULL;
	} else {
		pd->mrc_output_len = *(uint32_t*)(hob + 0x18);
		pd->mrc_output = (unsigned char*)(hob + 0x1c);
	}
	mrc_printk("System Agent: Done.\n");
}

void frag_fffa3fd4(pei_raminit_ppi *ram_ppi);
void frag_fffa3fd4(pei_raminit_ppi *ram_ppi)
{
	int model = haswell_family_model();
	int stepping = haswell_stepping();

	if (model == HASWELL_FAMILY_MOBILE && stepping == 1) {
		write32((void*)(ram_ppi->ram_data->mchbar + 0x5434), 0x1060100);
	} else {
		uint32_t dmibar = ram_ppi->ram_data->dmibar;
		write32((void*)(dmibar + 0x71c), ram_ppi->v);
		write32((void*)(dmibar + 0x720), 0x1060100);
	}
}

static void frag_fffa3ba4(PEI_USB *pusb)
{
	int nb_ehci = nb_usb2_ports();

	for (int i = 0; i < nb_ehci; i++) {
		PEI_EHCI *setting = &pusb->ehci_settings[i];
		uint8_t loc = setting->location;
		if (loc == 5) {
			setting->f4 = 5;
			setting->f5 = 2;
		} else if (loc == 2) {
			setting->f4 = 4;
			setting->f5 = 2 - (setting->length < 0x50);
		} else if (setting->length <= 0x6f) {
			setting->f4 = 5;
			setting->f5 = 2;
		} else {
			setting->f4 = 6;
			if (setting->length <= 0xff) {
				setting->f5 = 2;
			} else {
				setting->f5 = 3;
			}
		}
	}
}

static void frag_fffa3aa7(PEI_USB *pusb)
{
	int nb_ehci = nb_usb2_ports();

	for (int i = 0; i < nb_ehci; i++) {
		PEI_EHCI *setting = &pusb->ehci_settings[i];
		uint8_t loc = setting->location;
		if (loc == 0) {
			setting->f4 = 4;
			if (setting->length <= 0x7f) {
				setting->f5 = 2;
			}
			setting->f5 = 4 - (setting->length < 0x130);
		} else {
			setting->f4 = 3;
			setting->f5 = 2;
		}
	}
}

static void frag_fffa3c1b(PEI_USB *pusb)
{
	int nb_ehci = nb_usb2_ports();

	for (int i = 0; i < nb_ehci; i++) {
		PEI_EHCI *setting = &pusb->ehci_settings[i];
		uint8_t loc = setting->location;
		if (loc == 0 || loc == 3) {
			if (setting->length > 0x6f) {
				setting->f4 = 6;
				if (setting->length > 0xff)
					setting->f5 = 3;
				else
					setting->f5 = 2;
			} else {
				setting->f4 = 5;
				setting->f5 = 2;
			}
		} else if (loc == 2) {
			setting->f4 = 0x50;
			setting->f5 = 2 - (setting->length < 0x50);
		} else {
			setting->f4 = 5;
			setting->f5 = 2;
		}
	}
}

void frag_fffa3a17(PEI_USB *pusb);
void frag_fffa3a17(PEI_USB *pusb)
{
	int sku = mrc_sku_type();
	if (sku != 1) {
		if (sku != 2)
			return;
		frag_fffa3c1b(pusb);
		return;
	}

	uint16_t did = pci_read_config16(PCH_LPC_DEV, 2);
	if (is_desktop_pch(did)) {
		frag_fffa3aa7(pusb);
		return;
	}
	if (is_mobile_pch(did)) {
		frag_fffa3ba4(pusb);
		return;
	}
	did -= 0x9c41;
	if (did <= 6) {
		frag_fffa3ba4(pusb);
		return;
	}
}

void frag_fffa40d3(uint32_t bar);
void frag_fffa40d3(uint32_t dmibar)
{
	printk(BIOS_DEBUG, "bar for frag_fffa40d3 is 0x%08x.\n", dmibar);
	for (uint32_t i = 0xa00; i < 0xa40; i += 0x10) {
		if (dmibar) {
			u32 tmp = read32((void*)(dmibar + i));
			tmp &= 0xffffffe0;
			tmp |= 0xc;
			write32((void*)(dmibar + i), tmp);
		} else {
			pci_update_config32(PCI_DEV(0, 0, 0), i,
					0xffffffe0, 0xc);
		}
	}
}

void frag_fffa4507(void *ppi);
void frag_fffa4507(void *ppi)
{
	uint32_t a;
	for (int i = 0; i < 2; i++) {
		if (*(uint8_t*)ppi > 2) {
			void *p1 = *(void**)(ppi + 0xd);
			a = *(uint8_t*)(p1 + i + 0x54);
			a <<= 6;
		} else {
			a = 0x200;
		}
		pci_update_config32(PCI_DEV(0, 0, 0), 0x910 + (i << 5),
				0xfffffc3f, a);
	}
}

void fill_ram_param(pei_ram_param *param, struct pei_data *pd);
void fill_ram_param(pei_ram_param *param, struct pei_data *pd)
{
	memset(param, 0, sizeof(pei_ram_param));
	param->v00 = 1;
	param->v03[0] = 1;
	param->v03[14] = 1;
	param->v03[0x21] = 1;
	param->v2c[0] = 1;
	param->v2c[2] = 1;
	param->v2c[3] = 1;
	param->v2c[4] = 4;
	param->v2c[5] = 12;
	for (int i = 0; i < 4; i++)
		param->v2c[i + 7] = 1;
	for (int i = 0; i < 3; i++)
		param->v2c[i + 12] = 1;
	param->v2c[16] = 1;
	param->v2c[18] = 1;
	for (int i = 0; i < 5; i++)
		param->v2c[20] = 1;
	for (int i = 0; i < 3; i++)
		param->v2c[i + 27] = 1;
	param->v2c[42] = 1;
	param->dq_pins_interleaved = pd->dq_pins_interleaved;
	param->ddr_refresh_2x = param->ddr_refresh_2x_76 = pd->ddr_refresh_2x;
	param->v5a[0] = param->v5a[2] = 1;
	param->v5a[3] = 6;
	param->v5a[4] = 0x40;
	param->v5a[5] = param->v5a[6] = 1;
	param->v5a[8] = 7;
	param->v64 = 0x05f5e100;
	param->v6a[0] = 1;
	param->v6e = 0x30ce;
	param->v70[0] = param->v70[4] = 1;
	param->v77[0] = param->v77[3] = 1;
	for (int i = 0; i < 16; i++)
		param->v77[i + 0x11] = 0xff;
	param->v77[53] = 1;
	param->vad = 0x200;
	param->vb0[0] = 0x30;
	param->vb0[1] = 1;
	param->vb0[2] = 0x40;
	param->vb0[18] = 1;
	param->vb0[19] = 1;
	param->vb0[21] = 1;

	int freq = pd->max_ddr3_freq;
	switch (freq) {
		case 1600:
		case 1333:
		case 1067:
		case 800:
			param->max_ddr3_freq = freq;
			break;
		default:
			printk(BIOS_ERR, "System Agent: Unsupported DDR3 frequence %d (Supported are 800, 1067, 1333, 1600)", freq);
			die("System halted.");
	}
}
