call_hook(struct module_qstate* qstate, struct ipsecmod_qstate* iq,
	struct ipsecmod_env* ATTR_UNUSED(ie))
{
	size_t slen, tempdata_len, tempstring_len, i;
	char str[65535], *s, *tempstring;
	int w = 0, w_temp, qtype;
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


	w += sldns_str_print(&s, &slen, "%s", qstate->env->cfg->ipsecmod_hook);

	w += sldns_str_print(&s, &slen, " ");

	tempstring = sldns_wire2str_dname(qstate->qinfo.qname,
		qstate->qinfo.qname_len);
	if(!tempstring) {
		log_err("ipsecmod: out of memory when calling the hook");
		return 0;
	}
	if(!domainname_has_safe_characters(tempstring, strlen(tempstring))) {
		log_err("ipsecmod: qname has unsafe characters");
		free(tempstring);
		return 0;
	}
	w += sldns_str_print(&s, &slen, "\"%s\"", tempstring);
	free(tempstring);

	w += sldns_str_print(&s, &slen, " ");

	rrset_data = (struct packed_rrset_data*)iq->ipseckey_rrset->entry.data;
	w += sldns_str_print(&s, &slen, "\"%ld\"", (long)rrset_data->ttl);

	w += sldns_str_print(&s, &slen, " ");
	rrset_key = reply_find_answer_rrset(&qstate->return_msg->qinfo,
		qstate->return_msg->rep);


	qtype = ntohs(rrset_key->rk.type);
	if(qtype != LDNS_RR_TYPE_AAAA && qtype != LDNS_RR_TYPE_A) {
		log_err("ipsecmod: Answer is not of A or AAAA type");
		return 0;
	}
	rrset_data = (struct packed_rrset_data*)rrset_key->entry.data;


	w += sldns_str_print(&s, &slen, "\"");
	for(i=0; i<rrset_data->count; i++) {
		if(i > 0) {

			w += sldns_str_print(&s, &slen, " ");
		}

		w_temp = sldns_wire2str_rdata_buf(rrset_data->rr_data[i] + 2,
			rrset_data->rr_len[i] - 2, s, slen, qstate->qinfo.qtype);
		if(w_temp < 0) {

			log_err("ipsecmod: Error in printing IP address");
			return 0;
		} else if((size_t)w_temp >= slen) {
			s = NULL;
			slen = 0;
			log_err("ipsecmod: shell command too long");
			return 0;
		} else {
			s += w_temp;
			slen -= w_temp;
			w += w_temp;
		}
	}
	w += sldns_str_print(&s, &slen, "\"");

	w += sldns_str_print(&s, &slen, " ");


	w += sldns_str_print(&s, &slen, "\"");
	rrset_data = (struct packed_rrset_data*)iq->ipseckey_rrset->entry.data;
	for(i=0; i<rrset_data->count; i++) {
		if(i > 0) {

			w += sldns_str_print(&s, &slen, " ");
		}

		tempdata = rrset_data->rr_data[i] + 2;
		tempdata_len = rrset_data->rr_len[i] - 2;

		tempstring = s; tempstring_len = slen;
		w_temp = sldns_wire2str_ipseckey_scan(&tempdata, &tempdata_len, &s,
			&slen, NULL, 0);


		if(w_temp == -1) {
			s = tempstring; slen = tempstring_len;
		} else if(w_temp > 0) {
			if(!ipseckey_has_safe_characters(
					tempstring, tempstring_len - slen)) {
				log_err("ipsecmod: ipseckey has unsafe characters");
				return 0;
			}
			w += w_temp;
		}
	}
	w += sldns_str_print(&s, &slen, "\"");
	if(w >= (int)sizeof(str)) {
		log_err("ipsecmod: shell command too long");
		return 0;
	}
	verbose(VERB_ALGO, "ipsecmod: shell command: '%s'", str);

	if(system(str) != 0)
		return 0;
	return 1;
}
