reply_check_cname_chain(struct query_info* qinfo, struct reply_info* rep)
{


	size_t i;
	uint8_t* sname = qinfo->qname;
	size_t snamelen = qinfo->qname_len;
	for(i=0; i<rep->an_numrrsets; i++) {
		uint16_t t = ntohs(rep->rrsets[i]->rk.type);
		if(t == LDNS_RR_TYPE_DNAME)
			continue;

		if(query_dname_compare(sname, rep->rrsets[i]->rk.dname) != 0){

			return 0;
		}

		if(t == LDNS_RR_TYPE_CNAME) {
			get_cname_target(rep->rrsets[i], &sname, &snamelen);
		}
	}
	return 1;
}
