#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include "mrc_pei.h"
#include "pei_usb.h"
#include "mrc_sku.h"
#include "mrc_pch.h"
#include "mrc_utils.h"

static void xhci_setup_ss_route(void)
{
	u32 tmp;
	tmp = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xdc) & 0x3f;
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd8, 0xffffffc0, tmp); /* USB3 SuperSpeed Enable */
	tmp = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xd4) & 0x7fff;
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd0, 0xffff8000, tmp); /* USB2 Port Routing */
}

static int usb_xhci_port_count_usb3(void)
{
	int sku = mrc_sku_type();
	if (sku == 2) {
		/* LynxPoint-LP has 4 SS ports */
		return 4;
	}
	if (sku != 1)
		return 0;

	/* LynxPoint-H can have 0, 2, 4, or 6 SS ports */
	u32 fus = pci_read_config32(PCH_XHCI_DEV, XHCI_USB3FUS);
	fus >>= XHCI_USB3FUS_SS_SHIFT;
	fus &= XHCI_USB3FUS_SS_MASK;
	switch (fus) {
	case 3: return 0;
	case 2: return 2;
	case 1: return 4;
	case 0:
	default: return 6;
	}
}

void frag_usb_fffaecbe(void);
void frag_usb_fffaecbe(void)
{
	pch_iobp_update(0xe5007f04, 0, 0x4481);
	for (int i = 0; i < nb_usb2_ports(); i++)
		pch_iobp_update(0xe500410f + (i << 8), 0xfffffffe, 0);

	pch_iobp_update(0xe5007f14, ~0, 0x180000);
	if (mrc_sku_type() == 2)
		pch_iobp_update(0xe5007f02, 0xff3fffff, 0);
}

static const u32 ref_fffcb9f0[17] = {
	0x13000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x11000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x15000000,
	0x0f000000
};

void frag_usb_fffaed46(PEI_USB *upd, void *xbar);
void frag_usb_fffaed46(PEI_USB *upd, void *xbar)
{
#define XBAR_AND_OR(a, andv, orv) bar_update32(xbar, a, andv, orv)
#define XBAR_OR(a, orv) bar_or32(xbar, a, orv)
#define XBAR_RW32(addr, v) do { \
	read32(xbar + (addr)); \
	write32(xbar + (addr), v); \
} while(0);

	int sku = mrc_sku_type();
	int rev = mrc_pch_revision();
	u32 tmp1, tmp2;
	device_t dev = PCI_DEV(0, 0x14, 0);

	/* XBAR is e8100000
	printk(BIOS_DEBUG, "XBAR is %p.\n", xbar);
	*/

	if ((upd->xhci_resume_info[2] & 3) == 0)
		return;

	pci_write_config32(dev, 0x10, (u32)xbar);
	pci_or_config32(dev, 4, 6);

	tmp1 = 0;
	if (sku == 1) {
		tmp2 = (pci_read_config32(dev, 0xe0) & 0x18) - 8;
		if (tmp2 <= 0x10)
			tmp1 = ref_fffcb9f0[tmp2];
		else
			tmp1 = 0x15000000;

		XBAR_AND_OR(4, 0xffffff, tmp1);
	}
	XBAR_AND_OR(0xc, 0xff00, 0x200000a);
	XBAR_AND_OR(0x10, 0xfffff9df, 0x0600);
	if (sku == 1) {
		XBAR_AND_OR(0x8008, 0xfff7ffff, 0);
		XBAR_AND_OR(0x8058, 0xffeefeff, 0x110000);
	} else if (sku == 2) {
		XBAR_AND_OR(0x8058, 0xfffefeff, 0x10000);
	}

	XBAR_OR(0x8060, 0x2040000);
	XBAR_OR(0x8090, 0x4100);
	XBAR_OR(0x8094, 0xa04000);
	XBAR_AND_OR(0x80e0, 0xfffeffbf, 0x40);
	XBAR_AND_OR(0x80ec, 0xffff81ff, 0x0c00);
	XBAR_AND_OR(0x80f0, 0xffefffff, 0);
	if (sku == 2) {
		XBAR_OR(0x80fc, 0x2000000);
		XBAR_AND_OR(0x8110, 0xffeff6fb, 0x100800);
		read32(xbar + 0x8140);
		write32(xbar + 0x8140, 0xff00f03c);
		tmp2 = 0x200000;
		tmp1 = 0x2000;
	} else if (sku == 1) {
		XBAR_AND_OR(0x8110, 0xffeff7fb, 0x100800);
		read32(xbar + 0x8140);
		write32(xbar + 0x8140, 0xff03c132);
		tmp2 = 0x202000;
		tmp1 = 0;
	} else {
		tmp2 = 0;
	}
	XBAR_AND_OR(0x8154, ~tmp2, tmp1);
	XBAR_AND_OR(0x8154, 0xfffffff7, 0);
	if (sku == 2) {
		XBAR_OR(0x8164, 3);
		write32(xbar + 0x8174, 0x1400c0a);
		XBAR_RW32(0x817c, 0x33200a3);
		XBAR_RW32(0x8180, 0xcb0028);
		XBAR_RW32(0x8184, 0x64001e);
	}
	pci_or_config16(dev, 0x44, 0xc401);
	pci_or_config8(dev, 0x46, 0xf);
	if (rev > 3 && sku == 2) {
		XBAR_OR(0x8188, 0x5000000);
	} else if (rev != 0 && sku == 1) {
		XBAR_OR(0x8188, 0x1000000);
	}
}

void frag_usb_fffaeb10(PEI_USB *upd, void *ebar);
void frag_usb_fffaeb10(PEI_USB *upd, void *ebar)
{
	/* low power PCH (sku = 2) only has 00:1d.0,
	 * and normal PCH also has 00:1a.0
	 */
	int sku = mrc_sku_type();
	int nb_ehci_dev;
	const int ehci_dev[2] = { 0x1d, 0x1a };
	u16 cmd;
	u16 tmp16;
	uint8_t bar_was_set;
	u32 edx;

	if (sku == 1)
		nb_ehci_dev = 2;
	else if (sku == 2)
		nb_ehci_dev = 1;
	else
		return;

	for (int i = 0; i < nb_ehci_dev; i++) {
		device_t dev = PCI_DEV(0, ehci_dev[i], 0);

		if ((upd->xhci_resume_info[i] & 1) == 0) {
			pci_write_config32(dev, 0x10, 0); // MEM_BASE
			pci_write_config16(dev, 4, 0); // PCI_CMD
			continue;
		}
		if (upd->xhci_resume_info[2] & 0x10) {
			// reserved register?
			pci_update_config16(dev, 0x78, 0xfffc, 0);
		}

		if (pci_read_config32(dev, 0x10) == 0 &&
				(pci_read_config16(dev, 4) & 2) == 0) {
			pci_write_config32(dev, 0x10, (u32)ebar);
			bar_was_set = 0;
			cmd = 0;
		} else {
			ebar = (void*)pci_read_config32(dev, 0x10);
			cmd = pci_read_config16(dev, 4);
			bar_was_set = 1;
		}

		pci_or_config16(dev, 4, 6); /* Bus Master Enable, Memory Space Enable */
		if (!bar_was_set) {
			tmp16 = read16(ebar + 0x20);
			tmp16 |= 2; /* host controller reset */
			write16(ebar + 0x20, tmp16);
		}
		pci_or_config16(dev, 0x80, 1); /* ACCESS_CNTL */
		write32(ebar + 4, read32(ebar + 4) & 0xffff0fff);
		if (i != 0) {
			if (sku != 1 || i != 1 || (upd->v0 & 4) == 0) {
				edx = 2;
			} else {
				edx = 3;
			}
		} else {
			if ((upd->v0 & 2) == 0)
				edx = 2;
			else
				edx = 3;
		}

		u32 tmp = read32(ebar + 4);
		tmp &= 0xfffffff0;
		tmp |= edx;
		write32(ebar + 4, tmp);

		pci_update_config16(dev, 0x80, 0xfffe, 0);
		pci_or_config32(dev, 0x78, 4);
		pci_or_config32(dev, 0x7c, 0x4080);
		pci_update_config32(dev, 0x8c, 0xfbfff4ff, 0x20400);
		if (bar_was_set) {
			pci_write_config16(dev, 4, cmd);
		} else {
			pci_update_config16(dev, 4, 0xfff9, 0);
			pci_write_config32(dev, 0x10, 0);
		}
	}
}

static void frag_usb_loop1(void *ebx, const u32 *offsets, int count)
{
	for (int i = 0; i < count; i++) {
		void *addr = ebx + offsets[i];
		u32 tmp = read32(addr);
		tmp &= 0x7ffffffd;
		tmp |= 0x80000000;
		write32(addr, tmp);
	}
}

static void frag_usb_loop4(void *ebx, const u32 *offsets, int count)
{
	u32 tmp;
	for (int i = 0; i < 10; i++) {
		tmp = 0;
		for (int j = 0; j < count; j++) {
			void *addr = ebx + offsets[j];
			tmp |= read32(addr);
		}
		usleep(10000);
		if ((tmp & 0x10) == 0)
			return;
	}
}

static void frag_usb_loop2(void *ebx, const u32 *offsets, int count, int one_more_loop)
{
	if (one_more_loop != 0)
		one_more_loop = 1;

	for (int i = 0; i < count + one_more_loop; i++) {
		void *addr = ebx + offsets[i];
		u32 tmp = read32(addr);
		tmp &= 0xff01fffd;
		tmp |= 0xfe0000;
		write32(addr, tmp);
	}
}

static void frag_usb_loop3(void *ebx, const u32 *offsets, int count)
{
	for (int i = 0; i < count; i++) {
		void *addr = ebx + offsets[i];
		u32 tmp = read32(addr);
		if ((tmp & 1) == 0)
			continue;
		tmp &= 0xffffffed;
		tmp |= 0x10;
		write32(addr, tmp);
	}
}

void set_ehci_oc_map(PEI_USB *upd);
void set_ehci_oc_map(PEI_USB *upd)
{
	int sku = mrc_sku_type();
	int nusb = nb_usb2_ports();
	u32 ocmap1 = 0;
	u32 ocmap2 = 0;

	for (int i = 0; i < nusb; i++) {
		u32 oc = upd->ehci_oc[i];
		if (oc == 8)
			continue;
		if (i <= 7) {
			if (oc > 3)
				continue;
			ocmap1 |= (1 << (oc * 8 + i));
		} else {
			if (sku != 1)
				continue;
			if (oc >= 4 && oc <= 7) {
				ocmap2 |= (1 << ((oc - 4) * 8 + (i - 8)));
			}
		}
	}
	if (upd->xhci_resume_info[0] & 1) {
		pci_write_config32(PCI_DEV(0, 0x1d, 0), 0x74, ocmap1);
	}
	if (sku == 1 && (upd->xhci_resume_info[1] & 1)) {
		pci_write_config32(PCI_DEV(0, 0x1a, 0), 0x74, ocmap2);
	}
}

/* from loc_fffaf684 to loc_fffaf75b */
void set_usb_overcurrent(PEI_USB *upd);
void set_usb_overcurrent(PEI_USB *upd)
{
	device_t dev = PCI_DEV(0, 0x14, 0);

	u32 u2ocm1 = 0;
	u32 u2ocm2 = 0;
	u32 u3ocm2 = 0;
	u32 u3ocm1 = 0;

	for (int i = 0; i < nb_usb2_ports(); i++) {
		u32 oc = upd->ehci_oc[i];
		if (oc == 8) continue;
		if (i > 7) {
			if (oc >= 4 && oc <= 7) {
				u2ocm2 |= (1 << ((oc - 4) * 8 + (i - 8)));
			}
		} else {
			if (oc <= 3) {
				u2ocm1 |= (1 << (oc * 8 + i));
			}
		}
	}

	int nb_xxx;
	int sku = mrc_sku_type();
	if (sku == 1)
		nb_xxx = 6;
	else if (sku == 2)
		nb_xxx = 4;
	else
		nb_xxx = 0;

	for (int i = 0; i < nb_xxx; i++) {
		u32 oc = upd->xhci_oc[i];
		if (oc == 8) continue;
		if (oc <= 3) {
			u3ocm1 |= (1 << (oc * 8 + i));
		} else {
			u3ocm2 |= (1 << ((oc - 4) * 8 + i));
		}
	}

	/* U2OCM1: XHCI USB2 Overcurrent Mapping Register1
	 * OC 0~3 */
	pci_write_config32(dev, 0xc0, u2ocm1);
	/* U3OCM1: XHCI USB3 Overcurrent Mapping Register1
	 * OC 0~3 */
	pci_write_config32(dev, 0xc8, u3ocm1);

	if (sku == 1) {
		/* U2OCM2: OC 4~7 */
		pci_write_config32(dev, 0xc4, u2ocm2);
		/* U3OCM2: OC 4~7 */
		pci_write_config32(dev, 0xcc, u3ocm2);
	}
}

void frag_usb_fffaf4b1(PEI_USB *upd, int count);
void frag_usb_fffaf4b1(PEI_USB *upd, int count)
{
	u32 v = 0;
	for (int i = 0; i < count; i++) {
		if (upd->xhci_resume_info[3 + i] == 1) {
			v |= (1 << i);
		}
	}
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd0, 0xffff8000, v);
}

void frag_usb_fffaf555(PEI_USB *upd, int count);
void frag_usb_fffaf555(PEI_USB *upd, int count)
{
	u32 v = 0;
	for (int i = 0; i < count; i++) {
		if (upd->xhci_resume_info[0x11 + i] == 1) {
			v |= (1 << i);
		}
	}
	pci_update_config32(PCI_DEV(0, 0x14, 0), 0xd8, 0xffffffc0, v);
}

void frag_usb_fffaf75b(PEI_USB *upd);
void frag_usb_fffaf75b(PEI_USB *upd)
{
	for (int i = 0; i < nb_usb2_ports(); i++) {
		u32 a1 = (u32)(upd->ehci_settings[i].f4 & 7) << 8;
		u32 a2 = (u32)(upd->ehci_settings[i].f5 & 7) << 11;
		pch_iobp_update(a1 | a2, (0xe50041 + i) << 8, 0xffff80ff);
	}
}

void frag_usb_fffaf7d8(PEI_USB *upd);
void frag_usb_fffaf7d8(PEI_USB *upd)
{
	int sku = mrc_sku_type();

	for (int i = 0; i < nb_usb2_ports(); i++) {
		if (i <= 7 && (upd->xhci_resume_info[0] & 1)) {
			if (upd->ehci_settings[i].enable & 1) {
				pci_or_config8(PCI_DEV(0, 0x1d, 0), 0x64, (1 << i));
			} else {
				pci_update_config8(PCI_DEV(0, 0x1d, 0), 0x64, (~(1 << i)), 0);
			}
		}
		/* low power PCH doesn't have 00:1a.0 */
		if (sku != 1)
			continue;

		if (i > 0xd) continue;
		if ((upd->xhci_resume_info[1] & 1) == 0)
			continue;

		if (upd->ehci_settings[i].enable & 1) {
			pci_or_config8(PCI_DEV(0, 0x1a, 0), 0x64, 1 << (i - 8));
		} else {
			pci_update_config8(PCI_DEV(0, 0x1a, 0), 0x64, ~(1 << (i - 8)), 0);
		}
	}
}

static const u32 shift_tab[16] = {
	0x00000000,
	0x00000001,
	0x00000002,
	0x00000003,
	0x00000008,
	0x00000009,
	0x0000000c,
	0x0000000d,
	0x00000004,
	0x00000005,
	0x00000006,
	0x00000007,
	0x0000000a,
	0x0000000b,
	0x0000000c,
	0x0000000d
};

void set_usb_pdo(PEI_USB *upd, u8 ppiv);
void set_usb_pdo(PEI_USB *upd, u8 ppiv)
{
	int sku = mrc_sku_type();
	int nusb = nb_usb2_ports();

	u32 usb2pdo = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xe4) & 0x7fff;

	for (int i = 0; i < nusb; i++) {
		u32 shifts;
		if (sku == 1) {
			shifts = shift_tab[i];
		} else {
			shifts = i;
		}
		/* if usb2 port is enabled, prevents it from
		 * reporting a device connection to the xHC,
		 * otherwise allows the reporting
		 */
		if (upd->ehci_settings[i].enable & 1) {
			usb2pdo |= (1 << shifts);
		} else {
			usb2pdo &= ~(1 << shifts);
		}
	}

	u32 usb3pdo = pci_read_config32(PCI_DEV(0, 0x14, 0), 0xe8) & 0x3f;
	int nb_xxx;
	if (sku == 1)
		nb_xxx = 6;
	else if (sku == 2)
		nb_xxx = 4;
	else
		nb_xxx = 0;

	/* ppiv is 4
	printk(BIOS_DEBUG, "%s: ppiv is %d.\n", __func__, ppiv);
	*/

	for (int i = 0; i < nb_xxx; i++) {
		if (ppiv > 2) {
			if ((upd->xhci_en[i] & 1) == 0) {
				usb3pdo |= (1 << i);
			} else {
				usb3pdo &= ~(1 << i);
			}
		} else {
			if ((upd->ehci_settings[i].enable & 1) == 0) {
				usb3pdo |= (1 << i);
			} else {
				usb3pdo &= ~(1 << i);
			}
		}
	}

	pci_write_config32(PCI_DEV(0, 0x14, 0), 0xe4, usb2pdo);
	pci_write_config32(PCI_DEV(0, 0x14, 0), 0xe8, usb3pdo);
}

static const u32 ebar_o1[15] = {
	0x00000480,
	0x00000490,
	0x000004a0,
	0x000004b0,
	0x000004c0,
	0x000004d0,
	0x000004e0,
	0x000004f0,
	0x00000500,
	0x00000510,
	0x00000520,
	0x00000530,
	0x00000540,
	0x00000550,
	0x00000560
};

static const u32 ebar_o2[9] = {
	0x00000480,
	0x00000490,
	0x000004a0,
	0x000004b0,
	0x000004c0,
	0x000004d0,
	0x000004e0,
	0x000004f0,
	0x00000500
};

static const u32 xbar_o1[6] = {
	0x00000570,
	0x00000580,
	0x00000590,
	0x000005a0,
	0x000005b0,
	0x000005c0
};

static const u32 xbar_o2[4] = {
	0x00000510,
	0x00000520,
	0x00000530,
	0x00000540
};

static const u32 * const ebar_offsets[2] = { ebar_o1, ebar_o2 };
static const u32 * const xbar_offsets[2] = { xbar_o1, xbar_o2 };

int mrc_init_usb(const EFI_PEI_SERVICES **pps);
int mrc_init_usb(const EFI_PEI_SERVICES **pps)
{
	EFI_USB_PPI *usbppi;
	int res;
	uint32_t rcba_3418;
	uint32_t sku_type;
	int bootmode;
	extern EFI_GUID ref_fffcc988;

	res = (*pps)->LocatePpi(pps, &ref_fffcc988, 0, NULL, (void*)&usbppi);
	if (res != 0)
		return res;

	u8 vv0 = usbppi->v0;
	void * xbar = (void*)usbppi->ehci_bar1;
	void * ebar0 = (void*)usbppi->ehci_bar0;
	PEI_USB *upd = usbppi->usb_pei_data;

	if (upd == NULL)
		return 0x80000002;

	rcba_3418 = RCBA32(0x3418);
	sku_type = mrc_sku_type();

	u16 pmbase = pci_read_config16(PCH_LPC_DEV, PMBASE);

	if ((upd->xhci_resume_info[0] & 1) == 0)
		rcba_3418 |= 0x8000;

	if (sku_type == 1) {
		if ((upd->xhci_resume_info[1] & 1) == 0)
			rcba_3418 |= 0x2000;
	}

	if ((upd->xhci_resume_info[2] & 3) == 0)
		rcba_3418 |= 0x08000000;

	frag_usb_fffaeb10(upd, ebar0);
	frag_usb_fffaecbe();
	frag_usb_fffaed46(upd, xbar);

	int i = sku_type - 1;
	const u32 *ebar_offset, *xbar_offset;
	if (i == 0 || i == 1) {
		ebar_offset = ebar_offsets[i];
		xbar_offset = xbar_offsets[i];
	} else {
		ebar_offset = NULL;
		xbar_offset = NULL;
	}
	if ((upd->xhci_resume_info[2] & 3) == 0)
		goto begin_oc_settings;

	int xhci_usb3_count = usb_xhci_port_count_usb3(); // xhci_usb3_count
	u32 usb3_mask = (1 << xhci_usb3_count) - 1; // eax
	int xhci_usb2_count;
	u32 usb2_mask;
	u32 fus;
	int flag;

	if (sku_type == 1) {
		fus = pci_read_config32(PCH_XHCI_DEV, XHCI_USB3FUS) & 6;
		if (fus == 4) {
			xhci_usb2_count = 10;
			usb2_mask = 0xfff;
		} else if (fus == 6) {
			xhci_usb2_count = 8;
			usb2_mask = 0xff;
		} else {
			xhci_usb2_count = (fus != 2)? 14:12;
			usb2_mask = 0x3fff;
		}
		fus = pci_read_config32(PCH_XHCI_DEV, XHCI_USB3FUS) & 0x20;
		if (fus != 0) {
			flag = 0;
		} else {
			usb2_mask |= 0x4000;
			flag = 1;
		}
	} else if (sku_type == 2) {
		fus = pci_read_config32(PCH_XHCI_DEV, XHCI_USB3FUS) & 0x20;
		if (fus == 0) {
			flag = 1;
			xhci_usb2_count = 8;
			usb2_mask = 0x1ff;
		} else {
			xhci_usb2_count = 8;
			usb2_mask = 0xff;
			flag = 0;
		}
	} else {
		xhci_usb2_count = 0;
		usb2_mask = 0;
		flag = 0;
	}

	/* xHC USB2 Port Routing Mask */
	pci_update_config32(PCH_XHCI_DEV, 0xd4, 0xffff8000, usb2_mask);
	/* USB3 Routing Mask */
	pci_update_config32(PCH_XHCI_DEV, 0xdc, 0xffffffc0, usb3_mask);

	PeiServiceGetBootMode(&bootmode);
	if (bootmode == 0x11) {
		xhci_setup_ss_route();
		goto begin_oc_settings;
	}

	u16 pmcon2 = pci_read_config16(PCH_LPC_DEV, 0xa2); /* LPC GEN_PMCON_2 */
	if (pmcon2 & 0x20) {
		u32 pmir = pci_read_config32(PCH_LPC_DEV, 0xac); /* LPC PMIR */
		if (pmir & 0x10000) {
			xhci_setup_ss_route();
		}
	}

	pci_update_config32(PCH_LPC_DEV, 0xac, 0xfffeffff, 0);

	u8 al = upd->xhci_resume_info[2];
	u8 dl;
	if (al & 4) {
		dl = ((al & 7) == 6)? 1:0;
	} else {
		dl = 1;
	}

	al &= 7;
	if (al == 5) {
		pmcon2 = pci_read_config16(PCH_LPC_DEV, 0xa2);
		if ((pmcon2 & 0x20) != 0) {
			frag_usb_loop1(xbar, xbar_offset, xhci_usb3_count);
			frag_usb_loop4(xbar, xbar_offset, xhci_usb3_count);
		}
		if (xhci_usb3_count != 0) {
			xhci_setup_ss_route();
		}
	} else if (xhci_usb3_count != 0) {
		if (dl == 1 &&
				(pci_read_config32(PCH_XHCI_DEV, 0xd0) != 0 ||
				 pci_read_config32(PCH_XHCI_DEV, 0xd8) != 0)) {
			frag_usb_loop3(xbar, ebar_offset, xhci_usb2_count);
			frag_usb_loop4(xbar, ebar_offset, xhci_usb2_count);

			pci_update_config32(PCH_XHCI_DEV, 0xd0, 0xffff8000, 0);
			frag_usb_loop2(xbar, ebar_offset, xhci_usb2_count, flag);
			frag_usb_loop1(xbar, xbar_offset, xhci_usb3_count);
			pci_update_config32(PCH_XHCI_DEV, 0xd8, 0xffffffc0, 0);
			frag_usb_loop4(xbar, xbar_offset, xhci_usb3_count);
			frag_usb_loop2(xbar, xbar_offset, xhci_usb3_count, 0);

			u32 tmp = read32(xbar + 0x80) | 1;
			write32(xbar + 0x80, tmp);
			tmp = read32(xbar + 0x80) & 0xfffffffe;
			write32(xbar + 0x80, tmp);
		} else {
			pmcon2 = pci_read_config16(PCH_LPC_DEV, 0xa2);
			if ((pmcon2 & 0x20) != 0) {
				frag_usb_loop1(xbar, xbar_offset, xhci_usb3_count);
				frag_usb_loop4(xbar, xbar_offset, xhci_usb3_count);
			}
		}
	}

	if ((upd->xhci_resume_info[2] & 0x10) != 0) {
		frag_usb_loop3(xbar, ebar_offset, xhci_usb2_count);
		frag_usb_loop4(xbar, ebar_offset, xhci_usb2_count);
		frag_usb_fffaf4b1(upd, xhci_usb2_count);
		frag_usb_loop2(xbar, ebar_offset, xhci_usb2_count, flag);
		frag_usb_loop1(xbar, xbar_offset, xhci_usb3_count);
		frag_usb_fffaf555(upd, xhci_usb3_count);
		frag_usb_loop4(xbar, xbar_offset, xhci_usb3_count);
		frag_usb_loop2(xbar, xbar_offset, xhci_usb3_count, 0);

		u32 tmp = read32(xbar + 0x80) | 1;
		write32(xbar + 0x80, tmp);
		tmp = read32(xbar + 0x80) & 0xfffffffe;
		write32(xbar + 0x80, tmp);
	}

begin_oc_settings:
	set_ehci_oc_map(upd);

	if (upd->xhci_resume_info[2] & 3)
		set_usb_overcurrent(upd);

	frag_usb_fffaf75b(upd);

	if ((upd->v0 & 1) != 0) {
		u16 pm3c = (pmbase & 0xfffc) + 0x3c;
		u16 reg3c = inw(pm3c);
		outw(reg3c | 2, pm3c);

		frag_usb_fffaf7d8(upd);

		if ((upd->xhci_resume_info[2] & 3) != 0) {
			set_usb_pdo(upd, vv0);
		}

		outw(reg3c & 0xfffd, pm3c);
	}
	if ((upd->v0 & 2) != 0 && (upd->xhci_resume_info[0] & 1) != 0) {
		pci_or_config16(PCI_DEV(0, 0x1d, 0), 0x7a, 0x0100);
	}
	if (sku_type == 1 && (upd->v0 & 4) != 0
			&& (upd->xhci_resume_info[1] & 1) != 0) {
		pci_or_config16(PCI_DEV(0, 0x1a, 0), 0x7a, 0x0100);
	}
	if ((upd->xhci_resume_info[2] & 3) != 0) {
		pci_update_config16(PCH_XHCI_DEV, 4, 0xfff9, 0);
		pci_write_config32(PCH_XHCI_DEV, 0x10, 0);
	}
	RCBA32(0x3418) = rcba_3418;
	rcba_3418 = RCBA32(0x3418); /* read it */
	return 0;
}
