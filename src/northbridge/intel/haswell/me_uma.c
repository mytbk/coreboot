#include <device/pci_ops.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_pei.h"
#include "mrc_utils.h"
#include <console/console.h>

u32 get_uma_size(EFI_PEI_SERVICES **pps, void *me);
u32 get_uma_size(EFI_PEI_SERVICES **pps, void *me)
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
