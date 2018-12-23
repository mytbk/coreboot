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
	uint8_t v0; // 0x00
	uint16_t max_ddr3_freq; // 0x01
	uint8_t v1; // 0x03
	uint8_t padding0[13]; // 0x04
	uint8_t v2; // 0x11
	uint8_t padding1[18]; // 0x12
	uint8_t v3; // 0x24
	uint8_t padding2[5]; // 0x25
	uint8_t chan0_disabled; // 0x2a
	uint8_t chan1_disabled; // 0x2b
	uint8_t param0[43]; // 0x2c
	uint32_t dq_pins_interleaved; // 0x57
	uint8_t param1[10]; // 0x5b
	uint32_t param2; // 0x65
	uint16_t padding3; // 0x69
	uint8_t v4; // 0x6b
	uint8_t padding4; // 0x6c
	uint8_t ddr_refresh_2x; // 0x6d
	uint8_t v5; // 0x6f
	uint16_t param3; // 0x70

};
