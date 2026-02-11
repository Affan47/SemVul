btc8723b2ant_action_hid(struct btc_coexist *btcoexist)
{
	u8 wifi_rssi_state, bt_rssi_state;
	u32 wifi_bw;

	wifi_rssi_state = btc8723b2ant_wifi_rssi_state(btcoexist,
						       0, 2, 15, 0);
	bt_rssi_state = btc8723b2ant_bt_rssi_state(2, 29, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	if (btc8723b_need_dec_pwr(btcoexist))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	else
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wifi_bw);

	if (BTC_WIFI_BW_LEGACY == wifi_bw)
		btc8723b_coex_tbl_type(btcoexist, NORMAL_EXEC, 7);
	else
		btc8723b_coex_tbl_type(btcoexist, NORMAL_EXEC, 9);

	if ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH))
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	else
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 13);


	if (BTC_WIFI_BW_HT40 == wifi_bw) {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8723b2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8723b2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8723b2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8723b2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	} else {
		if ((wifi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wifi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) {
			btc8723b2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8723b2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		} else {
			btc8723b2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8723b2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		}
	}
}
