#include <device/pci_ops.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include <console/console.h>
#include "mrc_sku.h"
#include "mrc_wdt.h"
#include "me_uma.h"

u32 get_uma_size(const EFI_PEI_SERVICES **pps, void *me)
{
	int i = 0;
	u32 me_uma;
	u32 hfsts1;

	me_uma = pci_read_config32(PCH_ME_DEV, 0x44);
	hfsts1 = pci_read_config32(PCH_ME_DEV, 0x40);

	if (((hfsts1 >> 16) & 0xf) == 2)
		return 0;

	if (((hfsts1 >> 8) & 0xf0) != 0)
		return 0;

	while ((me_uma & 0x10000) == 0) {
		if (i == 5000)
			return 0;

		i++;
		usleep(1000);
		me_uma = pci_read_config32(PCH_ME_DEV, 0x44);
	}

	if (i != 5000) {
		/* returns Intel ME UMA size */
		u32 sz = me_uma & 0x3f;
		printk(BIOS_DEBUG, "ME UMA Size is %dMB.\n", sz);
		return sz;
	} else {
		return 0;
	}
}

int fcn_fffbe070(const EFI_PEI_SERVICES **pps, void *me, u8 *a2)
{
	int i = 0;
	int ret = 0;

	u32 gmes = pci_read_config32(PCH_ME_DEV, 0x48);

	while ((gmes & 0x100) == 0) {
		if (i == 50) {
			*a2 = 1;
			return ret;
		}
		usleep(1000);
		i++;
		gmes = pci_read_config32(PCH_ME_DEV, 0x48);
	}
	if (i != 50) {
		if (gmes & 0x80) {
			/* clear GEN_PMCON_2 DRAM initialization bit */
			pci_update_config16(PCH_LPC_DEV, 0xa2, 0xff7f, 0);
			ret = fcn_fffbdf70(pps, 1);
		}
		if ((gmes & 0x90) != 0x10)
			return ret;
	}
	*a2 = 1;
	return ret;
}

int fcn_fffbe14d(const EFI_PEI_SERVICES **pps, void *me, int a3, u32 a4)
{
	u32 hfs = pci_read_config32(PCH_ME_DEV, 0x40);

	if (((hfs >> 16) & 0xf) == 2)
		return 0;

	if (((hfs >> 8) & 0xf0) != 0)
		return 0;

	u32 meseg_lo = pci_read_config32(PCI_DEV(0, 0, 0), 0x70);
	u32 meseg_hi = pci_read_config32(PCI_DEV(0, 0, 0), 0x74);
	/* from intel_early_me_init_done in sb/intel/lynxpoint/early_me.c */
	/* low 4 bits of meseg_hi << 12, meseg_lo >> 20 */
	u32 uma_base = ((meseg_hi << 28) | (meseg_lo >> 4)) >> 16;
	u32 meDID = uma_base | (1 << 28);
	if (a4 & 0x80)
		meDID |= (1 << 23);
	meDID |= ((a4 & 0x7f) << 24);
	pci_read_config32(PCH_ME_DEV, 0x4c);
	pci_write_config32(PCH_ME_DEV, 0x4c, meDID);

	usleep(1100);
	pci_read_config32(PCH_ME_DEV, 0x40);

	for (int i = 0; i < 5001; i++) {
		usleep(1000);
		hfs = pci_read_config32(PCH_ME_DEV, 0x40);
		if (((hfs >> 24) & 0xf0) != 0) {
			break;
		}
	}
	return fcn_fffbe110(pps, a3, ((hfs >> 25) & 7));
}

int fcn_fffbe110(const EFI_PEI_SERVICES **pps, u32 me, u8 a3)
{
	pci_read_config32(PCH_ME_DEV, 0x48);
	int v;

	if (a3 == 2) {
		v = 2;
	} else if (a3 == 6) {
		v = 6;
	} else if (a3 == 1) {
		v = 1;
	} else {
		return 0;
	}
	fcn_fffbdf70(pps, v);
	return 0;
}

extern EFI_GUID gWdtPpiGuid;
int __attribute((regparm(2))) fcn_fffbdf70(const EFI_PEI_SERVICES **pps, int v)
{
	PEI_WDT_PPI *wdt = NULL;
	(*pps)->LocatePpi(pps, &gWdtPpiGuid, 0, NULL, (void**)&wdt);
	int sku = mrc_sku_type();
	pci_update_config32(PCH_LPC_DEV, 0xac, 0xffebffff, 0);
	u8 io_cf9 = inb(0xcf9) & 0xf1;

	if (v == 6) {
		u32 gpiobase = pci_read_config32(PCH_LPC_DEV, 0x48) & 0xfffffffe;
		/* GPIO Pin 30 used as GPIO, as output, level low */
		u32 tmp;
		if (sku == 1) {
			tmp = inl(gpiobase);
			tmp |= 0x40000000;
			outl(tmp, gpiobase);

			tmp = inl(gpiobase + 4);
			tmp &= 0xbfffffff;
			outl(tmp, gpiobase + 4);

			tmp = inl(gpiobase + 0xc);
			tmp &= 0xbfffffff;
			outl(tmp, gpiobase + 0xc);
		} else if (sku == 2) {
			u32 gpio30 = gpiobase + 0x1f0;

			tmp = inl(gpio30);
			tmp |= 1;
			outl(tmp, gpio30);

			tmp = inl(gpio30);
			tmp &= 0xfffffffb;
			outl(tmp, gpio30);

			tmp = inl(gpio30);
			tmp &= 0x7fffffff;
			outl(tmp, gpio30);
		}
		tmp = inl(gpiobase + 0x60);
		tmp |= 0x40000000; /* GPIO30 will be reset by RSMRST# assertion only */
		outl(tmp, gpiobase + 0x60);

		pci_or_config32(PCH_LPC_DEV, 0xac, 0x100000);
		io_cf9 |= 0xe;
	} else if (v == 2) {
		wdt->wdt_f0(2);
		io_cf9 |= 0xe;
	} else if (v == 1) {
		io_cf9 |= 6;
	}
	wdt->wdt_f3();
	outb(io_cf9, 0xcf9);
	return 0;
}
