#include "mrc_pei.h"

void mrc_get_bootmode(const EFI_PEI_SERVICES **pps, int *bootmode);
void mrc_get_bootmode(const EFI_PEI_SERVICES **pps, int *bootmode)
{
	(*pps)->GetBootMode(pps, bootmode);
}

int mrc_locateppi(const EFI_PEI_SERVICES **pps,
		const EFI_GUID *Guid, unsigned long instance,
		EFI_PEI_PPI_DESCRIPTOR  **PpiDescriptor, void *ppi);
int mrc_locateppi(const EFI_PEI_SERVICES **pps,
		const EFI_GUID *Guid, unsigned long instance,
		EFI_PEI_PPI_DESCRIPTOR  **PpiDescriptor, void *ppi)
{
	return (*pps)->LocatePpi(pps, Guid, instance, PpiDescriptor, ppi);
}
