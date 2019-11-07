#ifndef MRC_INIT_MEMORY_H
#define MRC_INIT_MEMORY_H

#include "pei_ram.h"

int __attribute((regparm(1))) mrc_init_memory(const EFI_PEI_SERVICES **pps);

int __attribute((regparm(3))) fcn_fffa1d20(int bootmode, int v, void *addr,
		const EFI_PEI_SERVICES **pps /* not used */, void *raminit_ppi);
void frag_fffc1c07(void);
int frag_fffc1d20(void);
int superfrag_fffc1ea8(int bootmode, void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl);
int frag_fffc1fc3(void);
int frag_fffc2026(void *ram_data);
void __attribute((regparm(1))) fcn_fffa9196(void *a);
int copy_mrc_input(pei_raminit_ppi *ppi, int bootmode, void* dst);
void *create_raminit_hob(void);
int test_memory(void);

#endif
