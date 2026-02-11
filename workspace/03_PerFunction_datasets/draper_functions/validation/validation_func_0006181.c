ldns_dnssec_rrs_add_rr(ldns_dnssec_rrs *rrs, ldns_rr *rr)
{
	int cmp;
	ldns_dnssec_rrs *new_rrs;
	if (!rrs || !rr) {
		return LDNS_STATUS_ERR;
	}


	cmp = ldns_rr_compare(rrs->rr, rr);
	if (cmp < 0) {
		if (rrs->next) {
			return ldns_dnssec_rrs_add_rr(rrs->next, rr);
		} else {
			new_rrs = ldns_dnssec_rrs_new();
			new_rrs->rr = rr;
			rrs->next = new_rrs;
		}
	} else if (cmp > 0) {


		new_rrs = ldns_dnssec_rrs_new();
		new_rrs->rr = rrs->rr;
		new_rrs->next = rrs->next;
		rrs->rr = rr;
		rrs->next = new_rrs;
	}

	return LDNS_STATUS_OK;
}
