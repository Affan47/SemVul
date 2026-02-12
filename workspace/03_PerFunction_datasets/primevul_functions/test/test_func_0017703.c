respip_merge_cname(struct reply_info* base_rep,
	const struct query_info* qinfo, const struct reply_info* tgt_rep,
	const struct respip_client_info* cinfo, int must_validate,
	struct reply_info** new_repp, struct regional* region)
{
	struct reply_info* new_rep;
	struct reply_info* tmp_rep = NULL;
	struct ub_packed_rrset_key* alias_rrset = NULL;
	uint16_t tgt_rcode;
	size_t i, j;
	struct respip_action_info actinfo = {respip_none, NULL};


	tgt_rcode = FLAGS_GET_RCODE(tgt_rep->flags);
	if((tgt_rcode != LDNS_RCODE_NOERROR &&
		tgt_rcode != LDNS_RCODE_NXDOMAIN &&
		tgt_rcode != LDNS_RCODE_YXDOMAIN) ||
		(must_validate && tgt_rep->security <= sec_status_bogus)) {
		return 0;
	}


	if(!respip_rewrite_reply(qinfo, cinfo, tgt_rep, &tmp_rep, &actinfo,
		&alias_rrset, 1, region))
		return 0;
	if(actinfo.action != respip_none) {
		log_info("CNAME target of redirect response-ip action would "
			"be subject to response-ip action, too; stripped");
		*new_repp = base_rep;
		return 1;
	}


	new_rep = make_new_reply_info(base_rep, region,
		base_rep->an_numrrsets + tgt_rep->an_numrrsets,
		base_rep->an_numrrsets);
	if(!new_rep)
		return 0;
	for(i=0,j=base_rep->an_numrrsets; i<tgt_rep->an_numrrsets; i++,j++) {
		new_rep->rrsets[j] = copy_rrset(tgt_rep->rrsets[i], region);
		if(!new_rep->rrsets[j])
			return 0;
	}

	FLAGS_SET_RCODE(new_rep->flags, tgt_rcode);
	*new_repp = new_rep;
	return 1;
}
