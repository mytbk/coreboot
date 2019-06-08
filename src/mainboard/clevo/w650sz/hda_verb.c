/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019 Iru Cai <mytbk920423@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x11068446, /* Codec Vendor / Device ID: VIA */
	0x15580655, /* Subsystem ID */
	10, /* Number of 4 dword sets */
	AZALIA_SUBVENDOR(0x0, 0x15580655),
	AZALIA_PIN_CFG(0x0, 0x24, 0x901701f0),
	AZALIA_PIN_CFG(0x0, 0x25, 0x022140f0),
	AZALIA_PIN_CFG(0x0, 0x28, 0x422140f0),
	AZALIA_PIN_CFG(0x0, 0x29, 0x90a701f0),
	AZALIA_PIN_CFG(0x0, 0x2a, 0x418130f0),
	AZALIA_PIN_CFG(0x0, 0x2b, 0x01a190f0),
	AZALIA_PIN_CFG(0x0, 0x2d, 0x474411f0),
	AZALIA_PIN_CFG(0x0, 0x30, 0x50a601f0),
	AZALIA_PIN_CFG(0x0, 0x33, 0x501701f0),
};

const u32 pc_beep_verbs[0] = {};

AZALIA_ARRAY_SIZES;
