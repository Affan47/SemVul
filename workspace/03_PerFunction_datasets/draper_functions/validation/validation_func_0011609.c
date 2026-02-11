iwl_mvm_tdls_sta_deinit(struct iwl_mvm *mvm,
				    struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	unsigned long sta_msk;
	int i;

	lockdep_assert_held(&mvm->mutex);


	sta_msk = mvmsta->tfd_queue_msk;
	for_each_set_bit(i, &sta_msk, sizeof(sta_msk) * BITS_PER_BYTE)
		iwl_mvm_disable_txq(mvm, i, i, IWL_MAX_TID_COUNT, 0);
}
