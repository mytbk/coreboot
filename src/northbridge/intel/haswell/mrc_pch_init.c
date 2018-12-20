#include <southbridge/intel/lynxpoint/pch.h>
#include <device/pci_ops.h>
#include "mrc_pch.h"
#include "mrc_sku.h"
#include "mrc_pch_init.h"

static void
do_update_iopb(uint8_t pch_rev, uint8_t sku_type, const u8 r410_bits[],
		const uint8_t sz0[], const iobp_upd_st *upd0[],
		const uint8_t sz1[], const iobp_upd_st *upd1[])
{
	int iobp_sz;
	const iobp_upd_st *iobp_upd_data;
	uint32_t rcba = pci_read_config32(PCH_LPC_DEV, 0xf0) & 0xfffffffe;

	if (pch_rev <= 3) {
		iobp_sz = sz0[pch_rev];
		iobp_upd_data = upd0[pch_rev];
	} else {
		iobp_sz = 0;
		iobp_upd_data = NULL;
	}
	for (int i = 0; i != iobp_sz; i++) {
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].address,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}

	if (pch_rev <= 6) {
		iobp_sz = sz1[pch_rev];
		iobp_upd_data = upd1[pch_rev];
	} else {
		iobp_sz = 0;
		iobp_upd_data = NULL;
	}
	for (int i = 0; i != iobp_sz; i++) {
		uint32_t m_addr = iobp_upd_data[i].address & 0xfe00;
		if (sku_type == 2) {
			if (m_addr == 0x2000 && r410_bits[0])
				continue;
			if (m_addr == 0x2200 && r410_bits[1])
				continue;
			if (m_addr == 0x2400 && r410_bits[2])
				continue;
			if (m_addr == 0x2600 && r410_bits[3])
				continue;
		} else if (sku_type == 1) {
			if (m_addr == 0x2000 && r410_bits[0])
				continue;
			if (m_addr == 0x2200 && r410_bits[1])
				continue;
		}
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].address,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}
}

void mrc_pch_init(void)
{
	uint32_t rcba;
	int sku_type;
	uint16_t pch_did;
	uint32_t tmp;
	uint8_t pch_rev;
	uint8_t reg_410;
	uint8_t r410_bits[4];

	sku_type = mrc_sku_type ();
	rcba = pci_read_config32(PCH_LPC_DEV, 0xf0) & 0xfffffffe;
	pch_did = pci_read_config16(PCH_LPC_DEV, 2);
	uint8_t pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
	uint8_t al = ((pcs & 0xf) != 0) ? 1 : 0;

	if (sku_type == 1) {
		pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
		uint8_t cl = pcs & 0x30;
		if (cl == 0 && al != 1) {
			pci_update_config8(PCI_DEV(0, 0x1f, 2), 0x90, 0x1f, 0x60);
		} else {
			mrc_pch_iobp_read (rcba, 0xea000aac, &tmp);
			return;
		}
	} else {
		if (al == 1)
			return;
		if (sku_type == 2) {
			pci_update_config8(PCI_DEV(0, 0x1f, 2), 0x90, 0x3f, 0x40);
		}
	}

	pci_update_config32(PCI_DEV(0, 0x1f, 2), 0x94, 0xfffffe00, 0x183);
	pci_or_config16(PCI_DEV(0, 0x1f, 2), 0x92, 0x8000);

	reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410); // pin ownership?
	r410_bits[0] = reg_410 & 0x10;
	r410_bits[1] = reg_410 & 0x20;
	r410_bits[2] = reg_410 & 0x40;
	r410_bits[3] = reg_410 & 0x80;
	pch_rev = mrc_pch_revision();

	do_update_iopb(pch_rev, sku_type, r410_bits,
			iobp0_sz, iobp0_ref, iobp1_sz, iobp1_ref);

	if (sku_type == 2 || pch_did == 0x8c49 || pch_did == 0x8c4b
			|| pch_did == 0x8c4f || pch_did == 0x8c41) {
		/* mobile/LP platform */
		do_update_iopb(pch_rev, sku_type, r410_bits,
				iobp2_sz, iobp2_ref, iobp3_sz, iobp3_ref);
	} else {
		do_update_iopb(pch_rev, sku_type, r410_bits,
				iobp4_sz, iobp4_ref, iobp5_sz, iobp5_ref);
	}
//label_0:
#if 0
	uint16_t tmp = pch_did & 0xfffd;
	if (tmp != 0x8c44 && tmp != 0x8c4c) { /* 8c44, 8c46, 8c4c, 8c4e */
		if (pch_did == 0x8c5c || pch_did == 0x8c50 || 
				(pch_did & 0xfff7) == 0x8c42) /* 8c42, 8c4a */
			goto label_19;

		if (pch_did == 0x8c4f || pch_did == 0x8c49)
			goto label_19;

		if (pch_did == 0x8c41 || pch_did == 0x8c4b)
			goto label_19;

		if (pch_did - 0x9c41 > 6)
			goto label_24;
	}
	goto label_19;
#endif
	if (sku_type <= 2) {
//label_19:
		pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x400000);
	}
//label_24:
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x80000);
	pci_update_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0xffffe27f, 2);
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x100000);
	pci_update_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0xffffff9f, 0x20);
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x40000);

	if (sku_type == 1) {
		pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0xf);
		reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
		if ((reg_410 & 0x10) == 0) {
			pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0x10);
		}
		reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
		if ((reg_410 & 0x20) == 0) {
			pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0x20);
		}
		return;
	} else {
		if (sku_type == 2) {
			reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((reg_410 & 0x80) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 1);
			}
			reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((reg_410 & 0x40) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 2);
			}
			reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((reg_410 & 0x20) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 4);
			}
			reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((reg_410 & 0x10) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 8);
			}
		}
		return;
	}
}
