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

int EFIAPI smbus_exec(EFI_PEI_SERVICES  **PeiServices,
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
	mem->smbus_ppi.Execute = smbus_exec;
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

#if 0
int EFIAPI smbus_exec(EFI_PEI_SERVICES **PeiServices,
		EFI_PEI_SMBUS_PPI *This,
		EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
		EFI_SMBUS_DEVICE_COMMAND Command,
		EFI_SMBUS_OPERATION Operation,
		int PecCheck, uint32_t *Length, void *Buffer)
{
    u32 addr = SlaveAddress & 0x7f;
    cl = PecCheck;
    edi = Length;
    local_25h = cl;
    if (Operation > 1) {
        if (Buffer == NULL || Length == NULL) {
            return 0x80000002;
        }
    }
    ebx = 0x80000012;
    al = mrc_smbus_inb (0);
    if ((al & 0x40) != 0) {
        goto loc_fffc642a;
    }
    if ((al & 1) != 0) {
        edx = 0xff;
        eax = 0;
        goto loc_fffc6416;
    }
    mrc_smbus_outb (0, al);
    local_1dh = addr * 2 + 1;
    local_24h = 3;
    local_1eh = addr * 2;
    local_20h = 0;
    local_30h = Operation & 0xfffffffd;
label_1:
    al = Command;
    local_1fh = al;
    switch (Operation) {
	    case EfiSmbusQuickRead:
		    esi = local_1dh;
		    if (local_25h == 1) goto loc_fffc6126;
		    local_1ch = 0;
		    goto loc_fffc6120;
	    case EfiSmbusQuickWrite:
		    esi = local_1eh;
		    if (local_25h == 1) goto loc_fffc6126;
		    local_1ch = 0;
		    goto loc_fffc6120;
	    case EfiSmbusReceiveByte:
		    esi = local_1dh;
		    local_1ch = 4;
		    ebx = (*(u32*)(edi) < 1)? 0x80000005:0;
		    *(u32*)(edi) = 1;
		    goto loc_fffc60f4;
	    case EfiSmbusSendByte:
		    esi = local_1eh;
		    ecx = Buffer; cl = *(u8*)ecx; local_1fh = cl;
		    local_1ch = 4;
		    ebx = (*(u32*)(edi) < 1)? 0x80000005:0;
		    *(u32*)(edi) = 1;
		    goto loc_fffc60f4;
	    case EfiSmbusReadByte:
		    esi = local_1dh;
		    goto loc_fffc6010;
	    case EfiSmbusWriteByte:
		    ecx = Buffer;
		    mrc_smbus_outb(5, *(u8*)ecx);
		    esi = local_1eh;
		    *(u32*)edi = 1;
		    goto loc_fffc6010;
	    case EfiSmbusReadWord:
		    esi = local_1dh;
		    ebx = (*(u32*)edi < 2)? 0x80000005:0;
		    *(u32*)edi = 2;
		    goto loc_fffc608e;
	    case EfiSmbusWriteWord:
		    mrc_smbus_outb(6, ((u8*)Buffer)[1]);
		    mrc_smbus_outb(5, ((u8*)Buffer)[0]);
		    esi = local_1eh;
		    ebx = (*(u32*)edi < 2)? 0x80000005:0;
		    *(u32*)edi = 2;
		    goto loc_fffc608e;
	    case EfiSmbusReadBlock:
		    esi = local_1dh;
		    goto loc_fffc60b0;
	    case EfiSmbusWriteBlock:
		    mrc_smbus_outb(5, *(u8*)edi);
		    esi = local_1eh;
		    local_20h = cl = *(u8*)edi;
		    goto loc_fffc60b0;
	    case EfiSmbusProcessCall:
		    mrc_smbus_outb(6, ((u8*)Buffer)[1]);
		    mrc_smbus_outb(5, ((u8*)Buffer)[0]);
		    ebx = (*(u32*)edi < 2)? 0x80000005:0;
		    local_1ch = 0x10;
		    *(u32*)edi = 2;
		    esi = local_1dh;
		    edx = 0; goto loc_fffc6142;
	    case EfiSmbusBWBRProcessCall:
		    eax = *(u32*)edi - 1;
		    if (eax > 0x1f) goto loc_fffc6138;
		    mrc_smbus_outb(5, *(u8*)edi);
		    cl = *(u8*)edi;
		    local_1ch = 0x1c;
		    esi = local_1dh;
		    local_20h = cl;
		    goto loc_fffc6134;
	    default:
		    break;
    }
loc_fffc6138:
    ebx = 0x80000002;
loc_fffc63f4:
    mrc_smbus_outb(0, 0xff);
    mrc_smbus_outb(0xc, 1);
    mrc_smbus_outb(0xd, 0);
    return ebx;

loc_fffc6120:
    edx = 0; ebx = 0; 
    if (local_25h == 1)
	    dl |= 1;
    mrc_smbus_outb(0xd, dl);
    al = mrc_smbus_inb(2);
    if (local_30h != 9) {
	    mrc_smbus_outb(4, (u8)esi);
	    if (Operation != 4) {
		    mrc_smbus_outb(3, local_1fh);
	    } else {
		    if (*(u32*)edi > 1) {
			    mrc_smbus_outb(6, local_1fh);
		    } else {
			    mrc_smbus_outb(3, local_1fh);
		    }
	    }
	    esi = 0x186a0;
	    mrc_smbus_outb(2, local_1ch + 0x40);
	    while (esi--) {
		    al = mrc_smbus_inb(0);
		    if (al & 0x8e) {
			    if (al & 4) {
				    al = mrc_smbus_inb(0xc) & 1;
				    ebx = (al < 1)?0xffffffec:0;
				    ebx -= 0x7fffffe5;
				    goto loc_fffc63f4;
			    }
			    else goto loc_fffc622a;
		    }
		    usleep(10);
	    }
	    ebx = 0x80000012;
	    goto loc_fffc63f4;
    } else {
	    edx = local_20h;
	    ecx = 0;
	    local_2ch = edx;
	    if (ecx < local_2ch) goto loc_fffc618a;
	    else goto loc_fffc6173;
    }
loc_fffc6126:
    ebx = 0x80000003;
    goto loc_fffc63f4;
}
#endif
