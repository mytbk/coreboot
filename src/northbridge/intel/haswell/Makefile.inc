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

bootblock-y += bootblock.c

ramstage-y += memmap.c
ramstage-y += northbridge.c
ramstage-y += gma.c

ramstage-y += acpi.c
ramstage-y += minihd.c

romstage-y += memmap.c
romstage-y += raminit.c
romstage-y += early_init.c
romstage-y += report_platform.c

smm-y += finalize.c

romstage-libs += $(obj)/mrc.o
romstage-libs += $(obj)/me_uma.o
romstage-libs += $(obj)/pei_cpuio.o
romstage-libs += $(obj)/mrc_init_memory.o
romstage-libs += $(obj)/mrc_end_of_pei.o
romstage-libs += $(obj)/pei_smbus.o
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
romstage-y += mrc_misc.c
romstage-y += pei_mem.c
romstage-y += do_raminit_frag.c
romstage-y += mrc_frag_init_memory.c
romstage-y += mrc_wdt.c
romstage-y += pei_smbus.c
romstage-y += mrc_frags.c
romstage-y += pei_usb.c
romstage-y += me_uma.c
romstage-y += mrc_init_memory_fcns.c
postcar-y += memmap.c

endif
