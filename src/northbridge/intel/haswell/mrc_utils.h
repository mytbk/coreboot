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

void __attribute((regparm(3))) mrc_setmem(void *s, size_t n, int c);
void __attribute((regparm(3))) mrc_memcpy(void *dst, const void *src, size_t n);
void __attribute((regparm(3))) mrc_fillword(int *s, int c, size_t n);
void __attribute((regparm(3))) mrc_zeromem(void *s, size_t n);
char __attribute((regparm(3))) mrc_highest_bit(int a);
void __attribute((regparm(1))) printGuid(const void *g);
void *__attribute((regparm(1))) mrc_alloc(int n);
void __attribute((regparm(1))) usleep(int usec);
uint32_t __attribute((regparm(2))) crc32(uint8_t data[], size_t len);
