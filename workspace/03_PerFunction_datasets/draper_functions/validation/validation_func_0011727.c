mwifiex_ret_802_11_scan(struct mwifiex_private *priv,
			    struct host_cmd_ds_command *resp)
{
	int ret = 0;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_ds_802_11_scan_rsp *scan_rsp;
	struct mwifiex_ie_types_data *tlv_data;
	struct mwifiex_ie_types_tsf_timestamp *tsf_tlv;
	u8 *bss_info;
	u32 scan_resp_size;
	u32 bytes_left;
	u32 idx;
	u32 tlv_buf_size;
	struct mwifiex_ie_types_chan_band_list_param_set *chan_band_tlv;
	struct chan_band_param_set *chan_band;
	u8 is_bgscan_resp;
	__le64 fw_tsf = 0;
	u8 *radio_type;

	is_bgscan_resp = (le16_to_cpu(resp->command)
			  == HostCmd_CMD_802_11_BG_SCAN_QUERY);
	if (is_bgscan_resp)
		scan_rsp = &resp->params.bg_scan_query_resp.scan_resp;
	else
		scan_rsp = &resp->params.scan_resp;


	if (scan_rsp->number_of_sets > MWIFIEX_MAX_AP) {
		mwifiex_dbg(adapter, ERROR,
			    "SCAN_RESP: too many AP returned (%d)\n",
			    scan_rsp->number_of_sets);
		ret = -1;
		goto check_next_scan;
	}


	mwifiex_11h_get_csa_closed_channel(priv);

	bytes_left = le16_to_cpu(scan_rsp->bss_descript_size);
	mwifiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: bss_descript_size %d\n",
		    bytes_left);

	scan_resp_size = le16_to_cpu(resp->size);

	mwifiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: returned %d APs before parsing\n",
		    scan_rsp->number_of_sets);

	bss_info = scan_rsp->bss_desc_and_tlv_buffer;


	tlv_buf_size = scan_resp_size - (bytes_left
					 + sizeof(scan_rsp->bss_descript_size)
					 + sizeof(scan_rsp->number_of_sets)
					 + S_DS_GEN);

	tlv_data = (struct mwifiex_ie_types_data *) (scan_rsp->
						 bss_desc_and_tlv_buffer +
						 bytes_left);


	mwifiex_ret_802_11_scan_get_tlv_ptrs(adapter, tlv_data, tlv_buf_size,
					     TLV_TYPE_TSFTIMESTAMP,
					     (struct mwifiex_ie_types_data **)
					     &tsf_tlv);


	mwifiex_ret_802_11_scan_get_tlv_ptrs(adapter, tlv_data, tlv_buf_size,
					     TLV_TYPE_CHANNELBANDLIST,
					     (struct mwifiex_ie_types_data **)
					     &chan_band_tlv);

	for (idx = 0; idx < scan_rsp->number_of_sets && bytes_left; idx++) {


		if (tsf_tlv)
			memcpy(&fw_tsf, &tsf_tlv->tsf_data[idx * TSF_DATA_SIZE],
			       sizeof(fw_tsf));

		if (chan_band_tlv) {
			chan_band = &chan_band_tlv->chan_band_param[idx];
			radio_type = &chan_band->radio_type;
		} else {
			radio_type = NULL;
		}

		ret = mwifiex_parse_single_response_buf(priv, &bss_info,
							&bytes_left,
							le64_to_cpu(fw_tsf),
							radio_type, false, 0);
		if (ret)
			goto check_next_scan;
	}

check_next_scan:
	mwifiex_check_next_scan_command(priv);
	return ret;
}
