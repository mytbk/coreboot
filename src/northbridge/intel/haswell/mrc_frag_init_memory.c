#include <southbridge/intel/lynxpoint/pch.h>
#include <arch/pci_ops.h>
#include "mrc_pei.h"
#include <cpu/x86/msr.h>
#include "mrc_utils.h"
#include <arch/cpu.h>
#include "pei_ram.h"

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

void set_cpuid(struct cpu_model_id *mycpu);
void set_cpuid(struct cpu_model_id *mycpu)
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
void * frag_fffc1f53(uint32_t *wb);
void * frag_fffc1f53(uint32_t *wb)
{
	void *hob = locate_hob(&ref_fffcd4a4, 4);
	if (hob == NULL)
		return NULL;
	uint8_t tmp = *(uint8_t*)(hob + 0x21) + *(uint8_t*)(hob + 0x19);
	if (tmp != 0)
		*wb = tmp;
	return hob;
}

void frag_fffc1d5a(void *ppi, int t, void* dst);
void frag_fffc1d5a(void *ppi, int t, void* dst)
{
	void * esi = *(void**)(ppi + 0x15);
	if (esi == NULL)
		return;
	if (t == 4)
		return;

	int ret = crc32(esi + 4, 0xfd0);
	if (ret != *(int*)esi)
		return;

	memcpy(dst, esi, 0xfd4);
}

int __attribute((regparm(2)))
fcn_fffa10df(void *ram_data, void *ppi);

/*
ram_data: ebp - 0x503a
ppi: [ebp - 0x50a4]
v50c4: [ebp - 0x50c4]
return value moved to edi
*/
int frag_fffc1ea8(void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl);
int frag_fffc1ea8(void *ram_data, pei_raminit_ppi *ppi,
		uint32_t v50c4, uint8_t bl)
{
	if (v50c4 - 1 > 1) {
		if (bl == 1) {
			if (ppi->ram_param->v2c[0x2a] != 0) {
				if (fcn_fffa10df(ram_data, ppi) == 0)
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
	if (fcn_fffa10df(ram_data, ppi) == 1) {
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
