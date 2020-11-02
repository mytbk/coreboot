ramstage-libs += $(obj)/broadwell_refcode.o

$(obj)/%.o: $(src)/soc/intel/broadwell/refcode/%.asm
	echo "NASM $@"
	nasm -f elf32 -o $@ $<
