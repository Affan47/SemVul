build_prefix6(struct in6_addr *pref,
	      const struct in6_addr *net_start_pref,
	      int pool_bits, int pref_bits,
	      const struct data_string *input) {
	isc_md5_t ctx;
	int net_bytes;
	int i;
	char *str;
	const char *net_str;


	isc_md5_init(&ctx);
	isc_md5_update(&ctx, input->data, input->len);
	isc_md5_final(&ctx, (unsigned char *)pref);


	str = (char *)pref;
	net_str = (const char *)net_start_pref;
	net_bytes = pool_bits / 8;
	for (i = 0; i < net_bytes; i++) {
		str[i] = net_str[i];
	}
	i = net_bytes;
	switch (pool_bits % 8) {
		case 1: str[i] = (str[i] & 0x7F) | (net_str[i] & 0x80); break;
		case 2: str[i] = (str[i] & 0x3F) | (net_str[i] & 0xC0); break;
		case 3: str[i] = (str[i] & 0x1F) | (net_str[i] & 0xE0); break;
		case 4: str[i] = (str[i] & 0x0F) | (net_str[i] & 0xF0); break;
		case 5: str[i] = (str[i] & 0x07) | (net_str[i] & 0xF8); break;
		case 6: str[i] = (str[i] & 0x03) | (net_str[i] & 0xFC); break;
		case 7: str[i] = (str[i] & 0x01) | (net_str[i] & 0xFE); break;
	}


	net_bytes = pref_bits / 8;
	for (i=net_bytes+1; i<16; i++) {
		str[i] = 0;
	}
	i = net_bytes;
	switch (pref_bits % 8) {
		case 0: str[i] &= 0; break;
		case 1: str[i] &= 0x80; break;
		case 2: str[i] &= 0xC0; break;
		case 3: str[i] &= 0xE0; break;
		case 4: str[i] &= 0xF0; break;
		case 5: str[i] &= 0xF8; break;
		case 6: str[i] &= 0xFC; break;
		case 7: str[i] &= 0xFE; break;
	}
}
