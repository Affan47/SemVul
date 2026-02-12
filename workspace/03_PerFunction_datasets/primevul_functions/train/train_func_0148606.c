delsig_ok(dns_rdata_rrsig_t *rrsig_ptr, dst_key_t **keys, unsigned int nkeys,
	  bool *warn)
{
	unsigned int i = 0;
	bool have_ksk = false, have_zsk = false;
	bool have_pksk = false, have_pzsk = false;

	for (i = 0; i < nkeys; i++) {
		if (rrsig_ptr->algorithm != dst_key_alg(keys[i]))
			continue;
		if (dst_key_isprivate(keys[i])) {
			if (KSK(keys[i]))
				have_ksk = have_pksk = true;
			else
				have_zsk = have_pzsk = true;
		} else {
			if (KSK(keys[i]))
				have_ksk = true;
			else
				have_zsk = true;
		}
	}

	if (have_zsk && have_ksk && !have_pzsk)
		*warn = true;


	if (have_pksk || have_pzsk)
		return (true);


	for (i = 0; i < nkeys; i++) {
		if ((rrsig_ptr->algorithm == dst_key_alg(keys[i])) &&
		    (rrsig_ptr->keyid == dst_key_id(keys[i])))
			return (false);
	}


	return (true);
}
