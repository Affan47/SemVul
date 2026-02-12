call_hook(struct module_qstate* qstate, struct ipsecmod_qstate* iq,
	struct ipsecmod_env* ATTR_UNUSED(ie))
{
	size_t slen, tempdata_len, tempstring_len, i;
	char str[65535], *s, *tempstring;
	int w;
	struct ub_packed_rrset_key* rrset_key;
	struct packed_rrset_data* rrset_data;
	uint8_t *tempdata;


	if(system(NULL) == 0) {
		log_err("ipsecmod: no shell available for ipsecmod-hook");
		return 0;
	}


	s = str;
	slen = sizeof(str);
	memset(s, 0, slen);


	sldns_str_print(&s, &slen, "%s", qstate->env->cfg->ipsecmod_hook);

	sldns_str_print(&s, &slen, " ");

	tempstring = sldns_wire2str_dname(qstate->qinfo.qname,
		qstate->qinfo.qname_len);
	if(!tempstring) {
		log_err("ipsecmod: out of memory when calling the hook");
		return 0;
	}
	sldns_str_print(&s, &slen, "\"%s\"", tempstring);
	free(tempstring);

	sldns_str_print(&s, &slen, " ");

	rrset_data = (struct packed_rrset_data*)iq->ipseckey_rrset->entry.data;
	sldns_str_print(&s, &slen, "\"%ld\"", (long)rrset_data->ttl);

	sldns_str_print(&s, &slen, " ");


	rrset_key = reply_find_answer_rrset(&qstate->return_msg->qinfo,
		qstate->return_msg->rep);
	rrset_data = (struct packed_rrset_data*)rrset_key->entry.data;
	sldns_str_print(&s, &slen, "\"");
	for(i=0; i<rrset_data->count; i++) {
		if(i > 0) {

			sldns_str_print(&s, &slen, " ");
		}

		w = sldns_wire2str_rdata_buf(rrset_data->rr_data[i] + 2,
			rrset_data->rr_len[i] - 2, s, slen, qstate->qinfo.qtype);
		if(w < 0) {

			return -1;
		} else if((size_t)w >= slen) {
			s = NULL;
			slen = 0;
			return -1;
		} else {
			s += w;
			slen -= w;
		}
	}
	sldns_str_print(&s, &slen, "\"");

	sldns_str_print(&s, &slen, " ");


	sldns_str_print(&s, &slen, "\"");
	rrset_data = (struct packed_rrset_data*)iq->ipseckey_rrset->entry.data;
	for(i=0; i<rrset_data->count; i++) {
		if(i > 0) {

			sldns_str_print(&s, &slen, " ");
		}

		tempdata = rrset_data->rr_data[i] + 2;
		tempdata_len = rrset_data->rr_len[i] - 2;

		tempstring = s; tempstring_len = slen;
		w = sldns_wire2str_ipseckey_scan(&tempdata, &tempdata_len, &s, &slen,
			NULL, 0);


		if(w == -1){
			s = tempstring; slen = tempstring_len;
		}
	}
	sldns_str_print(&s, &slen, "\"");
	verbose(VERB_ALGO, "ipsecmod: hook command: '%s'", str);

	if(system(str) != 0)
		return 0;
	return 1;
}
