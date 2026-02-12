int dccp_feat_activate_values(struct sock *sk, struct list_head *fn_list)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct dccp_feat_entry *cur, *next;
	int idx;
	dccp_feat_val *fvals[DCCP_FEAT_SUPPORTED_MAX][2] = {
		 [0 ... DCCP_FEAT_SUPPORTED_MAX-1] = { NULL, NULL }
	};

	list_for_each_entry(cur, fn_list, node) {


		if (cur->empty_confirm)
			continue;

		idx = dccp_feat_index(cur->feat_num);
		if (idx < 0) {
			DCCP_BUG("Unknown feature %u", cur->feat_num);
			goto activation_failed;
		}
		if (cur->state != FEAT_STABLE) {
			DCCP_CRIT("Negotiation of %s %s failed in state %s",
				  cur->is_local ? "local" : "remote",
				  dccp_feat_fname(cur->feat_num),
				  dccp_feat_sname[cur->state]);
			goto activation_failed;
		}
		fvals[idx][cur->is_local] = &cur->val;
	}


	for (idx = DCCP_FEAT_SUPPORTED_MAX; --idx >= 0;)
		if (__dccp_feat_activate(sk, idx, 0, fvals[idx][0]) ||
		    __dccp_feat_activate(sk, idx, 1, fvals[idx][1])) {
			DCCP_CRIT("Could not activate %d", idx);
			goto activation_failed;
		}


	list_for_each_entry_safe(cur, next, fn_list, node)
		if (!cur->needs_confirm)
			dccp_feat_list_pop(cur);

	dccp_pr_debug("Activation OK\n");
	return 0;

activation_failed:


	ccid_hc_rx_delete(dp->dccps_hc_rx_ccid, sk);
	ccid_hc_tx_delete(dp->dccps_hc_tx_ccid, sk);
	dp->dccps_hc_rx_ccid = dp->dccps_hc_tx_ccid = NULL;
	dccp_ackvec_free(dp->dccps_hc_rx_ackvec);
	dp->dccps_hc_rx_ackvec = NULL;
	return -1;
}
