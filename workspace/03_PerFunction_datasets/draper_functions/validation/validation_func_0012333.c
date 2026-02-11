brcmf_chip_dmp_get_regaddr(struct brcmf_chip_priv *ci, u32 *eromaddr,
				      u32 *regbase, u32 *wrapbase)
{
	u8 desc;
	u32 val;
	u8 mpnum = 0;
	u8 stype, sztype, wraptype;

	*regbase = 0;
	*wrapbase = 0;

	val = brcmf_chip_dmp_get_desc(ci, eromaddr, &desc);
	if (desc == DMP_DESC_MASTER_PORT) {
		mpnum = (val & DMP_MASTER_PORT_NUM) >> DMP_MASTER_PORT_NUM_S;
		wraptype = DMP_SLAVE_TYPE_MWRAP;
	} else if (desc == DMP_DESC_ADDRESS) {

		*eromaddr -= 4;
		wraptype = DMP_SLAVE_TYPE_SWRAP;
	} else {
		*eromaddr -= 4;
		return -EILSEQ;
	}

	do {

		do {
			val = brcmf_chip_dmp_get_desc(ci, eromaddr, &desc);

			if (desc == DMP_DESC_EOT) {
				*eromaddr -= 4;
				return -EFAULT;
			}
		} while (desc != DMP_DESC_ADDRESS);


		if (val & DMP_DESC_ADDRSIZE_GT32)
			brcmf_chip_dmp_get_desc(ci, eromaddr, NULL);

		sztype = (val & DMP_SLAVE_SIZE_TYPE) >> DMP_SLAVE_SIZE_TYPE_S;


		if (sztype == DMP_SLAVE_SIZE_DESC) {
			val = brcmf_chip_dmp_get_desc(ci, eromaddr, NULL);

			if (val & DMP_DESC_ADDRSIZE_GT32)
				brcmf_chip_dmp_get_desc(ci, eromaddr, NULL);
		}


		if (sztype != DMP_SLAVE_SIZE_4K)
			continue;

		stype = (val & DMP_SLAVE_TYPE) >> DMP_SLAVE_TYPE_S;


		if (*regbase == 0 && stype == DMP_SLAVE_TYPE_SLAVE)
			*regbase = val & DMP_SLAVE_ADDR_BASE;
		if (*wrapbase == 0 && stype == wraptype)
			*wrapbase = val & DMP_SLAVE_ADDR_BASE;
	} while (*regbase == 0 || *wrapbase == 0);

	return 0;
}
