ipsecmod_handle_query(struct module_qstate* qstate,
	struct ipsecmod_qstate* iq, struct ipsecmod_env* ie, int id)
{
	struct ub_packed_rrset_key* rrset_key;
	struct packed_rrset_data* rrset_data;
	size_t i;

	if(!(iq->enabled && iq->is_whitelisted)) {
		qstate->ext_state[id] = module_wait_module;
		return;
	}


	if(!iq->ipseckey_done) {
		if(qstate->qinfo.qtype == LDNS_RR_TYPE_A ||
			qstate->qinfo.qtype == LDNS_RR_TYPE_AAAA) {
			char type[16];
			sldns_wire2str_type_buf(qstate->qinfo.qtype, type,
				sizeof(type));
			verbose(VERB_ALGO, "ipsecmod: query for %s; engaging",
				type);
			qstate->no_cache_store = 1;
		}

		qstate->ext_state[id] = module_wait_module;
		return;
	}


	if(iq->ipseckey_rrset) {
		rrset_data = (struct packed_rrset_data*)iq->ipseckey_rrset->entry.data;
		if(rrset_data) {

			if(!qstate->env->cfg->ipsecmod_ignore_bogus &&
				rrset_data->security == sec_status_bogus) {
				log_err("ipsecmod: bogus IPSECKEY");
				ipsecmod_error(qstate, id);
				return;
			}

			if(!call_hook(qstate, iq, ie) &&
				qstate->env->cfg->ipsecmod_strict) {
				log_err("ipsecmod: ipsecmod-hook failed");
				ipsecmod_error(qstate, id);
				return;
			}


			rrset_key = reply_find_answer_rrset(&qstate->return_msg->qinfo,
				qstate->return_msg->rep);
			rrset_data = (struct packed_rrset_data*)rrset_key->entry.data;
			if(rrset_data->ttl > (time_t)qstate->env->cfg->ipsecmod_max_ttl) {

				rrset_data->ttl = qstate->env->cfg->ipsecmod_max_ttl;
				for(i=0; i<rrset_data->count+rrset_data->rrsig_count; i++)
					rrset_data->rr_ttl[i] = qstate->env->cfg->ipsecmod_max_ttl;

				if(qstate->return_msg->rep->ttl > (time_t)qstate->env->cfg->ipsecmod_max_ttl) {
					qstate->return_msg->rep->ttl =
						qstate->env->cfg->ipsecmod_max_ttl;
					qstate->return_msg->rep->prefetch_ttl = PREFETCH_TTL_CALC(
						qstate->return_msg->rep->ttl);
					qstate->return_msg->rep->serve_expired_ttl = qstate->return_msg->rep->ttl +
						qstate->env->cfg->serve_expired_ttl;
				}
			}
		}
	}

	if(!dns_cache_store(qstate->env, &qstate->qinfo,
		qstate->return_msg->rep, 0, qstate->prefetch_leeway,
		0, qstate->region, qstate->query_flags)) {
		log_err("ipsecmod: out of memory caching record");
	}
	qstate->ext_state[id] = module_finished;
}
