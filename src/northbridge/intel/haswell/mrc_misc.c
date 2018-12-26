#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_sku.h"
#include "mrc_misc.h"
#include <arch/io.h>

int dummy_func(void)
{
	return 0;
}

void dmi_check_link(void)
{
	if (mrc_sku_type() == 1) {
		uint32_t lcap = RCBA32(0x21a4);
		uint32_t max_link_speed = lcap & 0xf;
		if (max_link_speed == 2) {
			RCBA8_AND_OR(0x21b0, 0xf0, 2);
		}
	}
}

void __attribute((regparm(2))) rtc_wait(void *ram_data, uint16_t val)
{
	uint16_t t1, t2;
	*(uint16_t*)(ram_data + 0xfee) = val;
	outw(val, 0x80);

	do {
		outb(0x48, 0x74);
		t1 = inb(0x75);
		outb(0x49, 0x74);
		t2 = inb(0x75);
		t2 = (t2 << 8) | t1;
	} while (t2 == val);
}

int fcn_fffa1d20(bootmode, v, st, pps, ram_ppi)
{
	ebx = st; edi = ram_ppi; [bp-0x24] = st; esi = ram_ppi->ram_param;
	write32(st + 0x5f, 0xc8);
	write32(st + 0x5b, ram_ppi->ram_param);
	write32(st + 0x1d, 0); write8(st + 0x1c) = 0; write32(st + 0x45, 0);
	edx = ram_ppi->ram_param->v04;
	if (edx == 2) {
		eax = (bootmode != 4)? 2:0;
		write32(st + 0x49, eax);
		goto loc_fffa1dac;
	}
	if (edx == 3) {
		eax = (bootmode != 4)? 3:0;
		write32(st + 0x49, eax);
		goto loc_fffa1dac;
	}
	edx--; 
	if (edx!=0 || bootmode == 4) {
		write32(st + 0x49, 0);
	} else {
		write32(st + 0x49, 1);
		write32(st + 0x1d,  byte ram_ppi->ram_param[0x53]);
		write8(st + 0x1c,  byte ram_ppi->ram_param[0x54]);
		write32(st + 0x45,  byte ram_ppi->ram_param[0x4c]);
	}
loc_fffa1dac:
	write32(st + 0x67, ram_ppi->ram_data->mchbar);
	write32(st + 0x63, ram_ppi->ram_data->pciexbar);
	write32(st + 0x6b, ram_ppi->ram_data->smbusbar);
	write32(st + 0x6f, ram_ppi->ram_data->gdxcbar);
	write32(st + 0x73, 0xfed00000);
	eax = ram_ppi->cfg0; eax = *(uint16_t*)eax; write32(st + 0x7b, eax);
	write32(st + 0x18, ram_ppi->ram_param->max_ddr3_freq);
	eax = ram_ppi->ram_data->tseg_size >> 0x14; write32(st + 0x7f, eax);
	eax = ram_ppi->cfg0; eax = *(uint16_t*)(eax + 2); write32(st + 0x35, eax);
	eax = ram_ppi->cfg0; eax = *(uint8_t*)(eax + 4);
	if (al == 0x11) {
		write32(st + 0x31, 0x400);
	} else {
		eax <<= 5;
		write32(st + 0x31, eax);
	}

	[bp-0x1c] = st + 0x39;
	write8(st + 0x55, 0);
	fcn_fffc8290(eax = st + 0x39, edx = st + 0x3a, ecx = st + 0x3b, ebx + 0x3c, ebx + 0x3d, ebx + 0x3e, /*oldeax*/);

	eax = ram_ppi->ram_data->system_type;
	write32(st + 0x25, eax);
	ax = pci_read_config16(PCI_DEV(0, 0, 0), 2);
	if (ax == 0xa04 || ax == 0xc04 || ax == 0xa0c || ax == 0xd04)
		edx = 1;
	else
		edx = 0;

	write8(st + 0x52, edx);
	*(u32*)(st + 0x8b) = *(u32*)(esi + 0x4e);
	*(u16*)(st + 0x8f) = 0x3e8;
	*(u8*)(st + 0x54) = 0;
	*(u8*)(st + 0x57) = *(u8*)(esi + 0x2e);
	*(u8*)(st + 0x6d8) = *(u8*)(esi + 0x2f);
	*(u8*)(st + 0x6d9) = *(u8*)(esi + 0x30);
	*(u8*)(st + 0x6da) = *(u8*)(esi + 0x31);
	*(u8*)(st + 0x6db) = *(u8*)(esi + 0x6b);

	tmp = read8(st + 0x6dc);
	for (i = 0; i < 8; i++) {
		tmp &= 0xffffffff - (1 << i);
		tmp |= (read8(esi + 0x32 + i) & 1) << i;
	}
	write8(st + 0x6dc, tmp);

	tmp = read8(st + 0x6dd);
	for (i = 0; i < 8; i++) {
		if (i == 3) continue;
		tmp &= 0xffffffff - (1 << i);
		tmp |= (read8(esi + 0x3a + i) & 1) << i;
	}
	write8(st + 0x6dd, tmp);

#define UPDATEi(tmp, r_addr, sh) do { tmp &= (0xffffffff - (1 << i)); tmp |= ((read8(r_addr) & 1) << i); } while (0);
	tmp = read8(st + 0x6de);
	UPDATEi(tmp, esi + 0x42, 0);
	UPDATEi(tmp, esi + 0x43, 2);
	UPDATEi(tmp, esi + 0x44, 3);
	UPDATEi(tmp, esi + 0x47, 6);
	UPDATEi(tmp, esi + 0x48, 7);
	write8(st + 0x6de, tmp);

	tmp = read8(st + 0x6df);
	UPDATEi(tmp, esi + 0x49, 0);
	UPDATEi(tmp, esi + 0x4a, 1);
	UPDATEi(tmp, esi + 0x4b, 2);
	write8(st + 0x6df, tmp);

	if (read8(edi) > 1) {
		UPDATEi(tmp, esi + 0x58, 3);
		UPDATEi(tmp, esi + 0x59, 4);
		UPDATEi(tmp, esi + 0x5a, 5);
	} else {
		tmp &= 0xffffffe7;
		tmp |= 0x20;
	}
	write8(st + 0x6df, tmp);

	tmp = read8(st + 0x6de);
	if (read8(edi) > 3) {
		UPDATEi(tmp, esi + 0x5c, 1);
		write8(st + 0x6de, tmp);
		for (int i = 0; i < 7; i++) {
			*(u8*)(st + 0x91 + i) = *(u8*)(esi + 0x5d + i);
		}
	} else {
		tmp |= 2; write8(st + 0x6de, tmp);
		*(u8*)(st + 0x91) = 0xff;
		*(u8*)(st + 0x92) = 0x40;
		*(u8*)(st + 0x93) = 1;
		*(u8*)(st + 0x94) = 1;
		*(u8*)(st + 0x95) = 0;
		*(u8*)(st + 0x96) = 7;
		*(u8*)(st + 0x97) = 0;
	}

	if (read8(edi) > 4) {
		eax = read32(esi + 0x64);
		edx = 100000000;
		if (eax > 89999999) {
			edx = (eax / 1000000) * 1000000;
		}
		write8(st + 0x21, edx);
	} else {
		write8(st + 0x21, 100000000);
	}

	tmp = read8(st + 0x6df);
	if (read8(edi) > 5) {
		UPDATEi(tmp, esi + 0x6a, 6);
	} else {
		tmp |= 0x40;
	}
	write8(st + 0x6df, tmp);

	if (read8(edi) > 8) {
		eax = ram_ppi->ram_data->ied_region_size >> 0x14;
		*(u32*)(st + 0x83) = eax;
		for (int i = 0; i < 5; i++) {
			if (i == 3) continue;
			*(u8*)(st + 0x98 + i) = *(u8*)(esi + 0x6c);
		}
	} else {
		*(u32*)(st + 0x83) = 4;
		*(u8*)(st + 0x98) = 0;
		*(u8*)(st + 0x99) = 1;
		*(u8*)(st + 0x9a) = 0x30ce;
		*(u8*)(st + 0x9c) = 1;
	}

#define MOVEB(dst, src) do { *(u8*)(st + (dst)) = *(u8*)(esi + (src)); } while (0);
#define MOVEB2(dst, src) do { MOVEB((dst + 1), src); MOVEB(dst, (src + 1)); } while (0);
	if (read8(edi) > 9) {
		for (int i = 0; i < 4; i++)
			*(u8*)(st + 0x9d + i) = *(u8*)(esi + 0x71 + i);
		eax = *(u8*)(st + 0x2d);
		if (eax == HASWELL_FAMILY_ULT) {
			*(u8*)(st + 0xa1) = *(u8*)(esi + 0x75);
		}
		for (int i = 0; i < 5; i++) {
			MOVEB(0xa2 + i, 0x76 + i);
		}
		MOVEB(0xa8, 0x7b); MOVEB(0xa7, 0x7c);
		for (int i = 0; i < 5; i++) {
			MOVEB(0xa9 + i, 0x7d + i);
		}
		for (int i = 0; i < 4; i++) {
			MOVEB(0xaf + i, 0x83 + i);
		}
		for (int i = 0; i < 10; i++) {
			MOVEB(0xb4 + i, 0x88 + i);
		}
		for (int i = 0; i < 6; i++) {
			MOVEB(0xbe + i, 0x92 + i);
		}
		MOVEB2(0xc4, 0x98);
		MOVEB2(0xc6, 0xa2);
		MOVEB2(0xc8, 0x9a);
		MOVEB2(0xca, 0xa4);
		MOVEB2(0xcc, 0x9c);
		MOVEB2(0xce, 0xa6);
		MOVEB2(0xd0, 0x9e);
		MOVEB2(0xd2, 0xa8);
		MOVEB2(0xd4, 0xa0);
		MOVEB2(0xd6, 0xaa);

		MOVEB(0xd8, 0xac);
		MOVEB(0xd9, 0xad);
		MOVEB(0xdb, 0xaf);
		MOVEB(0xdc, 0xb0);
		
		if (eax == HASWELL_FAMILY_ULT) {
			MOVEB(0xdd, 0xb1);
			MOVEB(0xde, 0xb2);
		}
		jmp near loc_fffa2673  ; jmp 0xfffa2673
	} else {
		ecx = read32(st + 0x2d);
		write8(st + 0x9d, 0);
		write8(st + 0x9e, 0);
		write8(st + 0x9f, 0);
		write8(st + 0xa0, 1);
		if (ecx == HASWELL_FAMILY_ULT)
			write8(st + 0xa1, 0);

		write8(st + 0xa2, 0);
		write8(st + 0xa3, 1);
		write8(st + 0xa4, 0);
		write8(st + 0xa6, 3);
		write8(st + 0xa9, 0);
		write8(st + 0xaa, 0);
		write8(st + 0xab, 0);
		write8(st + 0xac, 0);
		write8(st + 0xad, 0);
		write8(st + 0xaf, 0);
		write8(st + 0xb0, 0);
		write8(st + 0xb1, 0);
		write16(st + 0xb2, 0);

		write8(st + 0xa7, 0); write8(st + 0xa8, 0);
		for (int i = 0; i < 16; i++)
			write8(st + 0xb4 + i, 0xff);
		for (int i = 0; i < 20; i++)
			write8(st + 0xc4 + i, 0xff);

		write8(ebx + 0xd8, 1);
		write8(ebx + 0xd9, 0x200);
		write8(ebx + 0xdb, 0);
		write8(ebx + 0xdc, 0x30);
		if (ecx == HASWELL_FAMILY_ULT) {
			write8(st + 0xdd, 1);
			write8(st + 0xde, 0x40);
		}
	}

	if (read8(edi) > 0xa) {
		MOVEB(0x59, 0xc2);
		MOVEB(0x5a, 0xc3);
		MOVEB(0x6e5, 0xc4);
	} else {
		write8(st + 0x59, 1);
		write8(st + 0x5a, 1);
		write8(st + 0x6e5, 0);
	}

	tmp = read8(st + 0x6dd);
	if (read8(edi) > 0xb) {
		UPDATEi(tmp, esi + 0xc5, 3);
	} else {
		tmp |= 8;
	}
	write8(st + 0x6dd, tmp);

	if (read8(edi) > 0xe) {
		tmp = read8(esi + 0xc7) & 1;
	} else {
		tmp = 1;
	}

	u8 tmp2 = read8(st + 0x6de) & 0xffffffef;
	tmp2 |= (tmp << 4);
	write8(st + 0x6de, tmp2);
	write8(st + 0x41, 0);
	write8(st + 0x40, 0);
	MOVEB(0x56, 0x11);
	MOVEB(0x58, 0x2c);
	MOVEB(0x53, 0);
	MOVEB(0x6e1, 0x52);

	if (read32(st + 0x2d) == HASWELL_FAMILY_ULT) {
		write8(st + 0x6e3, 0);
		MOVEB(0x6e2, 0x57);
	}

loc_fffa2732:
lea ecx, [ebx + 0xdf]
mov byte [ebx + 0xe3], 0
mov dword [ebp - 0x1c], 0

loc_fffa2746:
imul edx, dword [ebp - 0x1c], 0x2fa
add edx, ecx
mov eax, edx
mov dword [ebp - 0x28], edx
mov edx, dword [ebp - 0x1c]
add eax, 5
mov dl, byte [esi + edx + 0x2a]
cmp dl, 2
mov byte [ebp - 0x20], dl
je short loc_fffa2782  ; je 0xfffa2782
cmp dl, 3
je short loc_fffa27a9  ; je 0xfffa27a9
dec dl
jne short loc_fffa27cd  ; jne 0xfffa27cd
mov dword [eax + 8], 1
mov dword [eax + 0x157], 0
jmp short loc_fffa2793  ; jmp 0xfffa2793

loc_fffa2782:
mov dword [eax + 8], 0
mov dword [eax + 0x157], 1

loc_fffa2793:
mov edx, dword [ebp - 0x28]
mov dword [edx + 5], 2
inc byte [ecx + 4]
mov dword [eax + 4], 1
jmp short loc_fffa27f2  ; jmp 0xfffa27f2

loc_fffa27a9:
mov edx, dword [ebp - 0x28]
mov dword [eax + 8], 1
mov dword [eax + 0x157], 1
mov dword [edx + 5], 1
mov dword [eax + 4], 0
jmp short loc_fffa27f2  ; jmp 0xfffa27f2

loc_fffa27cd:
mov edx, dword [ebp - 0x28]
mov dword [eax + 8], 0
mov dword [eax + 0x157], 0
mov dword [edx + 5], 2
inc byte [ecx + 4]
mov dword [eax + 4], 2

loc_fffa27f2:
inc dword [ebp - 0x1c]
cmp dword [ebp - 0x1c], 2
jne loc_fffa2746  ; jne 0xfffa2746

mov eax, dword [edi + 1]
mov al, byte [eax]
mov byte [ebx + 0x23a], al
mov eax, dword [edi + 1]
mov al, byte [eax + 1]
mov byte [ebx + 0x389], al
mov eax, dword [edi + 1]
mov al, byte [eax + 2]
mov byte [ebx + 0x534], al
mov eax, dword [edi + 1]
mov al, byte [eax + 3]
mov byte [ebx + 0x683], al
mov eax, dword [0xff7d7538]
mov eax, dword [eax]
cmp dword [eax - 4], 0xfeadb00b
jne short loc_fffa2850  ; jne 0xfffa2850
mov eax, dword [eax + 0x258]
xor esi, esi
add eax, 0xe2
mov dword [ebp - 0x2c], eax
jmp short loc_fffa28bb  ; jmp 0xfffa28bb

loc_fffa2850:
jmp short loc_fffa2850  ; jmp 0xfffa2850

loc_fffa2852:
imul eax, dword [ebp - 0x1c], 0x14f
mov ecx, dword [ebp - 0x28]
lea edx, [eax + ecx + 0xd0]
add edx, ebx
cmp byte [edx + 0x16a], 0xff
lea eax, [edx + 0x1c]
mov dword [ebp - 0x20], eax
jne short loc_fffa28ac  ; jne 0xfffa28ac
cmp dword [edx + 0x1c], 0
jne short loc_fffa28ac  ; jne 0xfffa28ac
push eax
push dword [ebp - 0x1c]
mov dword [ebp - 0x30], edx
push esi
push ref_fffcc46a  ; push 0xfffcc46a
call mrc_printk
mov edx, dword [ebp - 0x30]
mov ecx, 0x100
lea eax, [edx + 0x40]
mov edx, dword [ebp - 0x2c]
call mrc_memcpy
mov edx, dword [ebp - 0x20]
add esp, 0x10
mov byte [edx + 0x14e], 0

loc_fffa28ac:
inc dword [ebp - 0x1c]
cmp dword [ebp - 0x1c], 2
jne short loc_fffa2852  ; jne 0xfffa2852
inc esi
cmp esi, 2
je short loc_fffa28cd  ; je 0xfffa28cd

loc_fffa28bb:
imul ecx, esi, 0x2fa
mov dword [ebp - 0x1c], 0
mov dword [ebp - 0x28], ecx
jmp short loc_fffa2852  ; jmp 0xfffa2852

loc_fffa28cd:
cmp dword [ebp - 0x24], 2
je short loc_fffa28f8  ; je 0xfffa28f8
cmp dword [ebp - 0x24], 3
je short loc_fffa28ff  ; je 0xfffa28ff
cmp dword [ebp - 0x24], 1
jne short loc_fffa2912  ; jne 0xfffa2912
cmp dword [ebx + 0x49], 1
mov esi, 1
jne short loc_fffa292d  ; jne 0xfffa292d
mov edx, edi
mov eax, ebx
call fcn_fffa0020  ; call 0xfffa0020
mov esi, dword [ebp - 0x24]
jmp short loc_fffa292d  ; jmp 0xfffa292d

loc_fffa28f8:
mov esi, 2
jmp short loc_fffa291e  ; jmp 0xfffa291e

loc_fffa28ff:
mov edx, ebx
mov eax, 3
call fcn_fffa91af  ; call 0xfffa91af
mov esi, 3
jmp short loc_fffa291e  ; jmp 0xfffa291e

loc_fffa2912:
mov edx, ebx
mov eax, dword [ebp - 0x24]
call fcn_fffa91af  ; call 0xfffa91af
xor esi, esi

loc_fffa291e:
cmp dword [ebx + 0x49], 1
jne short loc_fffa292d  ; jne 0xfffa292d
mov edx, edi
mov eax, ebx
call fcn_fffa0020  ; call 0xfffa0020

loc_fffa292d:
lea esp, [ebp - 0xc]
mov eax, esi
pop ebx
pop esi
pop edi
pop ebp
ret
