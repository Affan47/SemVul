iwl_mvm_stat_iterator(void *_data, u8 *mac,
				  struct ieee80211_vif *vif)
{
	struct iwl_mvm_stat_data *data = _data;
	struct iwl_mvm *mvm = data->mvm;
	int sig = -data->beacon_filter_average_energy;
	int last_event;
	int thold = vif->bss_conf.cqm_rssi_thold;
	int hyst = vif->bss_conf.cqm_rssi_hyst;
	u16 id = le32_to_cpu(data->mac_id);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);


	if (data->general) {
		mvmvif->beacon_stats.num_beacons =
			le32_to_cpu(data->general->beacon_counter[mvmvif->id]);
		mvmvif->beacon_stats.avg_signal =
			-data->general->beacon_average_energy[mvmvif->id];
	}

	if (mvmvif->id != id)
		return;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (sig == 0) {
		IWL_DEBUG_RX(mvm, "RSSI is 0 - skip signal based decision\n");
		return;
	}

	mvmvif->bf_data.ave_beacon_signal = sig;


	if (mvmvif->bf_data.bt_coex_min_thold !=
	    mvmvif->bf_data.bt_coex_max_thold) {
		last_event = mvmvif->bf_data.last_bt_coex_event;
		if (sig > mvmvif->bf_data.bt_coex_max_thold &&
		    (last_event <= mvmvif->bf_data.bt_coex_min_thold ||
		     last_event == 0)) {
			mvmvif->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex high %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vif, RSSI_EVENT_HIGH);
		} else if (sig < mvmvif->bf_data.bt_coex_min_thold &&
			   (last_event >= mvmvif->bf_data.bt_coex_max_thold ||
			    last_event == 0)) {
			mvmvif->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex low %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vif, RSSI_EVENT_LOW);
		}
	}

	if (!(vif->driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI))
		return;


	last_event = mvmvif->bf_data.last_cqm_event;
	if (thold && sig < thold && (last_event == 0 ||
				     sig < last_event - hyst)) {
		mvmvif->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm low %d\n",
			     sig);
		ieee80211_cqm_rssi_notify(
			vif,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
			GFP_KERNEL);
	} else if (sig > thold &&
		   (last_event == 0 || sig > last_event + hyst)) {
		mvmvif->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm high %d\n",
			     sig);
		ieee80211_cqm_rssi_notify(
			vif,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
			GFP_KERNEL);
	}
}
