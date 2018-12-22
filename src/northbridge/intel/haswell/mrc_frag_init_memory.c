#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/pci_ops.h>

int frag_fffc1d20(void);
int frag_fffc1d20(void)
{
	u32 tmp = pci_read_config32(PCI_DEV(0, 0x1f, 0), 0xa0);
	tmp >>= 16;
	tmp &= 0xa0;
	return (tmp == 0xa0)?1:0;
}
