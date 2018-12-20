#include <stdint.h>

void mrc_pch_init()
{
	int32_t pciexbar;
	int32_t rcba;
	int32_t sku_type;
	int32_t local_2fh;
	int32_t local_2eh;
	int32_t pch_did;
	int32_t local_2ah;
	int32_t local_1ch;
	int32_t local_ch;
       	u8 pch_rev;
	int iobp_sz;
	const iobp_upd *iobp_upd_data;
	uint8_t reg_410;
	uint8_t r410_bits[4];

	sku_type = mrc_sku_type ();
	rcba = get_rcba();
	pch_did = pci_read_config16(PCH_LPC_DEV, 2);
	u8 pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
	al = ((pcs & 0xf) != 0) ? 1 : 0;

	if (sku_type == 1) {
		pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
		cl = pcs & 0x30;
		if (cl == 0 && al != 1) {
			u8 al = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x90);
			eax &= 0x1f;
			eax |= 0x60;
			pci_write_config8(PCI_DEV(0, 0x1f, 2), 0x90, al);
		} else {
			mrc_pch_iobp_read (rcba, 0xea000aac, &local_1ch);
			return;
		}
	} else {
		if (al == 1)
			return;
		if (sku_type == 2) {
			al = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x90);
			eax &= 0x3f;
			eax |= 0x40;
			pci_write_config8(PCI_DEV(0, 0x1f, 2), 0x90, al);
		}
	}
	local_1ch = 0xfffffe00;

	eax = pci_read_config32(PCI_DEV(0, 0x1f, 2), 0x94);
	eax &= 0xfffffe00;
	eax |= 0x183;
	pci_read_config32(PCI_DEV(0, 0x1f, 2), 0x94, eax);

	ax = pci_read_config16(PCI_DEV(0, 0x1f, 2), 0x92);
	ax |= 0x8000;
	pci_write_config16(PCI_DEV(0, 0x1f, 2), 0x92, ax);

	reg_410 = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410); // pin ownership?
	r410_bits[0] = reg_410 & 0x10;
	r410_bits[1] = reg_410 & 0x20;
	r410_bits[2] = reg_410 & 0x40;
	r410_bits[3] = reg_410 & 0x80;
	pch_rev = mrc_pch_revision();

	if (pch_rev <= 3) {
		iobp_sz = iobp0_sz[pch_rev];
		iobp_upd_data = iobp0_ref[pch_rev];
	} else {
		iobp_sz = 0;
		iobp_upd_data = NULL;
	}
	for (int i = 0; i != iobp_sz; i++) {
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}

	if (pch_rev <= 6) {
		iobp_sz = iobp1_sz[pch_rev];
		iobp_upd_data = iobp1_ref[pch_rev];
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
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}

	dl = (pch_did == 0x8c4f || pch_did == 0x8c49);
	local_2fh = dl;
	if (dl == 0) {
		if (pch_did == 0x8c41 || pch_did == 0x8c4b) {
			goto label_12;
		} else if (pch_did - 0x9c41 > 6) {
			goto label_13; // loc_fffc7fe1
		}
	}
label_12:
	if (pch_rev <= 3) {
		iobp_sz = iobp2_sz[pch_rev];
		iobp_upd_data = iobp2_ref[pch_rev];
	} else {
		iobp_sz = 0;
		iobp_upd_data = NULL;
	}
	for (int i = 0; i != iobp_sz; i++) {
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}
	if (pch_rev <= 6) {
		iobp_sz = iobp3_sz[pch_rev];
		iobp_upd_data = iobp3_ref[pch_rev];
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
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}
label_0:
	eax = pch_did;
	eax &= 0xfffffffd;
	if (ax != 0x8c44) {
		goto label_18; // 0xfffc80e6
	}
	goto label_19; // 0xfffc8137
label_13: // loc_fffc7fe1:
	if (pch_rev <= 3) {
		iobp_sz = iobp4_sz[pch_rev];
		iobp_upd_data = iobp4_ref[pch_rev];
	} else {
		iobp_sz = 0;
		iobp_upd_data = NULL;
	}
	for (int i = 0; i != iobp_sz; i++) {
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}
	if (pch_rev <= 6) {
		iobp_sz = iobp5_sz[pch_rev];
		iobp_upd_data = iobp5_ref[pch_rev];
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
		mrc_pch_iobp_update (rcba, iobp_upd_data[i].addr,
				iobp_upd_data[i].andv, iobp_upd_data[i].orv);
	}
	goto label_0; // loc_fffc7fcc
label_18:
	if (ax != 0x8c4c) {
		dl = (pch_did == 0x8c5c) ? 1 : 0;
		al = (pch_did == 0x8c50) ? 1 : 0;
		dl |= al;
		if (dl != 0) {
			goto label_19;
		}
		eax = pch_did;
		eax &= 0xfffffff7;
		if (ax == 0x8c42) {
			goto label_19;
		}
		if (local_2fh != 0) {
			goto label_19;
		}
		dl = (pch_did == 0x8c41) ? 1 : 0;
		al = (pch_did == 0x8c4b) ? 1 : 0;
		dl |= al;
		if (dl != 0) {
			goto label_19;
		}
		eax = pch_did;
		ax += 0x63bf;
		if (ax > 6) {
			goto label_24;
		}
	}
label_19:
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x400000);
label_24:
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x80000);
	local_1ch = 0xffffe27f;
	pci_update_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0xffffe27f, 2);
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x100000);
	pci_update_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0xffffff9f, 0x20);
	pci_or_config32(PCI_DEV(0, 0x1f, 2), 0x98, 0x40000);

	if (sku_type == 1) {
		pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0xf);
		al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
		if ((al & 0x10) == 0) {
			pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0x10);
		}
		al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
		if ((al & 0x20) == 0) {
			pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 0x20);
		}
		return;
	} else {
		if (sku_type == 2) {
			al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((al & 0x80) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 1);
			}
			al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((al & 0x40) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 2);
			}
			al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((al & 0x20) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 4);
			}
			al = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410);
			if ((al & 0x10) == 0) {
				pci_or_config8(PCI_DEV(0, 0x1f, 2), 0x92, 8);
			}
		}
		return;
	}
}
