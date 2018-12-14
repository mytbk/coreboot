#include "mrc_pei.h"
#include "mrc_utils.h"
#include <string.h>
#include <console/console.h>

static inline
MRC_PEI *PEI_FROM_PEI_SERVICE(const EFI_PEI_SERVICES *ps)
{
	MRC_PEI *pei = (MRC_PEI *)((void*)ps - 4);
	if (pei->sig != PEI_SIGNATURE)
		die("PEI signature error!\n");
	return pei;
}

int EFIAPI
PeiInstallPpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_PEI_PPI_DESCRIPTOR *PpiList)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);
	int i;
	int sz;

	while (1) {
		sz = pei->nb_installed_ppi;
		EFI_PEI_PPI_DESCRIPTOR *plist = pei->installedPpi;
		for (i = 0; i < sz; i++) {
			if (memcmp(PpiList->Guid, plist[i].Guid, 16) == 0) {
				mrc_printk("%s: overwrite GUID ", "install_ppi");
				printGuid(PpiList->Guid);
				break;
			}
		}
		if (i == sz) {
			if (i >= 20) {
				mrc_printk("%s: no room for a new PPI\n", "install_ppi");
				return 0x80000009;
			}
			pei->nb_installed_ppi++;
		}
		plist[i] = *PpiList;

		for (i = 0; i < pei->nb_notify_desc; i++) {
			EFI_PEI_NOTIFY_DESCRIPTOR *dsc = &pei->notify_dsc[i];

			if (memcmp(PpiList->Guid, dsc->Guid, 16) == 0)
				dsc->Notify((EFI_PEI_SERVICES**)PeiServices, dsc, PpiList->Ppi);
		}
		if (PpiList->Flags & (1 << 31))
			return 0;
		else
			PpiList++;
	}
}

int PeiGetBootMode(const EFI_PEI_SERVICES **PeiServices, int *mode)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);

	*mode = pei->bootmode;
	return 0;
}
