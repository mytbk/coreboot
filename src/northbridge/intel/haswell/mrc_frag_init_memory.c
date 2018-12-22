#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/pci_ops.h>
#include "mrc_pei.h"
#include <cpu/x86/msr.h>
#include "mrc_utils.h"

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

void frag_fffc1cd2(void);
void frag_fffc1cd2(void)
{
	for (int i = 0; i < 0x2ee; i++) {
		uint8_t tmp = read8((void*)0xfed40000);
		if (tmp == 0xff)
			break;
		if (tmp & 0x80) {
			if (tmp & 1)
				break;
			else
				return;
		}
		usleep(1000);
	}
	wrmsr(0x2e6, (msr_t){0, 0});
}
