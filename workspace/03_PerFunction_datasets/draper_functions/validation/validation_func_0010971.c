ar9002_hw_init_mode_gain_regs(struct ath_hw *ah)
{
	if (AR_SREV_9287_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
		ar9287Modes_rx_gain_9287_1_1,
		ARRAY_SIZE(ar9287Modes_rx_gain_9287_1_1), 6);
	else if (AR_SREV_9280_20(ah))
		ar9280_20_hw_init_rxgain_ini(ah);

	if (AR_SREV_9287_11_OR_LATER(ah)) {
		INIT_INI_ARRAY(&ah->iniModesTxGain,
		ar9287Modes_tx_gain_9287_1_1,
		ARRAY_SIZE(ar9287Modes_tx_gain_9287_1_1), 6);
	} else if (AR_SREV_9280_20(ah)) {
		ar9280_20_hw_init_txgain_ini(ah);
	} else if (AR_SREV_9285_12_OR_LATER(ah)) {
		u32 txgain_type = ah->eep_ops->get_eeprom(ah, EEP_TXGAIN_TYPE);


		if (txgain_type == AR5416_EEP_TXGAIN_HIGH_POWER) {
			if (AR_SREV_9285E_20(ah)) {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9285Modes_XE2_0_high_power,
				ARRAY_SIZE(
				  ar9285Modes_XE2_0_high_power), 6);
			} else {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9285Modes_high_power_tx_gain_9285_1_2,
				ARRAY_SIZE(
				  ar9285Modes_high_power_tx_gain_9285_1_2), 6);
			}
		} else {
			if (AR_SREV_9285E_20(ah)) {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9285Modes_XE2_0_normal_power,
				ARRAY_SIZE(
				  ar9285Modes_XE2_0_normal_power), 6);
			} else {
				INIT_INI_ARRAY(&ah->iniModesTxGain,
				ar9285Modes_original_tx_gain_9285_1_2,
				ARRAY_SIZE(
				  ar9285Modes_original_tx_gain_9285_1_2), 6);
			}
		}
	}
}
