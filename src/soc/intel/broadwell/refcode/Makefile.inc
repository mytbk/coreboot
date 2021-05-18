ramstage-libs += $(obj)/broadwell_refcode.o
ramstage-y += print_gbe.c

$(obj)/%.o: $(src)/soc/intel/broadwell/refcode/%.asm
	echo "NASM $@"
	nasm -f elf32 -o $@ $<
