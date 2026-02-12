respip_rewrite_reply(const struct query_info* qinfo,
	const struct respip_client_info* cinfo, const struct reply_info* rep,
	struct reply_info** new_repp, struct respip_action_info* actinfo,
	struct ub_packed_rrset_key** alias_rrset, int search_only,
	struct regional* region)
{
	const uint8_t* ctaglist;
	size_t ctaglen;
	const uint8_t* tag_actions;
	size_t tag_actions_size;
	struct config_strlist** tag_datas;
	size_t tag_datas_size;
	struct view* view = NULL;
	struct respip_set* ipset = NULL;
	size_t rrset_id = 0;
	enum respip_action action = respip_none;
	int tag = -1;
	const struct resp_addr* raddr = NULL;
	int ret = 1;
	struct ub_packed_rrset_key* redirect_rrset = NULL;

	if(!cinfo)
		goto done;
	ctaglist = cinfo->taglist;
	ctaglen = cinfo->taglen;
	tag_actions = cinfo->tag_actions;
	tag_actions_size = cinfo->tag_actions_size;
	tag_datas = cinfo->tag_datas;
	tag_datas_size = cinfo->tag_datas_size;
	view = cinfo->view;
	ipset = cinfo->respip_set;


	if(view) {
		lock_rw_rdlock(&view->lock);
		if(view->respip_set) {
			if((raddr = respip_addr_lookup(rep,
				&view->respip_set->ip_tree, &rrset_id))) {


				action = raddr->action;
			}
		}
		if(!raddr && !view->isfirst)
			goto done;
	}
	if(!raddr && ipset && (raddr = respip_addr_lookup(rep, &ipset->ip_tree,
		&rrset_id))) {
		action = (enum respip_action)local_data_find_tag_action(
			raddr->taglist, raddr->taglen, ctaglist, ctaglen,
			tag_actions, tag_actions_size,
			(enum localzone_type)raddr->action, &tag,
			ipset->tagname, ipset->num_tags);
	}
	if(raddr && !search_only) {
		int result = 0;


		if(action != respip_always_refuse
			&& action != respip_always_transparent
			&& action != respip_always_nxdomain
			&& (result = respip_data_answer(raddr, action,
			qinfo->qtype, rep, rrset_id, new_repp, tag, tag_datas,
			tag_datas_size, ipset->tagname, ipset->num_tags,
			&redirect_rrset, region)) < 0) {
			ret = 0;
			goto done;
		}


		if(!result && !respip_nodata_answer(qinfo->qtype, action, rep,
			rrset_id, new_repp, region)) {
			ret = 0;
			goto done;
		}
	}
  done:
	if(view) {
		lock_rw_unlock(&view->lock);
	}
	if(ret) {


		if(redirect_rrset &&
			redirect_rrset->rk.type == ntohs(LDNS_RR_TYPE_CNAME) &&
			qinfo->qtype != LDNS_RR_TYPE_ANY)
			*alias_rrset = redirect_rrset;

		ret = populate_action_info(actinfo, action, raddr,
			redirect_rrset, tag, ipset, search_only, region);
	}
	return ret;
}
