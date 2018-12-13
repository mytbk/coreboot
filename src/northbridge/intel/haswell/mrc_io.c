#include <arch/io.h>

#define BASE_ADDR (pci_mmio_read_config32(PCI_DEV(0,0,0), 0x60) & 0xfc000000)
#define BDF(bus, dev, func) ((bus << 20) + (dev << 15) + (func << 12))

void __attribute((regparm(3))) fcn_fffa0250(u32 bus, u32 dev, u32 func, u32 *arg1);

void __attribute((regparm(3))) fcn_fffa0250(u32 bus, u32 dev, u32 func, u32 *arg1)
{
	u32 t1, t2;

	*arg1 = 0;
	if (read8((void*)(BASE_ADDR + BDF(bus, dev, func) + 11)) != 6) { /* class code is bridge device */
		for (int i = 0x10; i <= 0x24; i += 4) { /* base address #0 to #5 */
			u32 addr = BDF(bus, dev, func) + i;
			t1 = read32((void*)(BASE_ADDR + addr));
			t2 = read32((void*)(BASE_ADDR + addr));
			write32((void*)(BASE_ADDR + addr), 0);
			t2 = read32((void*)(BASE_ADDR + addr));
			write32((void*)(BASE_ADDR + addr), ~0);
			t2 = read32((void*)(BASE_ADDR + addr));
			if (t1 == t2) {
				write32((void*)(BASE_ADDR + addr), t1);
			} else {
				if (t1 & 1) {
					write32((void*)(BASE_ADDR + addr), t1);
				} else {
					t2 = read32((void*)(BASE_ADDR + addr)) & 0xfffffff0;
					*arg1 -= t2;
					write32((void*)(BASE_ADDR + addr), t1);
					if ((t1 & 6) == 4)
						i += 4;
				}
			}
		}
	}
}
