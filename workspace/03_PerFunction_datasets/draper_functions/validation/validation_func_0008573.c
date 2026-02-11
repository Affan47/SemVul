match_list(ldns_rr_list* q, ldns_rr_list *p, bool mttl)
{
	size_t i;
	if(ldns_rr_list_rr_count(q) != ldns_rr_list_rr_count(p))
		return 0;
	for(i=0; i<ldns_rr_list_rr_count(q); i++)
	{
		if(ldns_rr_compare(ldns_rr_list_rr(q, i),
			ldns_rr_list_rr(p, i)) != 0) {
			verbose(3, "rr %d different", (int)i);
			return 0;
		}
		if(mttl && ldns_rr_ttl(ldns_rr_list_rr(q, i)) !=
			ldns_rr_ttl(ldns_rr_list_rr(p, i))) {
			verbose(3, "rr %d ttl different", (int)i);
			return 0;
		}
	}
	return 1;
}
