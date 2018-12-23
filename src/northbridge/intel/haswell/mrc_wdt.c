#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/io.h>

static uint8_t *status = (uint8_t *)0xff7d7540;

int fcn_fffc5b14(void);
int fcn_fffc5b27(void);
void fcn_fffc5b3c(void);
int fcn_fffc5b65(void);
void fcn_fffc5b78(void);
int fcn_fffc5b9a(uint32_t v);

static uint32_t pm54(void)
{
	/* 0x54 is C3_RES, but it seems not in lynxpoint */
	uint32_t pmbase = pci_read_config32(PCH_LPC_DEV, PMBASE) & 0xfffc;
	return pmbase + 0x54;
}

int fcn_fffc5b14(void)
{
	uint32_t tmp = inl(pm54());
	return ((tmp >> 14) & 1);
}

int fcn_fffc5b27(void)
{
	uint32_t tmp = inl(pm54());
	return ((tmp & 0x3f0000)?1:0);
}

void fcn_fffc5b3c(void)
{
	*status = 1;
	u32 tmp = inl(pm54()) & 0xffbf7fff;
	outl(tmp, pm54());
}

int fcn_fffc5b65(void)
{
	u32 tmp = inl(pm54());
	return ((tmp >> 0x17) & 1);
}

void fcn_fffc5b78(void)
{
	u32 tmp = inl(pm54()) & 0xffbf3fff;
	outl(tmp, pm54());
}

int fcn_fffc5b9a(uint32_t v)
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

const void* const mrc_wdt_ppi[6] = {
	(const void*) fcn_fffc5b9a,
	(const void*) fcn_fffc5b65,
	(const void*) fcn_fffc5b78,
	(const void*) fcn_fffc5b3c,
	(const void*) fcn_fffc5b27,
	(const void*) fcn_fffc5b14,
};
