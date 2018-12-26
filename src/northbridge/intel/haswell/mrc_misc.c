#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_sku.h"
#include "mrc_misc.h"
#include <arch/io.h>

int dummy_func(void)
{
	return 0;
}

void dmi_check_link(void)
{
	if (mrc_sku_type() == 1) {
		uint32_t lcap = RCBA32(0x21a4);
		uint32_t max_link_speed = lcap & 0xf;
		if (max_link_speed == 2) {
			RCBA8_AND_OR(0x21b0, 0xf0, 2);
		}
	}
}

void __attribute((regparm(2))) rtc_wait(void *ram_data, uint16_t val)
{
	uint16_t t1, t2;
	*(uint16_t*)(ram_data + 0xfee) = val;
	outw(val, 0x80);

	do {
		outb(0x48, 0x74);
		t1 = inb(0x75);
		outb(0x49, 0x74);
		t2 = inb(0x75);
		t2 = (t2 << 8) | t1;
	} while (t2 == val);
}
