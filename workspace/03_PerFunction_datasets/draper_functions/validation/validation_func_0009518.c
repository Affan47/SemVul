act_stage3_ip4_config_start (NMDevice *self,
                             NMIP4Config **out_config,
                             NMDeviceStateReason *reason)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);
	NMConnection *connection;
	NMSettingIP4Config *s_ip4;
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_FAILURE;
	const char *method = NM_SETTING_IP4_CONFIG_METHOD_AUTO;
	GSList *slaves;
	gboolean ready_slaves;

	g_return_val_if_fail (reason != NULL, NM_ACT_STAGE_RETURN_FAILURE);

	connection = nm_device_get_connection (self);
	g_assert (connection);

	if (priv->is_master && ip4_requires_slaves (connection)) {


		slaves = nm_device_master_get_slaves (self);
		ready_slaves = NM_DEVICE_GET_CLASS (self)->have_any_ready_slaves (self, slaves);
		g_slist_free (slaves);

		if (ready_slaves == FALSE) {
			nm_log_info (LOGD_DEVICE | LOGD_IP4,
			             "(%s): IPv4 config waiting until slaves are ready",
			             nm_device_get_ip_iface (self));
			return NM_ACT_STAGE_RETURN_WAIT;
		}
	}


	s_ip4 = nm_connection_get_setting_ip4_config (connection);
	if (priv->master)
		method = NM_SETTING_IP4_CONFIG_METHOD_DISABLED;
	else if (s_ip4)
		method = nm_setting_ip4_config_get_method (s_ip4);
	else
		method = NM_SETTING_IP4_CONFIG_METHOD_AUTO;


	if (strcmp (method, NM_SETTING_IP4_CONFIG_METHOD_AUTO) == 0)
		ret = dhcp4_start (self, connection, reason);
	else if (strcmp (method, NM_SETTING_IP4_CONFIG_METHOD_LINK_LOCAL) == 0)
		ret = aipd_start (self, reason);
	else if (strcmp (method, NM_SETTING_IP4_CONFIG_METHOD_MANUAL) == 0) {

		*out_config = nm_ip4_config_new ();
		g_assert (*out_config);
		ret = NM_ACT_STAGE_RETURN_SUCCESS;
	} else if (strcmp (method, NM_SETTING_IP4_CONFIG_METHOD_SHARED) == 0) {
		*out_config = shared4_new_config (self, reason);
		if (*out_config) {
			priv->dnsmasq_manager = nm_dnsmasq_manager_new (nm_device_get_ip_iface (self));
			ret = NM_ACT_STAGE_RETURN_SUCCESS;
		} else
			ret = NM_ACT_STAGE_RETURN_FAILURE;
	} else if (strcmp (method, NM_SETTING_IP4_CONFIG_METHOD_DISABLED) == 0) {

		ret = NM_ACT_STAGE_RETURN_STOP;
	} else {
		nm_log_warn (LOGD_IP4, "(%s): unhandled IPv4 config method '%s'; will fail",
		             nm_device_get_ip_iface (self), method);
	}

	return ret;
}
