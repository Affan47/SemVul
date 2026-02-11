act_stage3_ip4_config_start (NMDevice *device,
                             NMIP4Config **out_config,
                             NMDeviceStateReason *reason)
{
	NMDeviceAdsl *self = NM_DEVICE_ADSL (device);
	NMDeviceAdslPrivate *priv = NM_DEVICE_ADSL_GET_PRIVATE (self);
	NMConnection *connection;
	NMSettingAdsl *s_adsl;
	NMActRequest *req;
	GError *err = NULL;
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_FAILURE;
	const char *iface = nm_device_get_iface (device);
	const char *ppp_iface;

	req = nm_device_get_act_request (device);
	g_assert (req);

	connection = nm_act_request_get_connection (req);
	g_assert (req);

	s_adsl = nm_connection_get_setting_adsl (connection);
	g_assert (s_adsl);


	if (g_strcmp0 (nm_setting_adsl_get_protocol (s_adsl), NM_SETTING_ADSL_PROTOCOL_PPPOE) == 0) {
		g_assert (priv->nas_ifname);
		ppp_iface = priv->nas_ifname;

		nm_log_dbg (LOGD_ADSL, "(%s): starting PPPoE on NAS interface %s",
			        iface, priv->nas_ifname);
	} else {
		ppp_iface = iface;
		nm_log_dbg (LOGD_ADSL, "(%s): starting PPPoA", iface);
	}

	priv->ppp_manager = nm_ppp_manager_new (ppp_iface);
	if (nm_ppp_manager_start (priv->ppp_manager, req, nm_setting_adsl_get_username (s_adsl), 30, &err)) {
		g_signal_connect (priv->ppp_manager, "state-changed",
		                  G_CALLBACK (ppp_state_changed),
		                  self);
		g_signal_connect (priv->ppp_manager, "ip4-config",
		                  G_CALLBACK (ppp_ip4_config),
		                  self);
		ret = NM_ACT_STAGE_RETURN_POSTPONE;
	} else {
		nm_log_warn (LOGD_ADSL, "(%s): PPP failed to start: %s", iface, err->message);
		g_error_free (err);

		g_object_unref (priv->ppp_manager);
		priv->ppp_manager = NULL;

		*reason = NM_DEVICE_STATE_REASON_PPP_START_FAILED;
	}

	return ret;
}
