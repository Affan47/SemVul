iwl_mvm_get_used_hw_queues(struct iwl_mvm *mvm,
					 struct ieee80211_vif *exclude_vif)
{
	u8 sta_id;
	struct iwl_mvm_hw_queues_iface_iterator_data data = {
		.exclude_vif = exclude_vif,
		.used_hw_queues =
			BIT(IWL_MVM_OFFCHANNEL_QUEUE) |
			BIT(mvm->aux_queue) |
			BIT(IWL_MVM_CMD_QUEUE),
	};

	lockdep_assert_held(&mvm->mutex);


	ieee80211_iterate_active_interfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_iface_hw_queues_iter, &data);


	ieee80211_iterate_stations_atomic(mvm->hw,
					  iwl_mvm_mac_sta_hw_queues_iter,
					  &data);


	for_each_set_bit(sta_id, mvm->sta_drained, IWL_MVM_STATION_COUNT)
		data.used_hw_queues |= mvm->tfd_drained[sta_id];

	return data.used_hw_queues;
}
