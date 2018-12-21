#include <stdint.h>

int pei_get_platform_memsize(void **peisv, void *_this_, uint64_t *memsz);
int pei_choose_ranges(void **peisv, void *_this_,
		uint32_t *oprom_mask, uint32_t *smram_mask,
		uint32_t *gfxram_mask, uint32_t *pcimem_mask);

int pei_get_platform_memsize(void **peisv, void *_this_, uint64_t *memsz)
{
	*memsz = 0x1000000;
	return 0;
}

int pei_choose_ranges(void **peisv, void *_this_,
		uint32_t *oprom_mask, uint32_t *smram_mask,
		uint32_t *gfxram_mask, uint32_t *pcimem_mask)
{
	*oprom_mask = 0;
	*smram_mask = 0;
	*gfxram_mask = 0;
	*pcimem_mask = 0;
	return 0;
}
