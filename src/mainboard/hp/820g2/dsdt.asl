/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi.h>

DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20141018	/* OEM revision */
)
{
	#include <acpi/dsdt_top.asl>

	/* split out _PTS and _WAK from soc/intel/broadwell/acpi/platform.asl */
	#include <soc/intel/broadwell/acpi/device_nvs.asl>
	#include <southbridge/intel/common/acpi/platform.asl>
	#include "acpi/platform.asl"
	#include <soc/intel/common/acpi/acpi_wake_source.asl>

	#include <soc/intel/broadwell/pch/acpi/globalnvs.asl>
	#include <cpu/intel/common/acpi/cpu.asl>
	#include <southbridge/intel/common/acpi/sleepstates.asl>

	Device (\_SB.PCI0)
	{
		#include <soc/intel/broadwell/acpi/hostbridge.asl>
		#include <soc/intel/broadwell/pch/acpi/pch.asl>
	}
}
