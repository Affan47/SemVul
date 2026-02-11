iwl_mvm_get_key_sta_id(struct iwl_mvm *mvm,
				 struct ieee80211_vif *vif,
				 struct ieee80211_sta *sta)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (sta) {
		struct iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

		return mvm_sta->sta_id;
	}


	if (vif->type == NL80211_IFTYPE_STATION &&
	    mvmvif->ap_sta_id != IWL_MVM_STATION_COUNT) {
		u8 sta_id = mvmvif->ap_sta_id;

		sta = rcu_dereference_check(mvm->fw_id_to_mac_id[sta_id],
					    lockdep_is_held(&mvm->mutex));


		if (IS_ERR_OR_NULL(sta))
			return IWL_MVM_STATION_COUNT;

		return sta_id;
	}

	return IWL_MVM_STATION_COUNT;
}
