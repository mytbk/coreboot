#include <console/console.h>
#include <arch/io.h>

void print_gbe(void *refcode_ppi);
void print_cf9_reset(void);
int PchIsGbeRegionValid(uint32_t rcba);

void print_gbe(void *refcode_ppi)
{
	int enable_gbe = *(char*)(refcode_ppi + 0x37e);
	uint32_t rcba = *(uint32_t*)(refcode_ppi + 4);
	uint32_t buc = *(uint32_t*)(rcba + 0x3414);

	printk(BIOS_DEBUG, "enable_gbe = %d\n"
			"gbe_region_valid = %d\n"
			"buc = 0x%x\n",
			enable_gbe, PchIsGbeRegionValid(rcba), buc);
}

void print_cf9_reset(void)
{
	printk(BIOS_DEBUG, "cf9_reset...\n");
}

void refcode_outb(uint16_t port, uint8_t value);
void refcode_outb(uint16_t port, uint8_t value)
{
	printk(BIOS_DEBUG, "outb(port=0x%x,val=0x%x)\n", port, value);
	outb(value, port);
}
