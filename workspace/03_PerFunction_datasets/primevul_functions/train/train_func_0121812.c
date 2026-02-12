spacefortsig(dns_tsigkey_t *key, int otherlen) {
	isc_region_t r1, r2;
	unsigned int x;
	isc_result_t result;


	dns_name_toregion(&key->name, &r1);
	dns_name_toregion(key->algorithm, &r2);
	if (key->key == NULL)
		x = 0;
	else {
		result = dst_key_sigsize(key->key, &x);
		if (result != ISC_R_SUCCESS)
			x = 0;
	}
	return (26 + r1.length + r2.length + x + otherlen);
}
