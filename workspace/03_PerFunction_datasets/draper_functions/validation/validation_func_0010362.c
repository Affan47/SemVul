iwlagn_bt_coex_rssi_monitor(struct iwl_priv *priv)
{
	if (priv->bt_is_sco &&
	    priv->bt_traffic_load == IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS)
		iwlagn_bt_adjust_rssi_monitor(priv, true);
	else
		iwlagn_bt_adjust_rssi_monitor(priv, false);
}
