#include "Smbus.h"

struct _PEI_SMBUS_POLICY_PPI {
	uint32_t BaseAddress;
	uint32_t PciAddress;
	uint8_t NumRsvdAddress;
	uint8_t *RsvdAddress;
} __packed;
typedef struct _PEI_SMBUS_POLICY_PPI PEI_SMBUS_POLICY_PPI;

typedef struct
{
	uint32_t sig;
	const EFI_PEI_SERVICES **pps;
	PEI_SMBUS_POLICY_PPI *pei_smbus_policy_ppi;
	uint32_t smbus_base_addr;
	EFI_PEI_PPI_DESCRIPTOR smbus_ppi_desc;
	EFI_PEI_SMBUS_PPI smbus_ppi;
	EFI_PEI_NOTIFY_DESCRIPTOR notify_desc;
	uint8_t v38;
	uint8_t v39[0x88];
	uint8_t NumRsvdAddress;
	uint8_t *RsvdAddress;
	uint8_t vc6;
} smbus_st;

int EFIAPI fcn_fffc5f08(EFI_PEI_SERVICES  **PeiServices,
		EFI_PEI_SMBUS_PPI         *This,
		EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress,
		EFI_SMBUS_DEVICE_COMMAND  Command,
		EFI_SMBUS_OPERATION       Operation,
		int                   PecCheck,
		uint32_t                     *Length,
		void                      *Buffer
		);

int EFIAPI fcn_fffc5c8e(EFI_PEI_SERVICES           **PeiServices,
		EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
		void *Ppi);


static int error_unsupported(void)
{
	return 0x80000003;
}

extern EFI_GUID gPeiSmbusPolicyPpiGuid;
extern EFI_GUID gEfiPeiMemoryDiscoveredPpiGuid;

void __attribute((regparm(2))) fcn_fffc5bf6(const EFI_PEI_SERVICES **pps, smbus_st *mem);
void __attribute((regparm(2))) fcn_fffc5bf6(const EFI_PEI_SERVICES **pps, smbus_st *mem)
{
	mem->sig = 0x626d7370;
	mem->pps = pps;
	(*pps)->LocatePpi(pps, &gPeiSmbusPolicyPpiGuid, 0, NULL, (void**)&mem->pei_smbus_policy_ppi);
	mem->smbus_base_addr = mem->pei_smbus_policy_ppi->BaseAddress;
	mem->smbus_ppi_desc.Flags = 0x80000010;
	mem->smbus_ppi_desc.Guid = &gEfiPeiSmbusPpiGuid;
	mem->smbus_ppi_desc.Ppi = (void*)&mem->smbus_ppi;
	mem->smbus_ppi.Execute = fcn_fffc5f08;
	mem->smbus_ppi.ArpDevice = (EFI_PEI_SMBUS_PPI_ARP_DEVICE)error_unsupported;
	mem->smbus_ppi.GetArpMap = (EFI_PEI_SMBUS_PPI_GET_ARP_MAP)error_unsupported;
	mem->smbus_ppi.Notify = (EFI_PEI_SMBUS_PPI_NOTIFY)error_unsupported;
	mem->notify_desc.Flags = 0x80000020;
	mem->notify_desc.Guid = &gEfiPeiMemoryDiscoveredPpiGuid;
	mem->notify_desc.Notify = fcn_fffc5c8e;
	mem->v38 = 0;
	mem->NumRsvdAddress = mem->pei_smbus_policy_ppi->NumRsvdAddress;
	mem->RsvdAddress = mem->pei_smbus_policy_ppi->RsvdAddress;
	mem->vc6 = 0;
}
