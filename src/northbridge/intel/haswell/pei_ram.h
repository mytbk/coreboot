#include <stdint.h>

struct _pei_ram_data
{
	uint8_t spd_addresses[4];
	uint32_t mchbar; /* 0x04 */
	uint32_t dmibar; /* 0x08 */
	uint32_t epbar; /* 0x0c */
	uint32_t pciexbar; /* 0x10 */
	uint32_t smbusbar; /* 0x14 */
	uint32_t gdxcbar; // 0x18 in coreboot, GDXC_BASE_ADDRESS is 0xfed84000
	uint32_t tseg_size; // 0x1c
	uint8_t system_type; // 0x20
	uint8_t v1;
	uint32_t edrambar; // 0x22 in coreboot, EDRAM_BASE_ADDRESS is 0xfed80000
	uint8_t padding[5];
	uint32_t ied_region_size; // in coreboot, IED_REGION_SIZE is 0x400000
} __packed;

typedef struct _pei_ram_data pei_ram_data;

/* FIXME: not completed yet, do not use! */
struct _pei_ram_param
{
	uint8_t v00; // 0x00
	uint16_t max_ddr3_freq; // 0x01
	uint8_t v03;
	uint32_t v04;
	uint8_t v08[0x22];
	uint8_t chan0_disabled; // 0x2a
	uint8_t chan1_disabled; // 0x2b
	uint8_t v2c[0x2b]; // 0x2c
	uint8_t dq_pins_interleaved; // 0x57
	uint16_t v58;
	uint8_t v5a[10]; // 0x5a
	uint32_t v64; // 0x64
	uint16_t v68;
	uint8_t v6a[2];
	uint8_t ddr_refresh_2x; // 0x6c
	uint8_t v6d; // 0x6d
	uint16_t v6e;
	uint8_t v70[6];
	uint8_t ddr_refresh_2x_76; // 0x76
	uint8_t v77[54];
	uint16_t vad;
	uint8_t vaf;
	uint8_t vb0[24];
} __packed;

typedef struct _pei_ram_param pei_ram_param;

struct _pei_raminit_ppi
{
	uint8_t v; // 0x00
	pei_ram_data *ram_data; // 0x01
	uint8_t *cfg0; // 0x05
	pei_ram_param *ram_param; // 0x09
	uint8_t *cfg1; // 0x0d
	void *functions; // 0x11
	uint8_t *mrc_input; // 0x15
} __packed;

typedef struct _pei_raminit_ppi pei_raminit_ppi;
