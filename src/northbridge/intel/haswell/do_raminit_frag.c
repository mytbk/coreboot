#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>

// loc_fffa3c2e
//
void io_fffa3c2e(void);
void io_fffa3c2e(void)
{
	u32 reg3410;
	u8 t1, t2, tmp;

	RCBA32_OR(0x3410, 0x10);
	reg3410 = RCBA32(0x3410);
	t1 = inb(0x70) & 0x80;
	t2 = t1 | 0xa;
	RCBA32_AND_OR(0x3410, 0xffffffef, 0);
	reg3410 = RCBA32(0x3410);
	outb(t2, 0x70);
	tmp = (inb(0x71) & 0x8f) | 0x60;
	outb(tmp, 0x71);
	t1 |= 0xb;
	outb(t1, 0x70);
	tmp = inb(0x71) | 0x80;
	outb(tmp, 0x71);
	outb(t2, 0x70);
	tmp = (inb(0x71) & 0x8f) | 0x20;
	outb(tmp, 0x71);
	outb(t1, 0x70);
	tmp = inb(0x71) & 0x7f;
	outb(tmp, 0x71);
}
