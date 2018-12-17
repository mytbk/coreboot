#include "mrc_pei.h"

typedef struct _EFI_PEI_STALL_PPI EFI_PEI_STALL_PPI;

typedef int (EFIAPI *EFI_PEI_STALL)(
  EFI_PEI_SERVICES **PeiServices,
  EFI_PEI_STALL_PPI *This,
  uint32_t usec);

struct _EFI_PEI_STALL_PPI {
	u32 resolution;
	EFI_PEI_STALL Stall;
};

int EFIAPI PeiStall(EFI_PEI_SERVICES **PeiServices,
		EFI_PEI_STALL_PPI *This,
		uint32_t usec);
