ath10k_tpc_config_get_rate(struct ath10k *ar,
				     struct wmi_pdev_tpc_config_event *ev,
				     u32 rate_idx, u32 num_chains,
				     u32 rate_code, u8 type)
{
	u8 tpc, num_streams, preamble, ch, stm_idx;

	num_streams = ATH10K_HW_NSS(rate_code);
	preamble = ATH10K_HW_PREAMBLE(rate_code);
	ch = num_chains - 1;

	tpc = min_t(u8, ev->rates_array[rate_idx], ev->max_reg_allow_pow[ch]);

	if (__le32_to_cpu(ev->num_tx_chain) <= 1)
		goto out;

	if (preamble == WMI_RATE_PREAMBLE_CCK)
		goto out;

	stm_idx = num_streams - 1;
	if (num_chains <= num_streams)
		goto out;

	switch (type) {
	case WMI_TPC_TABLE_TYPE_STBC:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_pow_agstbc[ch - 1][stm_idx]);
		break;
	case WMI_TPC_TABLE_TYPE_TXBF:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_pow_agtxbf[ch - 1][stm_idx]);
		break;
	case WMI_TPC_TABLE_TYPE_CDD:
		tpc = min_t(u8, tpc,
			    ev->max_reg_allow_pow_agcdd[ch - 1][stm_idx]);
		break;
	default:
		ath10k_warn(ar, "unknown wmi tpc table type: %d\n", type);
		tpc = 0;
		break;
	}

out:
	return tpc;
}
