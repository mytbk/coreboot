#include "mrc_pei.h"
#include "mrc_utils.h"
#include <string.h>
#include <console/console.h>

static const EFI_PEI_SERVICES ***gpPei = (const EFI_PEI_SERVICES***)0xff7d7538;

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

int EFIAPI PeiLocatePpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_GUID *Guid,
		unsigned long Instance,
		EFI_PEI_PPI_DESCRIPTOR **PpiDescriptor,
		void **Ppi)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);
	int nppi = pei->nb_installed_ppi;

	for (int i = 0; i < nppi; i++) {
		if (memcmp(Guid, pei->installedPpi[i].Guid, 16) == 0) {
			*Ppi = pei->installedPpi[i].Ppi;
			return 0;
		}
	}
	printGuid(Guid);
	return 0x8000000e;
}

int EFIAPI PeiNotifyPpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_PEI_NOTIFY_DESCRIPTOR *NotifyList)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);

	while (1) {
		int nb_notify = pei->nb_notify_desc;
		if (nb_notify >= 20)
			return 0x80000009;

		pei->notify_dsc[nb_notify] = *NotifyList;
		pei->nb_notify_desc++;
		if (NotifyList->Flags & (1 << 31))
			return 0;
		else
			NotifyList++;
	}
}

int PeiGetBootMode(const EFI_PEI_SERVICES **PeiServices, int *mode)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);

	*mode = pei->bootmode;
	return 0;
}

int EFIAPI PeiCreateHob(const EFI_PEI_SERVICES **PeiServices,
		uint16_t Type, uint16_t Length, void **Hob)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);
	EFI_HOB *hb = mrc_alloc(Length + sizeof(void*));
	if (hb == NULL)
		return 0x80000009;

	EFI_HOB_DATA *hbb = &hb->hobdata;
	*Hob = hbb;
	hbb->htype = Type;
	hbb->hlen = Length;
	hbb->data[0] = 0;
	hb->next = pei->hobList;
	pei->hobList = hb;
	return 0;
}

int EFIAPI PeiGetHobList(const EFI_PEI_SERVICES **PeiServices, void **HobList)
{
	MRC_PEI *pei = PEI_FROM_PEI_SERVICE(*PeiServices);
	*HobList = pei->hobList;
	return 0;
}

int __attribute((regparm(1))) PeiServiceGetBootMode(int *BootMode)
{
	const EFI_PEI_SERVICES **pps = *gpPei;
	return (*pps)->GetBootMode(pps, BootMode);
}
