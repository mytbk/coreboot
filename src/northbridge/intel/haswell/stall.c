#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include "stall.h"
#include "mrc_utils.h"

void __attribute((regparm(1))) usleep(int usec)
{
	u32 timerp = pci_read_config32(PCH_LPC_DEV, PMBASE) + PM1_TMR;
	u32 tm = inl(timerp) & 0xffffff;
	u32 end = usec * 358 / 100 + tm + 1; // 3.58 MHz clock
	u32 hi = end >> 24;
	u32 lo = end & 0xffffff;

	while (hi != 0 || lo > tm) {
		u32 now = inl(timerp) & 0xffffff;
		if (now > tm) { // not rollback
			tm = now;
			continue;
		} else {
			if (hi == 0)
				return;
			hi--;
			tm = now;
		}
	}
}

int EFIAPI PeiStall(EFI_PEI_SERVICES **PeiServices,
		EFI_PEI_STALL_PPI *This,
		uint32_t usec)
{
	if (usec)
		usleep(usec);
	return 0;
}
