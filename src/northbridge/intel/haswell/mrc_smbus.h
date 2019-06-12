#include <arch/io.h>

u8 __attribute((regparm(3))) mrc_smbus_inb(u32 addr);
void __attribute((regparm(3))) mrc_smbus_outb(u32 addr, u8 v);
