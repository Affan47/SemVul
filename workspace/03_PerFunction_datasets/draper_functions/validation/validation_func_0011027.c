fix_header(struct _adapter *padapter, u8 header, u16 header_addr)
{
	struct PGPKT_STRUCT pkt;
	u8 offset, word_en, value;
	u16 addr;
	int i;
	u8 ret = true;

	pkt.offset = GET_EFUSE_OFFSET(header);
	pkt.word_en = GET_EFUSE_WORD_EN(header);
	addr = header_addr + 1 + calculate_word_cnts(pkt.word_en) * 2;
	if (addr > efuse_available_max_size)
		return false;

	addr = 0;
	while (addr < header_addr) {
		if (!efuse_one_byte_read(padapter, addr++, &value)) {
			ret = false;
			break;
		}
		offset = GET_EFUSE_OFFSET(value);
		word_en = GET_EFUSE_WORD_EN(value);
		if (pkt.offset != offset) {
			addr += calculate_word_cnts(word_en) * 2;
			continue;
		}
		for (i = 0; i < PGPKG_MAX_WORDS; i++) {
			if (BIT(i) & word_en) {
				if (BIT(i) & pkt.word_en) {
					if (efuse_one_byte_read(
							padapter, addr,
							&value))
						pkt.data[i * 2] = value;
					else
						return false;
					if (efuse_one_byte_read(
							padapter,
							addr + 1,
							&value))
						pkt.data[i * 2 + 1] =
							value;
					else
						return false;
				}
				addr += 2;
			}
		}
	}
	if (addr != header_addr)
		return false;
	addr++;

	for (i = 0; i < PGPKG_MAX_WORDS; i++) {
		if (BIT(i) & pkt.word_en) {
			efuse_one_byte_write(padapter, addr, pkt.data[i * 2]);
			efuse_one_byte_write(padapter, addr + 1,
					     pkt.data[i * 2 + 1]);

			if (!efuse_one_byte_read(padapter, addr, &value)) {
				ret = false;
			} else if (pkt.data[i * 2] != value) {
				ret = false;
				if (0xFF == value)
					efuse_one_byte_write(padapter, addr,
							pkt.data[i * 2]);
			}
			if (!efuse_one_byte_read(padapter, addr + 1, &value)) {
				ret = false;
			} else if (pkt.data[i * 2 + 1] != value) {
				ret = false;
				if (0xFF == value)
					efuse_one_byte_write(padapter, addr + 1,
							     pkt.data[i * 2 +
								      1]);
			}
		}
		addr += 2;
	}
	return ret;
}
