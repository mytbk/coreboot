int fcn_fffbe070(PEI_SERVICES **ps, arg2, arg3)
{
	uint32_t v;
	int i = 0;
	int ret = 0;

	for (i = 0; i < 50; i++) {
		v = pci_read_config32(PCH_ME_DEV, PCI_ME_HFS2);
		if ((v & 0x100) != 0)
			break;
		usleep(1000);
	}
	if (i == 50) {
		*arg3 = 1;
		return ret;
	}

	if (v & 0x80) {
		pci_update_config16(PCH_LPC_DEV, 0xa2, 0xff7f, 0);
		ret = fcn_fffbdf70(ps, 1);
	}
	u8 tmp = v & 0x90;
	if (tmp == 0x10)
		*arg3 = 1;

	return ret;
}
