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

#include "pei_data.h"
#include <console/console.h>

static int *STACK_TOP = (int *)0xff800000;
static int *STACK_BTM = (int *)0xff7d7544;

struct mrc_heap {
	size_t sz;
	void *start;
	int data[0];
};

static struct mrc_heap *HEAP = (struct mrc_heap *)0xff7d0000;
#define MAX_HEAP_SIZE ((void *)STACK_BTM - (void *)HEAP->data - 16)
#define POOL_COOKIE 0x900ddea1

int __attribute((regparm(1))) do_raminit(struct pei_data *pd);
void *__attribute((regparm(1))) mrc_alloc(int n);
int mrc_main(struct pei_data *pd);

int mrc_main(struct pei_data *pd)
{
	int stkwords = (STACK_TOP - STACK_BTM);
	int lowsize = stkwords / 8;
	int rv;

	for (int i = 0; i < lowsize; i += 0x100) {
		for (int j = 0; j < 4; j++)
			STACK_BTM[i + j] = 0xdeadbeef;
	}

	rv = do_raminit(pd);

	for (int i = 0; i < lowsize; i += 0x100) {
		for (int j = 0; j < 4; j++) {
			if (STACK_BTM[i + j] != 0xdeadbeef) {
				mrc_printk("Reference code used "
						"approx 0x%x/0x%x of stack.\n",
						(stkwords - i) * 4,
						stkwords * 4);
				if (i == 0) {
					mrc_printk("Stack completely exhaused!\n");
					while (1)
						;
				}
			}
		}
	}

	mrc_printk("Sanity checking heap.\n");
	mrc_alloc(8);
	return rv;
}

void *__attribute((regparm(1))) mrc_alloc(int n)
{
	size_t alloc = (n + 3) & (-4);
	size_t sz = HEAP->sz;

	if (sz == 0) {
		HEAP->start = HEAP->data;
	} else {
		if (*((uint32_t *)(HEAP->start + sz)) != POOL_COOKIE) {
			mrc_printk("%s:%d pool cookie corrupted...\n",
					"GlueAllocatePool", 0x35);
			while (1)
				;
		}
	}

	size_t newsz = alloc + sz;
	if (newsz <= MAX_HEAP_SIZE) {
		HEAP->sz = newsz;
		*((uint32_t *)(HEAP->start + newsz)) = POOL_COOKIE;
		return HEAP->start + sz;
	}
	mrc_printk("%s:%d failed to allocate %d bytes...\n",
			"GlueAllocatePool", 0x43);
	while (1)
		;
}
