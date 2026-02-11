dns_mnemonic_fromtext(unsigned int *valuep, isc_textregion_t *source,
		      struct tbl *table, unsigned int max)
{
	isc_result_t result;
	int i;

	result = maybe_numeric(valuep, source, max, ISC_FALSE);
	if (result != ISC_R_BADNUMBER)
		return (result);

	for (i = 0; table[i].name != NULL; i++) {
		unsigned int n;
		n = strlen(table[i].name);
		if (n == source->length &&
		    strncasecmp(source->base, table[i].name, n) == 0) {
			*valuep = table[i].value;
			return (ISC_R_SUCCESS);
		}
	}
	return (DNS_R_UNKNOWN);
}
