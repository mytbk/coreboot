#include <stdint.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include "mrc_misc.h"
#include "device/pci.h"
#include "mrc_init_memory.h"
#include "me_uma.h"

const uint32_t ref_fffcbee8[] = {
	0x4000f001,
	0x02005a01,
	0x011800dc,
	0x9004005a,
	0xa0020801,
	0x01900500,
	0x00a00208,
	0xe000f010,
	0x11000001,
	0x01e000f0,
	0xc0200000,
	0x00018000,
	0x00c02100,
	0x00000180,
	0x2200be0b,
	0x00000001,
};

extern EFI_GUID ref_fffcd4e4;
extern EFI_GUID gEfiPeiReadOnlyVariablePpiGuid;

int __attribute((regparm(1))) mrc_init_memory(const EFI_PEI_SERVICES **pps)
{
	int iVar1;
	uint8_t retv;
	uint8_t bVar2;
	int iVar3;
	uint32_t uVar4;
	uint8_t local_BL__1;
	uint32_t local_50c8;
	uint8_t local_50ae;
	uint8_t local_50ad;
	void *ro_var_ppi;
	void *raminit_ppi;
	void *ram_hob;
	int bootmode;
	uint32_t local_5098;
	uint32_t local_508c;
	uint8_t local_507d[63];
	char ram_data[20514];

	mrc_zeromem(ram_data, 0x5022);
	*(void **)(ram_data + 5996) = local_507d;
	mrc_memcpy(local_507d, ref_fffcbee8, 0x3f);
	mrc_get_bootmode(pps, &bootmode);
	if (bootmode == 0x11) {
		ram_hob = (void *)0x0;
	} else {
		ram_hob = create_raminit_hob();
	}
	mrc_locateppi(pps, &ref_fffcd4e4, 0, 0, &raminit_ppi);
	rtc_wait(ram_data, 0xdd00);
	local_50ae = '\0';
	mrc_locateppi(pps, &gEfiPeiReadOnlyVariablePpiGuid, 0, 0, &ro_var_ppi);
	frag_fffc1c07();
	local_50c8 = 2;
	if (bootmode != 0x11) {
		local_50c8 = frag_fffc1d20();
	}
	fcn_fffa9196(&local_5098);
	retv = copy_mrc_input(raminit_ppi, bootmode, ram_data + 4);
	local_BL__1 = retv;
	if ((bootmode != 0x11) || (iVar3 = -0x7ffffff2, retv != '\0')) {
		if (1 < local_50c8 - 1) {
			fcn_fffbe070(pps, (void *)0x0, &local_50ae);
			if (local_50ae == '\x01') {
				local_BL__1 = 0;
			}
		}
		iVar3 = superfrag_fffc1ea8(bootmode, ram_data, raminit_ppi, local_50c8,
				local_BL__1);
		*(uint32_t *)(ram_data + 4175) = get_uma_size(pps, (void *)0x0);
		do {
			iVar1 = *(uint32_t *)(ram_data + 4133);
			if (iVar1 == 0) {
				frag_fffc1fc3();
			}
			*(uint32_t *)(ram_data + 5847) = iVar1;
			fcn_fffa9196((uint32_t *)(ram_data + 0x16be));
			uVar4 = frag_fffc2026(ram_data);
			if (uVar4 == 0x16) {
				fcn_fffbe14d(pps, (void *)0x0, iVar3, 1);
				rtc_wait(ram_data, 0xddfe);
loc_fffc2251:
				bVar2 = inb(0x80);
				outb(bVar2 | 0x80, 0x80);
				return -0x7ffffff9;
			}
			if (uVar4 < 0x17) {
				if (uVar4 != 0) {
					if ((uVar4 != 0x15)
							|| (fcn_fffb5038(ram_data, &local_508c, &local_50ad,
									NULL),
								(uint8_t)ram_data[5846] <= local_50ad
								/* what's this function?? */))
						goto loc_fffc2251;
loc_fffc21b8:
					if (*(uint32_t *)(ram_data + 4133) == 3) {
						*(uint32_t *)(ram_data + 4133) = fcn_fffa1d20(
								bootmode, 0, ram_data + 0xfd8, pps,
								raminit_ppi);
					} else {
						*(uint32_t *)(ram_data + 4133) = 0;
					}
					uVar4 = 0x17;
				}
			} else {
				if (uVar4 == 0x17)
					goto loc_fffc21b8;
				if (uVar4 != 0x1b)
					goto loc_fffc2251;
				mrc_zeromem(ram_data + 0x16be, 0x395c);
				*(void **)(ram_data + 5996) = local_507d;
				ram_data[4120] = ram_data[4120] + '\x01';
			}
		} while (uVar4 == 0x1b || uVar4 == 0x17);
		inb(0x84);
		if ((*(int32_t *)(ram_data + 4175) < 0x21)
				&& pci_read_config32(PCH_ME_DEV, PCI_BASE_ADDRESS_0) != -1) {
			fcn_fffbe14d(pps, (void *)0x0, iVar3,
					-(uint32_t)(iVar3 == 0 && (char)local_50c8 == '\x01') & 3);
		}
		if (bootmode != 0x11) {
			if ((iVar3 == 3 || iVar3 == 0) && (iVar3 = test_memory(), iVar3 != 0)) {
				rtc_wait(ram_data, 0xd5);
				return -0x7ffffff9;
			}
			*(uint32_t *)(ram_data) = 0xfd4;
			memcpy((void *)((int)ram_hob + 0x18), ram_data, 0x5022);
			mrc_zeromem((void *)((int)ram_hob + 0x503a), 1);
		}
		rtc_wait(ram_data, 0x55);
		iVar3 = 0;
	}
	return iVar3;
}
