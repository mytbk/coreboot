#include <console/console.h>
#include <arch/io.h>

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

void refcode_outb(uint16_t port, uint8_t value);
void refcode_outb(uint16_t port, uint8_t value)
{
	printk(BIOS_DEBUG, "outb(port=0x%x,val=0x%x)\n", port, value);
	outb(value, port);
}
