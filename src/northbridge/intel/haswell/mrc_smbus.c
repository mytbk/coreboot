/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/io.h>

u8 __attribute((regparm(3))) mrc_smbus_inb(u32 addr);
void __attribute((regparm(3))) mrc_smbus_outb(u32 addr, u8 v);

u8 __attribute((regparm(3))) mrc_smbus_inb(u32 addr)
{
	u32 pciexbar = pci_mmio_read_config32(PCI_DEV(0, 0, 0), 0x60);
	u32 smb_base = read32((void*)((pciexbar & 0xfc000000) + 0xfb020)) & 0xffe0;
	return inb(smb_base + addr);
}

void __attribute((regparm(3))) mrc_smbus_outb(u32 addr, u8 v)
{
	u32 pciexbar = pci_mmio_read_config32(PCI_DEV(0, 0, 0), 0x60);
	u32 smb_base = read32((void*)((pciexbar & 0xfc000000) + 0xfb020)) & 0xffe0;
	outb(v, smb_base + addr);
}
