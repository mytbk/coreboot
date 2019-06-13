#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include "mrc_wdt.h"

static uint8_t *status = (uint8_t *)0xff7d7540;

static uint32_t pm54(void)
{
	/* 0x54 is C3_RES, but it seems not in lynxpoint */
	uint32_t pmbase = pci_read_config32(PCH_LPC_DEV, PMBASE) & 0xfffc;
	return pmbase + 0x54;
}

static int fcn_fffc5b14(void)
{
	uint32_t tmp = inl(pm54());
	return ((tmp >> 14) & 1);
}

static int fcn_fffc5b27(void)
{
	uint32_t tmp = inl(pm54());
	return ((tmp & 0x3f0000)?1:0);
}

static void fcn_fffc5b3c(void)
{
	*status = 1;
	u32 tmp = inl(pm54()) & 0xffbf7fff;
	outl(tmp, pm54());
}

static int fcn_fffc5b65(void)
{
	u32 tmp = inl(pm54());
	return ((tmp >> 0x17) & 1);
}

static void fcn_fffc5b78(void)
{
	u32 tmp = inl(pm54()) & 0xffbf3fff;
	outl(tmp, pm54());
}

static int fcn_fffc5b9a(uint32_t v)
{
	v--;
	if (v > 0x3fe)
		return 0x80000002;
	u32 tmp = inl(pm54());
	if (*status == 0) {
		tmp |= 0x40e000;
	} else {
		tmp |= 0xe000;
	}
	tmp &= 0xfffffc00;
	tmp |= v;
	outl(tmp, pm54());
	tmp |= 0x80000000;
	outl(tmp, pm54());
	return 0;
}

const PEI_WDT_PPI mrc_wdt_ppi = {
	fcn_fffc5b9a,
	fcn_fffc5b65,
	fcn_fffc5b78,
	fcn_fffc5b3c,
	fcn_fffc5b27,
	fcn_fffc5b14,
};
