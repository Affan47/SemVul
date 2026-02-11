rs_tpc_perform(struct iwl_mvm *mvm,
			   struct ieee80211_sta *sta,
			   struct iwl_lq_sta *lq_sta,
			   struct iwl_scale_tbl_info *tbl)
{
	struct iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	struct ieee80211_vif *vif = mvm_sta->vif;
	struct ieee80211_chanctx_conf *chanctx_conf;
	enum ieee80211_band band;
	struct iwl_rate_scale_data *window;
	struct rs_rate *rate = &tbl->rate;
	enum tpc_action action;
	s32 sr;
	u8 cur = lq_sta->lq.reduced_tpc;
	int current_tpt;
	int weak, strong;
	int weak_tpt = IWL_INVALID_VALUE, strong_tpt = IWL_INVALID_VALUE;

#ifdef CONFIG_MAC80211_DEBUGFS
	if (lq_sta->pers.dbg_fixed_txp_reduction <= TPC_MAX_REDUCTION) {
		IWL_DEBUG_RATE(mvm, "fixed tpc: %d\n",
			       lq_sta->pers.dbg_fixed_txp_reduction);
		lq_sta->lq.reduced_tpc = lq_sta->pers.dbg_fixed_txp_reduction;
		return cur != lq_sta->pers.dbg_fixed_txp_reduction;
	}
#endif

	rcu_read_lock();
	chanctx_conf = rcu_dereference(vif->chanctx_conf);
	if (WARN_ON(!chanctx_conf))
		band = IEEE80211_NUM_BANDS;
	else
		band = chanctx_conf->def.chan->band;
	rcu_read_unlock();

	if (!rs_tpc_allowed(mvm, vif, rate, band)) {
		IWL_DEBUG_RATE(mvm,
			       "tpc is not allowed. remove txp restrictions\n");
		lq_sta->lq.reduced_tpc = TPC_NO_REDUCTION;
		return cur != TPC_NO_REDUCTION;
	}

	rs_get_adjacent_txp(mvm, cur, &weak, &strong);


	window = tbl->tpc_win;
	sr = window[cur].success_ratio;
	current_tpt = window[cur].average_tpt;
	if (weak != TPC_INVALID)
		weak_tpt = window[weak].average_tpt;
	if (strong != TPC_INVALID)
		strong_tpt = window[strong].average_tpt;

	IWL_DEBUG_RATE(mvm,
		       "(TPC: %d): cur_tpt %d SR %d weak %d strong %d weak_tpt %d strong_tpt %d\n",
		       cur, current_tpt, sr, weak, strong,
		       weak_tpt, strong_tpt);

	action = rs_get_tpc_action(mvm, sr, weak, strong,
				   current_tpt, weak_tpt, strong_tpt);


	if (weak == TPC_INVALID && action == TPC_ACTION_DECREASE) {
		IWL_DEBUG_RATE(mvm, "already in lowest txp, stay\n");
		action = TPC_ACTION_STAY;
	} else if (strong == TPC_INVALID &&
		   (action == TPC_ACTION_INCREASE ||
		    action == TPC_ACTION_NO_RESTIRCTION)) {
		IWL_DEBUG_RATE(mvm, "already in highest txp, stay\n");
		action = TPC_ACTION_STAY;
	}

	switch (action) {
	case TPC_ACTION_DECREASE:
		lq_sta->lq.reduced_tpc = weak;
		return true;
	case TPC_ACTION_INCREASE:
		lq_sta->lq.reduced_tpc = strong;
		return true;
	case TPC_ACTION_NO_RESTIRCTION:
		lq_sta->lq.reduced_tpc = TPC_NO_REDUCTION;
		return true;
	case TPC_ACTION_STAY:

		break;
	}
	return false;
}
