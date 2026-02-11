mwifiex_check_last_packet_indication(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	u8 ret = false;

	if (!adapter->sleep_period.period)
		return ret;
	if (mwifiex_wmm_lists_empty(adapter))
			ret = true;

	if (ret && !adapter->cmd_sent && !adapter->curr_cmd &&
	    !is_command_pending(adapter)) {
		adapter->delay_null_pkt = false;
		ret = true;
	} else {
		ret = false;
		adapter->delay_null_pkt = true;
	}
	return ret;
}
