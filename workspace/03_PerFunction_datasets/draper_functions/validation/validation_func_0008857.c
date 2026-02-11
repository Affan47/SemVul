ns_config_getkeyalgorithm2(const char *str, dns_name_t **name,
			   unsigned int *typep, isc_uint16_t *digestbits)
{
	int i;
	size_t len = 0;
	isc_uint16_t bits;
	isc_result_t result;

	for (i = 0; algorithms[i].str != NULL; i++) {
		len = strlen(algorithms[i].str);
		if (strncasecmp(algorithms[i].str, str, len) == 0 &&
		    (str[len] == '\0' ||
		     (algorithms[i].size != 0 && str[len] == '-')))
			break;
	}
	if (algorithms[i].str == NULL)
		return (ISC_R_NOTFOUND);
	if (str[len] == '-') {
		result = isc_parse_uint16(&bits, str + len + 1, 10);
		if (result != ISC_R_SUCCESS)
			return (result);
		if (bits > algorithms[i].size)
			return (ISC_R_RANGE);
	} else if (algorithms[i].size == 0)
		bits = 128;
	else
		bits = algorithms[i].size;

	if (name != NULL) {
		switch (algorithms[i].hmac) {
		case hmacmd5: *name = dns_tsig_hmacmd5_name; break;
		case hmacsha1: *name = dns_tsig_hmacsha1_name; break;
		case hmacsha224: *name = dns_tsig_hmacsha224_name; break;
		case hmacsha256: *name = dns_tsig_hmacsha256_name; break;
		case hmacsha384: *name = dns_tsig_hmacsha384_name; break;
		case hmacsha512: *name = dns_tsig_hmacsha512_name; break;
		default:
			INSIST(0);
		}
	}
	if (typep != NULL)
		*typep = algorithms[i].type;
	if (digestbits != NULL)
		*digestbits = bits;
	return (ISC_R_SUCCESS);
}
