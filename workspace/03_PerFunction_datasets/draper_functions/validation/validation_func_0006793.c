print_class_type(FILE *fp, ldns_rr *r)
{
	ldns_lookup_table *lt;
        lt = ldns_lookup_by_id(ldns_rr_classes, ldns_rr_get_class(r));
        if (lt) {
               	fprintf(fp, " %s", lt->name);
        } else {
        	fprintf(fp, " CLASS%d", ldns_rr_get_class(r));
        }

	switch (ldns_rr_get_type(r)) {
		case LDNS_RR_TYPE_RRSIG:
			fprintf(fp, " RRSIG ");
			break;
		case LDNS_RR_TYPE_DNSKEY:
			fprintf(fp, " DNSKEY ");
			break;
		case LDNS_RR_TYPE_DS:
			fprintf(fp, " DS ");
			break;
		default:
			break;
	}
}
