ath10k_wmi_10_4_op_pull_phyerr_ev(struct ath10k *ar,
					     const void *phyerr_buf,
					     int left_len,
					     struct wmi_phyerr_ev_arg *arg)
{
	const struct wmi_10_4_phyerr_event *phyerr = phyerr_buf;
	u32 phy_err_mask;
	int i;

	if (left_len < sizeof(*phyerr)) {
		ath10k_warn(ar, "wrong phyerr event head len %d (need: >=%zd)\n",
			    left_len, sizeof(*phyerr));
		return -EINVAL;
	}

	arg->tsf_timestamp = __le32_to_cpu(phyerr->tsf_timestamp);
	arg->freq1 = __le16_to_cpu(phyerr->freq1);
	arg->freq2 = __le16_to_cpu(phyerr->freq2);
	arg->rssi_combined = phyerr->rssi_combined;
	arg->chan_width_mhz = phyerr->chan_width_mhz;
	arg->buf_len = __le32_to_cpu(phyerr->buf_len);
	arg->buf = phyerr->buf;
	arg->hdr_len = sizeof(*phyerr);

	for (i = 0; i < 4; i++)
		arg->nf_chains[i] = __le16_to_cpu(phyerr->nf_chains[i]);

	phy_err_mask = __le32_to_cpu(phyerr->phy_err_mask[0]);

	if (phy_err_mask & PHY_ERROR_10_4_SPECTRAL_SCAN_MASK)
		arg->phy_err_code = PHY_ERROR_SPECTRAL_SCAN;
	else if (phy_err_mask & PHY_ERROR_10_4_RADAR_MASK)
		arg->phy_err_code = PHY_ERROR_RADAR;
	else
		arg->phy_err_code = PHY_ERROR_UNKNOWN;

	return 0;
}
