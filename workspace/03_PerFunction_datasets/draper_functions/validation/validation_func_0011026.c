ldns_nsec_get_bitmap(ldns_rr *nsec) {
	if (ldns_rr_get_type(nsec) == LDNS_RR_TYPE_NSEC) {
		return ldns_rr_rdf(nsec, 1);
	} else if (ldns_rr_get_type(nsec) == LDNS_RR_TYPE_NSEC3) {
		return ldns_rr_rdf(nsec, 5);
	} else {
		return NULL;
	}
}
