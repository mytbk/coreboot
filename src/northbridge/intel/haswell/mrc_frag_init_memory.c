#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/pci_ops.h>
#include "mrc_pei.h"

int frag_fffc1d20(void);
int frag_fffc1d20(void)
{
	u32 tmp = pci_read_config32(PCI_DEV(0, 0x1f, 0), 0xa0);
	tmp >>= 16;
	tmp &= 0xa0;
	return (tmp == 0xa0)?1:0;
}

int frag_fffc1fc3(void);
int frag_fffc1fc3(void)
{
	u32 tmp = pci_read_config32(PCI_DEV(0, 0x1f, 0), 0xa0);
	tmp &= 0xff7f0000;
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0xa0, tmp);
	return 0;
}

static const EFI_PEI_SERVICES ***gpPei = (const EFI_PEI_SERVICES***)0xff7d7538;
extern EFI_GUID mEfiMemoryRestoreDataGuid;

void *create_raminit_hob(void);
void *create_raminit_hob(void)
{
	void *hob;
	const EFI_PEI_SERVICES **pps = *gpPei;
	int res = (*pps)->CreateHob(pps, 4, 0x503b, &hob);
	if (res < 0)
		return hob;

	memcpy(hob + 8, &mEfiMemoryRestoreDataGuid, 16);
	memset(hob + 0x18, 0, 0x5022);
	return hob;
}
