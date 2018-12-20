#
# This file is part of the coreboot project.
#
# Copyright (C) 2010 Google Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

ifeq ($(CONFIG_NORTHBRIDGE_INTEL_HASWELL),y)

ramstage-y += ram_calc.c
ramstage-y += northbridge.c
ramstage-y += gma.c
ramstage-y += pcie.c

ramstage-y += acpi.c
ramstage-y += minihd.c

romstage-y += ram_calc.c
romstage-y += raminit.c
romstage-y += early_init.c
romstage-y += report_platform.c
romstage-y += ../../../arch/x86/walkcbfs.S

smm-$(CONFIG_HAVE_SMI_HANDLER) += finalize.c

romstage-libs += $(obj)/mrc.o
romstage-libs += $(obj)/me_uma.o
romstage-libs += $(obj)/pei_usb.o
romstage-libs += $(obj)/pei_cpuio.o
romstage-libs += $(obj)/mrc_init_memory.o
#romstage-libs += $(obj)/mrc_pch_init.o
$(obj)/%.o: $(src)/northbridge/intel/haswell/%.asm
	echo "NASM $@"
	nasm -f elf32 -o $@ $<

romstage-y += pei_svc.c
romstage-y += mrc_utils.c
romstage-y += mrc_smbus.c
romstage-y += mrc_sku.c
romstage-y += mrc_io.c
romstage-y += mrc_pch.c
romstage-y += stall.c
romstage-y += mrc_main.c
romstage-y += mrc_pch_init.c

postcar-y += ram_calc.c

endif
