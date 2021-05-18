#include <console/console.h>
#include <stdint.h>

void print_gbe(void *refcode_ppi);
int PchIsGbeRegionValid(uint32_t rcba);

void print_gbe(void *refcode_ppi)
{
	int enable_gbe = *(char*)(refcode_ppi + 0x37e);
	uint32_t rcba = *(uint32_t*)(refcode_ppi + 4);

	printk(BIOS_DEBUG, "enable_gbe = %d\n"
			"gbe_region_valid = %d\n",
			enable_gbe, PchIsGbeRegionValid(rcba));
}
