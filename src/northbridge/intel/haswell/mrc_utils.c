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

#include <string.h>
#include <console/console.h>

void __attribute((regparm(3))) mrc_setmem(void *s, size_t n, int c);
void __attribute((regparm(3))) mrc_memcpy(void *dst, const void *src, size_t n);
void __attribute((regparm(3))) mrc_fillword(int *s, int c, size_t n);
void __attribute((regparm(3))) mrc_zeromem(void *s, size_t n);
char __attribute((regparm(3))) mrc_highest_bit(int a);
void __attribute((regparm(1))) printGuid(const void *g);

void __attribute((regparm(3))) mrc_setmem(void *s, size_t n, int c)
{
	memset(s, c, n);
}

void __attribute((regparm(3))) mrc_fillword(int *s, int c, size_t n)
{
	for (size_t i = 0; i < n; i++)
		s[i] = c;
}

void __attribute((regparm(3))) mrc_memcpy(void *dst, const void *src, size_t n)
{
	memcpy(dst, src, n);
}

void __attribute((regparm(3))) mrc_zeromem(void *s, size_t n)
{
	memset(s, 0, n);
}

char __attribute((regparm(3))) mrc_highest_bit(int a)
{
	int result = 0;

	if (a == -1)
		return 0;

	for (int i = 0; i < 32; i++) {
		if (a & (1 << i))
			result = i + 1;
	}

	return result;
}

void __attribute((regparm(1))) printGuid(const void *g)
{
	struct guid {
		u32 g0;
		u16 g4;
		u16 g6;
		u8 g8[8];
	};
	const struct guid *gg = g;
	mrc_printk("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}\n",
			gg->g0, gg->g4, gg->g6, gg->g8[0], gg->g8[1],
			gg->g8[2], gg->g8[3], gg->g8[4], gg->g8[5],
			gg->g8[6], gg->g8[7]);
}
