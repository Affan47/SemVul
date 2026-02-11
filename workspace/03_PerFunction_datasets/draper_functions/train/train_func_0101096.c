tsig_rdata_alg(const knot_rrset_t *tsig)
{

	const knot_dname_t *alg_name = tsig_rdata_alg_name(tsig);
	if (!alg_name) {
		dbg_tsig("TSIG: rdata: cannot get algorithm name.\n");
		return KNOT_TSIG_ALG_NULL;
	}


	char *name = knot_dname_to_str(alg_name);
	if (!name) {
		dbg_tsig("TSIG: rdata: cannot convert alg name.\n");
		return KNOT_TSIG_ALG_NULL;
	}

	knot_lookup_table_t *item = knot_lookup_by_name(
	                                      knot_tsig_alg_dnames_str, name);
	free(name);
	if (!item) {
		dbg_tsig("TSIG: rdata: unknown algorithm.\n");
		return KNOT_TSIG_ALG_NULL;
	}
	return item->id;
}
