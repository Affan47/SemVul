OCTET_STRING_per_put_characters(asn_per_outp_t *po, const uint8_t *buf,
		size_t units, unsigned int bpc, unsigned int unit_bits,
		long lb, long ub, asn_per_constraints_t *pc) {
	const uint8_t *end = buf + units * bpc;

	ASN_DEBUG("Squeezing %d characters into (%ld..%ld):%d (%d bpc)",
		(int)units, lb, ub, unit_bits, bpc);


	if((unsigned long)ub <= ((unsigned long)2 << (unit_bits - 1))) {

		lb = 0;
	} else if(pc && pc->value2code) {
		for(; buf < end; buf += bpc) {
			int code;
			uint32_t value;
			switch(bpc) {
			case 1: value = *(const uint8_t *)buf; break;
			case 2: value = (buf[0] << 8) | buf[1]; break;
			case 4: value = (buf[0] << 24) | (buf[1] << 16)
					| (buf[2] << 8) | buf[3]; break;
			default: return -1;
			}
			code = pc->value2code(value);
			if(code < 0) {
				ASN_DEBUG("Character %d (0x%02x) is"
					" not in map (%ld..%ld)",
					*buf, *buf, lb, ub);
				return -1;
			}
			if(per_put_few_bits(po, code, unit_bits))
				return -1;
		}
	}


	if(lb == 0 && (unit_bits == 8 * bpc)) {
		return per_put_many_bits(po, buf, unit_bits * units);
	}

	for(ub -= lb; buf < end; buf += bpc) {
		int ch;
		uint32_t value;
		switch(bpc) {
		case 1: value = *(const uint8_t *)buf; break;
		case 2: value = (buf[0] << 8) | buf[1]; break;
		case 4: value = (buf[0] << 24) | (buf[1] << 16)
				| (buf[2] << 8) | buf[3]; break;
		default: return -1;
		}
		ch = value - lb;
		if(ch < 0 || ch > ub) {
			ASN_DEBUG("Character %d (0x%02x)"
			" is out of range (%ld..%ld)",
				*buf, *buf, lb, ub + lb);
			return -1;
		}
		if(per_put_few_bits(po, ch, unit_bits))
			return -1;
	}

	return 0;
}
