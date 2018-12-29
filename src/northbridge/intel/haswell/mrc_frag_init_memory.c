#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/pci_ops.h>
#include "mrc_pei.h"
#include <cpu/x86/msr.h>
#include "mrc_utils.h"
#include <arch/cpu.h>
#include "pei_ram.h"
#include <console/console.h>
#include "mrc_misc.h"

int frag_fffc1d20(void);
int frag_fffc1d20(void)
{
	u32 tmp = pci_read_config32(PCI_DEV(0, 0x1f, 0), 0xa0);
	tmp >>= 16;
	tmp &= 0xa0;
	return (tmp == 0xa0)?1:0;
}

int frag_fffc1fc3(void);
int frag_fffc1fc3(void)
{
	u32 tmp = pci_read_config32(PCI_DEV(0, 0x1f, 0), 0xa0);
	tmp &= 0xff7f0000;
	pci_write_config32(PCI_DEV(0, 0x1f, 0), 0xa0, tmp);
	return 0;
}

static const EFI_PEI_SERVICES ***gpPei = (const EFI_PEI_SERVICES***)0xff7d7538;
extern EFI_GUID mEfiMemoryRestoreDataGuid;

void *create_raminit_hob(void);
void *create_raminit_hob(void)
{
	void *hob;
	const EFI_PEI_SERVICES **pps = *gpPei;
	int res = (*pps)->CreateHob(pps, 4, 0x503b, &hob);
	if (res < 0)
		return hob;

	memcpy(hob + 8, &mEfiMemoryRestoreDataGuid, 16);
	memset(hob + 0x18, 0, 0x5022);
	return hob;
}

static void frag_fffc1cd2(void)
{
	for (int i = 0; i < 0x2ee; i++) {
		uint8_t tmp = read8((void*)0xfed40000);
		if (tmp == 0xff)
			break;
		if (tmp & 0x80) {
			if (tmp & 1)
				break;
			else
				return;
		}
		usleep(1000);
	}
	wrmsr(0x2e6, (msr_t){0, 0});
}

struct cpu_model_id
{
	int stepping;
	int model;
};

int haswell_family_model(void);
int haswell_stepping(void);

#define HASWELL_FAMILY_MOBILE 0x306c0
#define HASWELL_FAMILY_ULT 0x40650
#define HASWELL_FAMILY_GT3E 0x40660

static void set_cpuid(struct cpu_model_id *mycpu)
{
	int model = haswell_family_model();
	int stepping = haswell_stepping();
	if (model == HASWELL_FAMILY_ULT || model == HASWELL_FAMILY_GT3E) {
		mycpu->model = model;
		if (stepping == 0) {
			mycpu->stepping = 0;
			return;
		} else {
			mycpu->stepping = (stepping == 1)?1:0;
			return;
		}
	}
	if (model == HASWELL_FAMILY_MOBILE) {
		mycpu->model = HASWELL_FAMILY_MOBILE;
		if (stepping == 2 || stepping == 3) {
			mycpu->stepping = stepping;
			return;
		} else {
			mycpu->stepping = (stepping != 1)?3:1;
			return;
		}
	}
}

int test_memory(void);
int test_memory(void)
{
	for (size_t i = 0; i < 0x1000; i++) {
		*(uint8_t*)i = (uint8_t)i;
	}

	for (int j = 0; j < 20; j++) {
		for (size_t i = 0; i < 0x1000; i++) {
			if (*(uint8_t*)i != (uint8_t)i)
				return -1;
		}
	}
	return 0;
}

void frag_fffc1c07(void);
int initialize_txt(void);
void frag_fffc1c07()
{
	struct cpuid_result res;
	int t;

	res = cpuid_ext(1, 0);
	if ((u8)res.ecx & 0x40) {
		res = cpuid_ext(1, 0);
		t = 0;
		if (res.ecx & 0x40) {
			t = initialize_txt();
		}
		if (t != 1)
			frag_fffc1cd2();
	}
}

extern EFI_GUID ref_fffcd4a4;
static void * frag_fffc1f53(uint32_t *wb)
{
	void *hob = locate_hob(&ref_fffcd4a4, 4);
	if (hob == NULL)
		return NULL;
	uint8_t tmp = *(uint8_t*)(hob + 0x21) + *(uint8_t*)(hob + 0x19);
	if (tmp != 0)
		*wb = tmp;
	return hob;
}

int copy_mrc_input(pei_raminit_ppi *ppi, int bootmode, void* dst);
int copy_mrc_input(pei_raminit_ppi *ppi, int bootmode, void* dst)
{
	void *inp = ppi->mrc_input;
	if (inp == NULL)
		return 0;
	if (bootmode == 4)
		return 0;

	if (crc32(inp + 4, 0xfd0) != *(uint32_t*)inp)
		return 0;

	memcpy(dst, inp, 0xfd4);
	return 1;
}

void __attribute((regparm(1))) fcn_fffa9196(void *a);
static int check_data_structs(void *ram_data, pei_raminit_ppi *ppi)
{
	uint32_t chk;
	uint32_t crc;

	pei_ram_param *parm = ppi->ram_param;
	fcn_fffa9196((void*)&chk);
	crc = crc32((void*)parm, 0xc8);

	if (chk != *(uint32_t*)(ram_data + 0x9dc))
		return 1;

	if (*(uint32_t*)(ram_data + 0x9d8)
			!= *(uint32_t*)(ram_data + 0x1005))
		return 1;

	if (*(uint32_t*)(ram_data + 0x9d4)
			!= *(uint32_t*)(ram_data + 0x1001))
		return 1;

	if (*(uint32_t*)(ram_data + 0x9e0) != crc)
		return 1;

	return 0;
}

/*
ram_data: ebp - 0x503a
ppi: [ebp - 0x50a4]
v50c4: [ebp - 0x50c4]
return value moved to edi
*/
static int frag_fffc1ea8(void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl)
{
	if (v50c4 - 1 > 1) {
		if (bl == 1) {
			if (ppi->ram_param->v2c[0x2a] != 0) {
				if (check_data_structs(ram_data, ppi) == 0)
					return 3;
			}
		}
		mrc_zeromem(ram_data + 4, 0xfd4);
		return 0;
	}
	if (bl == 0) {
		mrc_zeromem(ram_data + 4, 0xfd4);
		return 0;
	}
	if (check_data_structs(ram_data, ppi) == 1) {
		mrc_zeromem(ram_data + 4, 0xfd4);
		return 0;
	}
	void * mchbar = (void*)ppi->ram_data->mchbar;
	uint32_t reg_5d10 = read32(mchbar + 0x5d10);
	uint32_t reg_5d14 = read32(mchbar + 0x5d14);
	if (reg_5d10 | reg_5d14)
		return v50c4;

	if (v50c4 - 1 == 0) {
		mrc_zeromem(ram_data + 4, 0xfd4);
		return 0;
	}
	return 2;
}

int __attribute((regparm(3))) fcn_fffa1d20(int bootmode, int v, void *addr,
		EFI_PEI_SERVICES **pps /* not used */, void *raminit_ppi);

int superfrag_fffc1ea8(int bootmode, void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl);
int superfrag_fffc1ea8(int bootmode, void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl)
{
	set_cpuid(ram_data + 0x1001);
	int ret = frag_fffc1ea8(ram_data, ppi, v50c4, bl);
	frag_fffc1f53(ram_data + 0x105f);
	*(u32*)(ram_data + 0x1025) = fcn_fffa1d20(bootmode, ret, ram_data + 0xfd8, NULL, ppi);
	*(u32*)(ram_data + 0x104f) = 0;
	return ret;
}

#ifndef __packed
#if defined(__WIN32) || defined(__WIN64)
#define __packed __attribute__((gcc_struct, packed))
#else
#define __packed __attribute__((packed))
#endif
#endif

typedef struct _ram_st {
	int (*func)(void*);
	uint16_t v1;
	uint32_t v2;
	uint8_t v3;
	uint8_t v4;
} __packed ram_st;
extern ram_st ref_fffcbf28[];

int __attribute((regparm(3))) fcn_fffc6438(void *ram_data, u32 a, u32 b);
void fcn_fffc6986(void);

int frag_fffc2026(void *ram_data);
int frag_fffc2026(void *ram_data)
{
	uint32_t tmp;
	int ret = 1;
	uint8_t dl = 1;

	for (int i = 0; i <= 0x33 && dl; i++) {
		ram_st *st = &ref_fffcbf28[i];

		if (ref_fffcbf28[i].v1 == ~0) {
			tmp = (uint16_t)(i - 0x2300);
		} else {
			tmp = ref_fffcbf28[i].v1;
		}
		rtc_wait(ram_data, tmp);

		dl = 1;
		if (ref_fffcbf28[i].func == NULL)
			continue;
		if (*(uint8_t*)(ram_data + 0x1018) >= st->v4)
			continue;

		tmp = *(uint32_t*)(ram_data + 0x1019);
		if (tmp != 0) {
			tmp--; if (tmp != 0) continue;
			if ((st->v3 & 0x20) == 0) continue;
		} else {
			if ((st->v3 & 0x10) == 0)
				continue;
		}

		tmp = *(uint32_t*)(ram_data + 0x16d7);
		if (tmp == 2) {
			if (st->v3 & 8)
				goto loc_fffc20ce;
			goto loc_fffc210d;
		} else if (tmp == 3) {
			if (st->v3 & 2)
				goto loc_fffc20ce;
			goto loc_fffc210d;
		} else if (tmp == 1) {
			if (st->v3 & 4)
				goto loc_fffc20ce;
			goto loc_fffc210d;
		} else if (tmp != 0) {
			dl = 1;
			continue;
		} else {
			dl = 1;
			if (st->v3 & 1)
				goto loc_fffc20ce;
			else
				continue;
		}
loc_fffc20ce:
		tmp = st->v2;
		if (tmp <= 0x3b) {
			if (fcn_fffc6438(ram_data, tmp, 0) != 0) {
loc_fffc210d:
				dl = 1;
				continue;
			}
		}
		fcn_fffc6986();
		ret = ref_fffcbf28[i].func(ram_data);
		fcn_fffc6986();
		dl = (ret == 0)? 1:0;
	}
	printk(BIOS_DEBUG, "return from frag_fffc2026 with value 0x%x\n", ret);
	return ret;
}
