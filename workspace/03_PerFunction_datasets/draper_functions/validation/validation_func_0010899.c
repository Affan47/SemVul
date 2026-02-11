ath5k_get_chan_pcal_surrounding_piers(struct ath5k_hw *ah,
			struct ieee80211_channel *channel,
			struct ath5k_chan_pcal_info **pcinfo_l,
			struct ath5k_chan_pcal_info **pcinfo_r)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	struct ath5k_chan_pcal_info *pcinfo;
	u8 idx_l, idx_r;
	u8 mode, max, i;
	u32 target = channel->center_freq;

	idx_l = 0;
	idx_r = 0;

	switch (channel->hw_value) {
	case AR5K_EEPROM_MODE_11A:
		pcinfo = ee->ee_pwr_cal_a;
		mode = AR5K_EEPROM_MODE_11A;
		break;
	case AR5K_EEPROM_MODE_11B:
		pcinfo = ee->ee_pwr_cal_b;
		mode = AR5K_EEPROM_MODE_11B;
		break;
	case AR5K_EEPROM_MODE_11G:
	default:
		pcinfo = ee->ee_pwr_cal_g;
		mode = AR5K_EEPROM_MODE_11G;
		break;
	}
	max = ee->ee_n_piers[mode] - 1;


	if (target < pcinfo[0].freq) {
		idx_l = idx_r = 0;
		goto done;
	}


	if (target > pcinfo[max].freq) {
		idx_l = idx_r = max;
		goto done;
	}


	for (i = 0; i <= max; i++) {


		if (pcinfo[i].freq == target) {
			idx_l = idx_r = i;
			goto done;
		}


		if (target < pcinfo[i].freq) {
			idx_r = i;
			idx_l = idx_r - 1;
			goto done;
		}
	}

done:
	*pcinfo_l = &pcinfo[idx_l];
	*pcinfo_r = &pcinfo[idx_r];
}
