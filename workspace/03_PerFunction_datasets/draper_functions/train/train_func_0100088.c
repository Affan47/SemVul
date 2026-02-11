ipw_rfkill_state_work (gpointer user_data)
{
	NMDeviceWifi *self = NM_DEVICE_WIFI (user_data);
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	RfKillState old_state;

	old_state = priv->ipw_rfkill_state;
	priv->ipw_rfkill_state = nm_device_wifi_get_ipw_rfkill_state (self);
	if (priv->ipw_rfkill_state != old_state)
		g_object_notify (G_OBJECT (self), NM_DEVICE_WIFI_IPW_RFKILL_STATE);

	return TRUE;
}
