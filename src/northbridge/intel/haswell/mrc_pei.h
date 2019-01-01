#ifndef HASWELL_MRC_PEI_H_oo3evahX
#define HASWELL_MRC_PEI_H_oo3evahX

#include <stdint.h>
#include <stddef.h>
#include "pei_data.h"
#include <console/console.h>

#ifndef EFIAPI
#define EFIAPI /* __attribute((msabi)) */
#endif

#define PEI_SIGNATURE 0xfeadb00b

struct _EFI_PEI_SVC;
typedef struct _EFI_PEI_SVC EFI_PEI_SERVICES;

typedef int EFI_BOOT_MODE;
typedef void* EFI_PHYSICAL_ADDRESS;
typedef int (*EFI_PEI_REPORT_STATUS_CODE)(void);
#define EFI_PEI_RESET_SYSTEM void*
#define EFI_PEI_PCI_CFG_PPI void*
#define EFI_PEI_FFS_FIND_NEXT_VOLUME void*
#define EFI_PEI_FFS_FIND_SECTION_DATA void*
#define EFI_PEI_ALLOCATE_PAGES void*
#define EFI_PEI_ALLOCATE_POOL void*
#define EFI_PEI_SET_MEM void*
#define EFI_PEI_REINSTALL_PPI void*
#define EFI_PEI_SET_BOOT_MODE void*
#define EFI_PEI_FFS_FIND_NEXT_FILE void*

typedef struct {
	uint8_t g[16];
} EFI_GUID;

#include "CpuIo.h"

typedef struct {
	uint32_t Flags;
	EFI_GUID *Guid;
	void *Ppi;
} EFI_PEI_PPI_DESCRIPTOR;

struct _EFI_PEI_NOTIFY_DESCRIPTOR;
typedef struct _EFI_PEI_NOTIFY_DESCRIPTOR EFI_PEI_NOTIFY_DESCRIPTOR;

typedef int (EFIAPI *EFI_PEIM_NOTIFY_ENTRY_POINT)(
  EFI_PEI_SERVICES           **PeiServices,
  EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  void *Ppi);

struct _EFI_PEI_NOTIFY_DESCRIPTOR {
  uint32_t Flags;
  EFI_GUID *Guid;
  EFI_PEIM_NOTIFY_ENTRY_POINT Notify;
};

typedef int (EFIAPI *EFI_PEI_INSTALL_PPI)(
		const EFI_PEI_SERVICES            **PeiServices,
		const EFI_PEI_PPI_DESCRIPTOR      *PpiList
		);

typedef int (EFIAPI *EFI_PEI_LOCATE_PPI)(
		const EFI_PEI_SERVICES            **PeiServices,
		const EFI_GUID                    *Guid,
		unsigned long Instance,
		EFI_PEI_PPI_DESCRIPTOR      **PpiDescriptor ,
		void                        **Ppi
		);

typedef int (EFIAPI *EFI_PEI_NOTIFY_PPI)(
		const EFI_PEI_SERVICES                **PeiServices,
		const EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyList
		);

typedef int (EFIAPI *EFI_PEI_GET_BOOT_MODE)(
		const EFI_PEI_SERVICES            **PeiServices,
		EFI_BOOT_MODE                    *BootMode
		);

typedef int (EFIAPI *EFI_PEI_GET_HOB_LIST)(
		const EFI_PEI_SERVICES        **PeiServices,
		void                         **HobList
		);

typedef int (EFIAPI *EFI_PEI_CREATE_HOB)(
		const EFI_PEI_SERVICES            **PeiServices,
		uint16_t                            Type,
		uint16_t                            Length,
		void                          **Hob
		);

typedef int (EFIAPI *EFI_PEI_INSTALL_PEI_MEMORY)(void);

typedef void* (EFIAPI *EFI_PEI_COPY_MEM)(void *t, const void *s, size_t n);

typedef struct _EFI_PEI_SVC {
	uint8_t hdr[24];
	// PPI
	EFI_PEI_INSTALL_PPI               InstallPpi;
	EFI_PEI_REINSTALL_PPI             ReInstallPpi;
	EFI_PEI_LOCATE_PPI                LocatePpi;
	EFI_PEI_NOTIFY_PPI                NotifyPpi;
	// BootMode
	EFI_PEI_GET_BOOT_MODE             GetBootMode;
	EFI_PEI_SET_BOOT_MODE             SetBootMode;
	// HOB
	EFI_PEI_GET_HOB_LIST              GetHobList;
	EFI_PEI_CREATE_HOB                CreateHob;
	// Firmware Volume
	EFI_PEI_FFS_FIND_NEXT_VOLUME      FfsFindNextVolume;
	EFI_PEI_FFS_FIND_NEXT_FILE        FfsFindNextFile;
	EFI_PEI_FFS_FIND_SECTION_DATA     FfsFindSectionData;
	// PEI Memory
	EFI_PEI_INSTALL_PEI_MEMORY        InstallPeiMemory;
	EFI_PEI_ALLOCATE_PAGES            AllocatePages;
	EFI_PEI_ALLOCATE_POOL             AllocatePool;
	EFI_PEI_COPY_MEM                  CopyMem;
	EFI_PEI_SET_MEM                   SetMem;
	//
	// (the following interfaces are installed by publishing PEIM)
	// Status Code
	//
	EFI_PEI_REPORT_STATUS_CODE        ReportStatusCode;
	//
	// Reset
	//
	EFI_PEI_RESET_SYSTEM              ResetSystem;
	//
	// I/O Abstractions
	//
	EFI_PEI_CPU_IO_PPI                *CpuIo;
	EFI_PEI_PCI_CFG_PPI               *PciCfg;
} EFI_PEI_SERVICES;

typedef struct {
	uint16_t htype;
	uint16_t hlen;
	int data[1];
} EFI_HOB_DATA;

struct _EFI_HOB {
	struct _EFI_HOB *next;
	EFI_HOB_DATA hobdata;
};

typedef struct _EFI_HOB EFI_HOB;

typedef struct {
	uint32_t sig;
	EFI_PEI_SERVICES peisv; // 0x00, 0x04
	int bootmode; // 0x68, 0x6c
	EFI_PEI_PPI_DESCRIPTOR installedPpi[20]; // 0x70
	int nb_installed_ppi; // 0x160
	EFI_PEI_NOTIFY_DESCRIPTOR notify_dsc[20]; // 0x164
	int nb_notify_desc; // 0x254
	EFI_HOB *hobList; // 0x258
	struct pei_data *pei_data; // 0x25c
} MRC_PEI;

int EFIAPI PeiInstallPpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_PEI_PPI_DESCRIPTOR *PpiList);
int EFIAPI PeiLocatePpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_GUID *Guid,
		unsigned long Instance,
		EFI_PEI_PPI_DESCRIPTOR **PpiDescriptor,
		void **Ppi);
int EFIAPI PeiNotifyPpi(const EFI_PEI_SERVICES **PeiServices,
		const EFI_PEI_NOTIFY_DESCRIPTOR *NotifyList);
int EFIAPI PeiGetBootMode(const EFI_PEI_SERVICES **PeiServices,
		int *BootMode);
int EFIAPI PeiCreateHob(const EFI_PEI_SERVICES **PeiServices,
		uint16_t Type, uint16_t Length, void **Hob);
int EFIAPI PeiGetHobList(const EFI_PEI_SERVICES **PeiServices, void **HobList);

int __attribute((regparm(1))) PeiServiceGetBootMode(int *BootMode);
int __attribute((regparm(1)))
PeiServiceNotifyPpi(const EFI_PEI_NOTIFY_DESCRIPTOR *NotifyList);

void init_mrc_pei(MRC_PEI *pei, struct pei_data *pd);
EFI_HOB_DATA * __attribute((regparm(2)))
locate_hob(EFI_GUID *guid, uint16_t v);

#define gpPei ((const EFI_PEI_SERVICES***)0xff7d7538)

static inline
MRC_PEI *PEI_FROM_PEI_SERVICE(const EFI_PEI_SERVICES *ps)
{
	MRC_PEI *pei = (MRC_PEI *)((void*)ps - 4);
	if (pei->sig != PEI_SIGNATURE)
		die("PEI signature error!\n");
	return pei;
}

#endif
