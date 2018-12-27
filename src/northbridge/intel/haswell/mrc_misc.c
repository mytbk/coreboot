#include <southbridge/intel/lynxpoint/pch.h>
#include "mrc_sku.h"
#include "mrc_misc.h"
#include <arch/io.h>
#include <arch/pci_ops.h>

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

uint8_t __attribute((regparm(1))) pci_setup_bridge(uint8_t bus)
{
	uint8_t a = bus;
	uint8_t r = 0;
	for (int i = 0; i < 0x20; i++) {
		uint32_t dev = PCI_DEV(bus, i, 0);
		uint16_t vid = pci_read_config16(dev, 0);
		if (vid == 0xffff) continue;
		uint16_t cls = pci_read_config16(dev, 0xa);
		if (cls != 0x604) continue; // PCI_CLASS_BRIDGE_PCI
		/* primary bus number */
		pci_write_config8(dev, 0x18, bus);
		a++;
		/* secondary bus number */
		pci_write_config8(dev, 0x19, a);
		/* subordinate bus number */
		pci_write_config8(PCI_DEV(a, i, 0), 0x1a, 0xff);
		pci_write_config16(PCI_DEV(a, 0, 0), 0, 0);
		r = pci_setup_bridge(a);
		pci_write_config8(dev, 0x1a, r);
		a = r;
	}
	return (r == 0)?bus:r;
}
