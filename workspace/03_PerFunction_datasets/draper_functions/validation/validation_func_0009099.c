ar9003_hw_rtt_force_restore(struct ath_hw *ah)
{
	if (!ath9k_hw_wait(ah, AR_PHY_RTT_CTRL,
			   AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE,
			   0, RTT_RESTORE_TIMEOUT))
		return false;

	REG_RMW_FIELD(ah, AR_PHY_RTT_CTRL,
		      AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE, 1);

	if (!ath9k_hw_wait(ah, AR_PHY_RTT_CTRL,
			   AR_PHY_RTT_CTRL_FORCE_RADIO_RESTORE,
			   0, RTT_RESTORE_TIMEOUT))
		return false;

	return true;
}
