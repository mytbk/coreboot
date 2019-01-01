#include <southbridge/intel/lynxpoint/pch.h>
#include <console/console.h>
#include "mrc_pch.h"

#define IOBP_RETRY 10000000
static inline int iobp_poll(void)
{
	unsigned try;

	for (try = IOBP_RETRY; try > 0; try--) {
		u16 status = RCBA16(IOBPS);
		if ((status & IOBPS_READY) == 0)
			return 1;
	}

	printk(BIOS_ERR, "IOBP: timeout waiting for transaction to complete\n");
	return 0;
}

static u32 pch_iobp_read(u32 address)
{
	u16 status;

	if (!iobp_poll())
		return 0;

	/* Set the address */
	RCBA32(IOBPIRI) = address;

	/* READ OPCODE */
	status = RCBA16(IOBPS);
	status &= ~IOBPS_MASK;
	status |= IOBPS_READ;
	RCBA16(IOBPS) = status;

	/* Undocumented magic */
	RCBA16(IOBPU) = IOBPU_MAGIC;

	/* Set ready bit */
	status = RCBA16(IOBPS);
	status |= IOBPS_READY;
	RCBA16(IOBPS) = status;

	if (!iobp_poll())
		return 0;

	/* Check for successful transaction */
	status = RCBA16(IOBPS);
	if (status & IOBPS_TX_MASK) {
		printk(BIOS_ERR, "IOBP: read 0x%08x failed\n", address);
		return 0;
	}

	/* Read IOBP data */
	return RCBA32(IOBPD);
}

static void pch_iobp_write(u32 address, u32 data)
{
	u16 status;

	if (!iobp_poll())
		return;

	/* Set the address */
	RCBA32(IOBPIRI) = address;

	/* WRITE OPCODE */
	status = RCBA16(IOBPS);
	status &= ~IOBPS_MASK;
	status |= IOBPS_WRITE;
	RCBA16(IOBPS) = status;

	RCBA32(IOBPD) = data;

	/* Undocumented magic */
	RCBA16(IOBPU) = IOBPU_MAGIC;

	/* Set ready bit */
	status = RCBA16(IOBPS);
	status |= IOBPS_READY;
	RCBA16(IOBPS) = status;

	if (!iobp_poll())
		return;

	/* Check for successful transaction */
	status = RCBA16(IOBPS);
	if (status & IOBPS_TX_MASK) {
		printk(BIOS_ERR, "IOBP: write 0x%08x failed\n", address);
		return;
	}

	printk(BIOS_INFO, "IOBP: set 0x%08x to 0x%08x\n", address, data);
}

void pch_iobp_update(u32 address, u32 andvalue, u32 orvalue)
{
	u32 data = pch_iobp_read(address);

	/* Update the data */
	data &= andvalue;
	data |= orvalue;

	pch_iobp_write(address, data);
}

int __attribute((regparm(3))) mrc_pch_iobp_read(u32 rcba, u32 addr, u32 *data)
{
	u32 ret = pch_iobp_read(addr);
	if (ret == 0) {
		printk(BIOS_ERR, "pch_iobp_read 0x%08x failed\n", addr);
		return 0x80000007;
	}
	*data = ret;
	return 0;
}

int __attribute((regparm(3))) mrc_pch_iobp_update(u32 rcba, u32 addr, u32 andv, u32 orv)
{
	pch_iobp_update(addr, andv, orv);
	return 0;
}
