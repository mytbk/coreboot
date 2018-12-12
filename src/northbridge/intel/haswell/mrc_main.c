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

int __attribute((regparm(1))) do_raminit(struct pei_data *pd);
int __attribute((regparm(1))) heap_check(int n);
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
	heap_check(8);
	return rv;
}
