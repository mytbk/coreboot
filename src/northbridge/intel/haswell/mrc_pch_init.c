#include <stdint.h>

void mrc_pch_init()
{
	int32_t pciexbar;
	int32_t rcba;
	int32_t sku_type;
	int32_t local_2fh;
	int32_t local_2eh;
	int32_t local_2dh;
	int32_t pch_did;
	int32_t local_2ah;
	int32_t local_1ch;
	int32_t local_ch;

	sku_type = mrc_sku_type ();
	rcba = get_rcba();
	pch_did = pci_read_config16(PCH_LPC_DEV, 2);
	u8 pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
	al = ((pcs & 0xf) != 0) ? 1 : 0;
	if (sku_type != 1) {
		al--;
		if (al != 0) {
			goto label_3; // loc_fffc7d33
		}
		return eax;
	}
	pcs = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x92);
	cl = pcs & 0x30;
	if (cl == 0) {
		al--;
		if (al != 0) {
			u8 al = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x90);
			eax &= 0x1f;
			eax |= 0x60;
			goto label_7;
		}
	}
	mrc_pch_iobp_read (rcba, 0xea000aac, &local_1ch);
	return;
label_3:
	if (sku_type == 2) {
		al = pci_read_config8(PCI_DEV(0, 0x1f, 2), 0x90);
		eax &= 0x3f;
		eax |= 0x40;
label_7:
		pci_write_config8(PCI_DEV(0, 0x1f, 2), 0x90, al);
	}
	local_1ch = 0xfffffe00;

	eax = pci_read_config32(PCI_DEV(0, 0x1f, 2), 0x94);
	eax &= 0xfffffe00;
	eax |= 0x183;
	pci_read_config32(PCI_DEV(0, 0x1f, 2), 0x94, eax);

	ax = pci_read_config16(PCI_DEV(0, 0x1f, 2), 0x92);
	ax |= 0x8000;
	pci_write_config16(PCI_DEV(0, 0x1f, 2), 0x92, ax);

	local_2dh = pci_read_config8(PCI_DEV(0, 0x1c, 0), 0x410); // pin ownership?
	if (mrc_pch_revision() <= 3) {
		u8 sz = ref_fffcc32c[eax]; /* size */
		iobp_upd *upd_data = ref_fffcc330[eax]; /* data */
	} else {
		sz = 0;
		upd_data = 0;
	}
	i = 0;
	for (i = 0; i != sz; i++) {
		mrc_pch_iobp_update (rcba, upd_data[i].addr, upd_data[i].andv, upd_data[i].orv);
	}
	eax = mrc_pch_revision ();
	if (eax <= 6) {
		edx = *(eax+ ref_fffcc340);
		ebx = *(eax*4 + ref_fffcc348);
	} else {
		ebx = 0;
		edx = 0;
	}
	local_2eh = local_2dh & 0x10;
	edi = ebx + edx * 12;
	local_2ah = local_2dh & 0x20;
	for (; ebx != edi; ebx += 12) {
		if (sku_type == 2) {
			eax = *((int32_t*) ebx) & 0xfe00;
			if (eax == 0x2000) {
				if (local_2eh != 0) {
					continue;
				}
			}
			if (eax == 0x2200) {
				if (local_2ah != 0) {
					continue;
				}
			}
			if (eax == 0x2400) {
				if ((local_2dh & 0x40) != 0) {
					continue;
				}
			}
			if (eax == 0x2600) {
				if (local_2dh & 0x80) {
					continue;
				}
			}
		} else if (sku_type == 1) { /* sku_type != 2 */
			eax = *((int32_t*) ebx) & 0xfe00;
			if (eax == 0x2000) {
				if (local_2eh != 0) {
					continue;
				}
			}
			if (eax == 0x2200) {
				if (local_2ah != 0) {
					continue;
				}
			}
		}
		ecx = *((int32_t*) (ebx + 4));
		edx = *((int32_t*) ebx);
		mrc_pch_iobp_update(rcba, edx, ecx, [ebx+8]);
	}
	dl = (pch_did == 0x8c4f) ? 1 : 0;
	al = (pch_did == 0x8c49) ? 1 : 0;
	dl |= al;
	local_2fh = dl;
	if (dl == 0) {
		dl = (pch_did == 0x8c41) ? 1 : 0;
		al = (pch_did == 0x8c4b) ? 1 : 0;
		dl |= al;
		if (dl != 0) {
			goto label_12;
		}
		eax = pch_did;
		ax += 0x63bf;
		if (ax > 6) {
			goto label_13; // loc_fffc7fe1
		}
	}
label_12:
	eax = mrc_pch_revision ();
	if (eax <= 3) {
		edi = *((uint8_t*) (eax + ref_fffcc364));
		ebx = *((int32_t*) (eax*4 + ref_fffcc368));
	} else {
		ebx = 0;
		edi = 0;
	}
	local_2ah = 0;
	while (local_2ah != di) {
		ecx = *((int32_t*) (ebx + 4));
		eax = rcba;
		edx = *((int32_t*) ebx);
		mrc_pch_iobp_update (eax, edx, ecx, [ebx+8]);
		ebx += 0xc;
		local_2ah++;
	}
	eax = mrc_pch_revision ();
	if (eax <= 6) {
		edx = *((uint8_t*) (eax + ref_fffcc378));
		ebx = *((int32_t*) (eax*4 + ref_fffcc380));
	} else {
		ebx = 0;
		edx = 0;
	}
	edx *= 0xc;
	al = local_2dh;
	eax &= 0x10;
	local_2eh = al;
	edi = ebx + edx;
	dl = local_2dh;
	edx &= 0x20;
	local_2ah = dl;
	for (; ebx != edi; ebx += 12) {
		if (sku_type == 2) {
			eax = *((int32_t*) ebx) & 0xfe00;
			if (eax == 0x2000 && (local_2dh & 0x10))
				continue;

			if (eax == 0x2200 && (local_2dh & 0x20))
				continue;

			if (eax == 0x2400 && (local_2dh & 0x40))
				continue;

			if (eax == 0x2600 && (local_2dh & 0x80))
				continue;
		} else if (sku_type == 1) {
			eax = *((int32_t*) ebx) & 0xfe00;
			if (eax == 0x2000 && (local_2dh & 0x10))
				continue;

			if (eax == 0x2200 && (local_2dh & 0x20))
				continue;
		}
label_16:
		ecx = *((int32_t*) (ebx + 4));
		eax = rcba;
		edx = *((int32_t*) ebx);
		mrc_pch_iobp_update (rcba, edx, ecx, [ebx+8]);
	}
label_0:
	eax = pch_did;
	eax &= 0xfffffffd;
	if (ax != 0x8c44) {
		goto label_18; // 0xfffc80e6
	}
	goto label_19; // 0xfffc8137
label_13: // loc_fffc7fe1:
	eax = mrc_pch_revision ();
	if (eax <= 3) {
		edi = *((uint8_t*) (eax + ref_fffcc39c));
		ebx = *((int32_t*) (eax*4 + ref_fffcc3a0));
	} else {
		ebx = 0;
		edi = 0;
	}
	local_2ah = 0;
	while (local_2ah != di) {
		ecx = *((int32_t*) (ebx + 4));
		eax = rcba;
		edx = *((int32_t*) ebx);
		mrc_pch_iobp_update ();
		ebx += 0xc;
		local_2ah++;
	}
	eax = mrc_pch_revision ();
	if (eax <= 6) {
		edx = *((uint8_t*) (eax + ref_fffcc3b0));
		ebx = *((int32_t*) (eax*4 + ref_fffcc3b8));
	} else {
		ebx = 0;
		edx = 0;
	}
	edx *= 0xc;
	al = local_2dh;
	eax &= 0x10;
	local_2eh = al;
	edi = ebx + edx;
	dl = local_2dh;
	edx &= 0x20;
	local_2ah = dl;
	for (ebx; ebx != edi; ebx += 12) {
		if (sku_type == 2) {
			eax = *((int32_t*) ebx);
			eax &= 0xfe00;
			if (eax == 0x2000) {
				if (local_2eh != 0)
					continue; // loc_fffc80da:
				update; //loc_fffc80c4
			}
			if (eax == 0x2200) {
				if (local_2ah != 0)
					continue;
				update;
			}
			if (eax == 0x2400) {
				if ((local_2dh & 0x40) != 0) {
					continue;
				}
				update;
			}
			if (eax == 0x2600) {
				if (local_2dh & 0x80) {
					update;
				}
				continue;
			}
			update;
		} else {
			if (sku_type != 1) {
				goto label_22;
			}
			eax = *((int32_t*) ebx);
			eax &= 0xfe00;
			if (eax == 0x2000) {
				if (local_2eh != 0) {
					continue;
				}
				goto label_22;
			}
			if (eax == 0x2200) {
				if (local_2ah != 0) {
					continue;
				}
			}
		}
label_22:
		ecx = *((int32_t*) (ebx + 4));
		eax = rcba;
		edx = *((int32_t*) ebx);
		ax = mrc_pch_iobp_update ();
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
	eax = *((int32_t*) (esi + 0xfa098));
	eax |= 0x400000;
	*((int32_t*) (esi + 0xfa098)) = eax;
label_24:
	eax = *((int32_t*) (esi + 0xfa098));
	eax |= 0x80000;
	*((int32_t*) (esi + 0xfa098)) = eax;
	local_1ch = 0xffffe27f;
	eax = *((int32_t*) (esi + 0xfa098));
	eax &= 0xffffe27f;
	ah |= 2;
	*((int32_t*) (esi + 0xfa098)) = eax;
	eax = *((int32_t*) (esi + 0xfa098));
	eax |= 0x100000;
	*((int32_t*) (esi + 0xfa098)) = eax;
	eax = *((int32_t*) (esi + 0xfa098));
	eax &= 0xffffff9f;
	eax |= 0x20;
	*((int32_t*) (esi + 0xfa098)) = eax;
	eax = *((int32_t*) (esi + 0xfa098));
	eax |= 0x40000;
	*((int32_t*) (esi + 0xfa098)) = eax;
	if (sku_type == 1) {
		al = *((int8_t*) (esi + 0xfa092));
		eax |= 0xf;
		*((int8_t*) (esi + 0xfa092)) = al;
		edx = pciexbar;
		al = *((int8_t*) (edx + 0xe0410));
		if ((al & 0x10) != 0) {
			goto label_25; // loc_fffc8255
		}
	} else {
		if (sku_type != 2) {
			return;
		}
		edx = pciexbar;
		al = *((int8_t*) (edx + 0xe0410));
		if (al >= 0) {
			al = *((int8_t*) (esi + 0xfa092));
			eax |= 1;
			*((int8_t*) (esi + 0xfa092)) = al;
		}
		edx = pciexbar;
		al = *((int8_t*) (edx + 0xe0410));
		if ((al & 0x40) == 0) {
			al = *((int8_t*) (esi + 0xfa092));
			eax |= 2;
			*((int8_t*) (esi + 0xfa092)) = al;
		}
		edx = pciexbar;
		al = *((int8_t*) (edx + 0xe0410));
		if ((al & 0x20) == 0) {
			al = *((int8_t*) (esi + 0xfa092));
			eax |= 4;
			*((int8_t*) (esi + 0xfa092)) = al;
		}
		edx = pciexbar;
		al = *((int8_t*) (edx + 0xe0410));
		if ((al & 0x10) != 0) {
			return;
		}
		al = *((int8_t*) (esi + 0xfa092));
		eax |= 8;
		goto label_26; // loc_fffc826b
	}
	al = *((int8_t*) (esi + 0xfa092));
	eax |= 0x10;
	*((int8_t*) (esi + 0xfa092)) = al;
label_25: // loc_fffc8255:
	edx = pciexbar;
	al = *((int8_t*) (edx + 0xe0410));
	if ((al & 0x20) != 0) {
		return;
	}
	al = *((int8_t*) (esi + 0xfa092));
	eax |= 0x20;
label_26:
	*((int8_t*) (esi + 0xfa092)) = al;
	return;
}
