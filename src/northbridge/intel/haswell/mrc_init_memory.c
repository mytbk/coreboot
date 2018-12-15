#include "mrc_pei.h"
#include "mrc_utils.h"

uint8_t ref_fffcbee8[64];

struct {
	void (*func)(int);
	uint32_t v1;
	uint32_t v2;
} ref_fffcbf28[];

int mrc_init_memory(const EFI_PEI_SERVICES **pps)
{
	int32_t local_50c8h;
	int32_t local_50c4h;
	int32_t local_50c0h;
	const EFI_PEI_SERVICES ** local_50bch = pps;
	int32_t local_50aah;
	int32_t local_50a9h;
	int32_t local_50a8h;
	void *local_50a4h; // stores a ppi
	void *mHob;
	int bootmode; // ebp - 0x509c
	int32_t local_5098h;
	int32_t local_5094h;
	int32_t local_5090h;
	int32_t local_508ch;
	int32_t local_5088h;
	uint8_t local_5079h[63] ;

	struct {
		int32_t local_503ah;
		int32_t local_5036h;
		int32_t local_4062h;
		int32_t local_4039h;
		int32_t local_4035h;
		int32_t local_4022h;
		int32_t local_4021h;
		int32_t local_4015h;
		int32_t local_3febh;
		int32_t local_3fdbh;
		int32_t local_397ch;
		int32_t local_3964h;
		int32_t local_3963h;
		int32_t local_391ah;
		uint8_t *local_38ceh;
	} st_503a;

	mrc_zeromem(&st_503a, 0x5022);
	mrc_memcpy(local_5079h, ref_fffcbee8, 63);
	st_503a.local_38ceh = local_5079h;
	(*pps)->GetBootMode(pps, &bootmode);
	if (bootmode != 0x11) {
		int ret = (*pps)->CreateHob(pps, 4, 0x503b, &mHob);
		if (ret >= 0) {
			memcpy(mHob + 8, mEfiMemoryRestoreDataGuid, 16);
			mrc_zeromem(mHob + 0x18, 0x5022);
		}
	} else {
		mHob = NULL;
	}

	esi = 1;
	edi = 0;
	(*pps)->LocatePpi(pps, ref_fffcd4e4, 0, NULL, &local_50a4h);
	fcn_fffc83be(&st_503a, 0xdd00);
	(*pps)->LocatePpi(pps, gEfiPeiReadOnlyVariablePpiGuid, 0, NULL, &local_50a8h);
	local_50aah = 0;
	cpuid(eax=1,ecx=0);
	cl &= 0x40;
	if (cl == 0) goto loc_fffc1d20;
	cpuid(eax=1, ecx=0);
	esi = ecx & 0x40;
	if (ecx != 0) {
		edx = cr4;
		cr4 |= 0x4000; // enable safer mode extensions
		eax = ebx = 0;
		asm("getsec");
		cr4 = edx;
	}
	if (al & 1) goto loc_fffc1d20;
	ebx = 0x2ee;
	(*pps)->LocatePpi(pps, gEfiPeiStallPpiGuid, 0, NULL, &local_5088h);

	do {
		uint8_t b = (*pps)->CpuIo->MemRead8(pps, (*pps)->CpuIo, 0xfed40000);
		if (b == 0xff)
			break;
		if (b < 0) {
			if (al & 1)
				wrmsr(0x2e6, 0);

			goto loc_fffc1d20;
		}
		usleep(1000);
		ebx--;
	} while (ebx);

	wrmsr(0x2e6, 0);
loc_fffc1d20:
	local_50c4h = 2;
	if (bootmode != 0x11) {
		outl(0xf000f8a0, 0xcf8);
		uint32_t eax = inl(0xcfc);
		eax >>= 16;
		eax &= 0xa0;
		if (eax == 0xa0)
			eax = 1;
		local_50c4h = eax;
	}
	ebx = 0;
	fcn_fffa9196(&local_5094h);
	eax = &local_50a4h;
	esi = [eax + 0x15];
	if (esi != 0 && bootmode != 4) {
		eax = esi + 4;
		edx = 0xfd0;
		eax = fcn_fffab210(eax, edx); // crc32
		if (eax == *(int*)esi) {
			memcpy(&st_503a.local_5036h, esi, 0xfd4);
			ebx = 1;
		}
	}
	if (bootmode == 0x11 && bl == 0) {
		return 0x8000000e;
	}

	(*pps)->LocatePpi(pps, gPchMeUmaPpiGuid, 0, NULL, &local_5098h);
	eax = local_50c4h - 1;
	if (eax > 1) {
		local_5098h->[4](pps, 0, &local_50aah, pps);
		if (local_50aah == 1)
			ebx = 0;
	}
	esi = haswell_family_model();
	eax = haswell_stepping();
	if (esi == 0x40650) {
		st_503a.local_4035h = 0x40650;
	} else if (esi == 0x40660) {
		st_503a.local_4035h = 0x40660;
	} else {
		if (esi == 0x306c0) {
			st_503a.local_4035h = 0x306c0;
			if (eax == 2) {
				st_503a.local_4039h = 2;
			} else if (eax == 3) {
				st_503a.local_4039h = 3;
			} else {
				eax--;
				if (eax != 0) eax = 1;
				eax = eax * 2 + 1;
				st_503a.local_4039h = eax;
			}
		}
		goto loc_fffc1ea8;
	}

	if (eax != 0) {
		eax--;
		if (eax == 0) eax = 1;
		st_503a.local_4039h = eax;
	} else {
		st_503a.local_4039h = 0;
	}
loc_fffc1ea8:
	eax = local_50c4h - 1;
	if (eax > 1) {
		ebx--;
		if (ebx != 0) goto loc_fffc2376;
		edx = local_50a4h;
		eax = [edx + 9];
		if ([eax + 0x56] == 0) goto loc_fffc2376;
		eax = &st_503a;
		edi = 3;
		al = fcn_fffa10df(eax, edx);
		if (al != 0) goto loc_fffc2376;
	} else {
		if (bl == 0) goto loc_fffc2376;
		edx = local_50a4h;
		eax = &st_503a;
		al = fcn_fffa10df(eax, edx);
		al--;
		if (al == 0) goto loc_fffc2376;
		eax = local_50a4h;
		eax = [eax + 1];
		eax = [eax + 4];
		(u64)local_5090h = (u64)[eax + 0x5d10];
		eax = local_508ch | local_5090h;
		edi = local_50c4h;
		if (eax == 0) {
			edi--;
			if (edi == 0) goto loc_fffc2376;
			edi = 2;
		}
	}
loc_fffc1f53:
	edx = 4;
	eax = ref_fffcd4a4;
	eax = fcn_fffa11b3(eax, edx);
	if (eax != 0) {
		dl = (u8)[eax + 0x21] + (u8)[eax + 0x19];
		if (dl != 0) {
			edx = dl;
			st_503a.local_3fdbh = edx;
		}
	}
	ecx = &st_503a.local_4062h;
	edx = edi;
	_eax = eax;
	eax = bootmode;
	eax = fcn_fffa1d20(eax, edx, ecx, pps, local_50a4h, eax, eax);
	st_503a.local_4015h = eax;
	st_503a.local_3febh = 0;
	eax = local_5098h;
	eax = [eax](pps, 0);
	st_503a.local_3febh = eax;

loc_fffc1fc3:
	ecx = st_503a.local_4015h;
	if (ecx == 0) {
		outl(0x8000f8a0, 0xcf8);
		eax = inl(0xcfc);
		local_50c0h = eax;
		outl(0x8000f8a0, 0xcf8);
		local_50c0h &= 0xff7f0000;
		outl(local_50c0h, 0xcfc);
	}
	eax = &st_503a.local_397ch;
	st_503a.local_3963h = ecx;
	ebx = 1;
	fcn_fffa9196(eax);
	dl = 1;
	(u16)local_50c0h = 0;
	goto loc_fffc2116;
loc_fffc2026:
	idx = (u16)local_50c0h;
	eax = (u16)ax;
	edx = (u16)ref_fffcbf28[idx].v1;
	ecx = &ref_fffcbf28[idx];
	if ((u16)ref_fffcbf28[idx].v1 == -1)
		edx = eax;
	eax = &st_503a;
	local_50c8h = ecx;
	fcn_fffc83be(eax, edx, ecx);
	dl = 1;
	ecx = local_50c8h;
	if (ref_fffcbf28[idx].func == NULL)
		goto loc_fffc210f;
	al = [ecx + 0xb];
	if ((u8)st_503a.local_4022h >= al)
		goto loc_fffc210f;
	eax = st_503a.local_4021h;
	if (eax == 0) {
		if (([ecx + 0xa] & 0x10) == 0)
			goto loc_fffc210f;
	} else {
		eax--;
		if (eax != 0)
			goto loc_fffc210f;
		if (([ecx + 0xa] & 0x20) == 0)
			goto loc_fffc210f;
	}
	eax = st_503a.local_3963h;
	if (eax == 2) {
		if ([ecx + 0xa] & 8)
			goto loc_fffc20ce;
		goto loc_fffc210d;
	}
	if (eax == 3) {
		if ([ecx + 0xa] & 2)
			goto loc_fffc20ce;
		goto loc_fffc210d;
	}
	if (eax == 1) {
		if ([ecx + 0xa] & 4)
			goto loc_fffc20ce;
		goto loc_fffc210d;
	}
	dl = 1;
	if (eax == 0) {
		if (([ecx + 0xa] & 1) == 0)
			goto loc_fffc210f;
	} else {
		goto loc_fffc210f;
	}
loc_fffc20ce:
	edx = [ecx + 6];
	if (edx > 0x3b) {
loc_fffc20d6:
		fcn_fffc6986();
		edx = &st_503a;
		ebx = eax = ref_fffcbf28[idx].func(edx);
		fcn_fffc6986();
		if (ebx == 0)
			dl = 1;
		goto loc_fffc210f;
	}
	ecx = 0;
	eax = &st_503a;
	eax = fcn_fffc6438();
	if (eax == 0)
		goto loc_fffc20d6;
loc_fffc210d:
	dl = 1;
loc_fffc210f:
	(u16)local_50c0h ++;
loc_fffc2116:
	eax = local_50c0h;
	ax -= 0x2300;
	if ((u16)local_50c0h <= 0x33)
		cl = 1;
	if ((cl & dl) != 0)
		goto loc_fffc2026;
	if (ebx == 0x16)
		goto loc_fffc21fe;
	if (ebx == 0x15)
		goto loc_fffc2186;
	if (ebx <= 0x16) {
		if (ebx == 0)
			goto loc_fffc225d;
	}
	if (ebx == 0x17)
		goto loc_fffc21b8;
	if (ebx != 0x1b)
		goto loc_fffc2251;
	eax = &st_503a.local_397ch;
	edx = 0x395c;
	mrc_zeromem(eax, edx);
	eax = &local_5079h;
	(u8)st_503a.local_4022h++;
	st_503a.local_38ceh = eax;
	goto loc_fffc225d;
loc_fffc2186:
	ecx = &local_50a9h;
	edx = &local_5088h;
	eax = &st_503a;
	fcn_fffb5038(eax, edx, ecx, 0);
	cl = &st_503a.local_3964h;
	if (local_50a9h >= cl)
		goto loc_fffc2251;
loc_fffc21b8:
	if (st_503a.local_4015h == 3) {
		ecx = &st_503a.local_4062h;
		edx = 0;
		_eax = eax;
		eax = bootmode;
		eax = fcn_fffa1d20(eax, edx, ecx, pps, local_50a4h,
				_eax, _eax);
		st_503a.local_4015h = eax;
	} else {
		st_503a.local_4015h = 0;
	}
	ebx = 0x17;
	goto loc_fffc225d;
loc_fffc21fe:
	_eax = eax;
	eax = local_5098h;
	[eax + 8](pps, 0, edi, 1, st_503a.local_391ah,
			st_503a.local_3febh, _eax, _eax);
	eax = &st_503a;
	edx = 0xddfe;
	eax = fcn_fffc83be(eax, edx);
	edx = pps;
	_eax = eax;
	eax = edx;
	[eax + 0x58](edx, 2, 0x51009, 0, 0, 0, _eax, _eax);
loc_fffc2251:
	al = inb(0x80);
	al |= 0x80;
	outb(al, 0x80);
	return 0x80000007;
loc_fffc225d:
	if (ebx == 0x1b)
		dl = 1;
	if (ebx == 0x17)
		al = 1;
	dl |= al;
	if (dl != 0)
		goto loc_fffc1fc3;
	al = inl(0x84);
	eax = al + 0x100;
	ecx = st_503a.local_3febh;
	if (edi == 0)
		bl = 1;
	if ((u8)local_50c4h == 1)
		al = 1;
	eax &= ebx;
	eax = -eax;
	eax &= 3;
	if (ecx > 0x20)
		goto loc_fffc22d0;
	edx = [0xf0000060] & 0xfc000000;
	edx = [edx + 0xb0010];
	edx++;
	if (edx == 0)
		goto loc_fffc22d0;
	_eax = (u8)al;
	eax = local_5098h;
	[eax+8](pps, 0, edi, _eax, st_503a.local_391ah,
			ecx, esi, esi);
loc_fffc22d0:
	if (bootmode == 0x11) {
		eax = &st_503a;
		edx = 0x55;
		fcn_fffc83be(eax, edx);
		return 0;
	}
	if (edi == 3)
		dl = 1;
	eax = 0;
	dl |= bl;

	if (dl != 0) {
		for (eax = 0; eax < 0x1000; eax++)
			byte [eax] = (u8)eax;

		edx = 0x14;

		while (edx) {
			for (eax = 0; eax < 0x1000; eax++) {
				cl = (u8)eax;
				if (byte [eax] != cl) {
					edx = 0xd5;
					eax = &st_503a;
					fcn_fffc83be(eax, edx);
					return 0x80000007;
				}
			}
			edx--;
		}
	}

	ecx = pps;
	st_503a.local_503ah = 0xfd4;
	memcpy(mHob + 0x18, &st_503a, 0x5022);
	eax = mHob + 0x503a;
	edx = 1;
	mrc_zeromem(eax, edx);
	eax = &st_503a;
	edx = 0x55;
	fcn_fffc83be(eax, edx);
	return 0;
loc_fffc2376:
	edx = 0xfd4;
	eax = &st_503a.local_5036h;
	mrc_zeromem(eax, edx);
	edi = 0;
	goto loc_fffc1f53;
}
