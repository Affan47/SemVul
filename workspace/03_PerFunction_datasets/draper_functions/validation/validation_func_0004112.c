nm_ip6_manager_prepare_interface (NMIP6Manager *manager,
                                  int ifindex,
                                  const guint8 *hwaddr,
                                  guint hwaddr_len,
                                  NMSettingIP6Config *s_ip6,
                                  const char *accept_ra_path)
{
	NMIP6ManagerPrivate *priv;
	NMIP6Device *device;
	const char *method = NULL;

	g_return_val_if_fail (NM_IS_IP6_MANAGER (manager), FALSE);
	g_return_val_if_fail (ifindex > 0, FALSE);
	g_return_val_if_fail (hwaddr != NULL, FALSE);
	g_return_val_if_fail (hwaddr_len > 0, FALSE);
	g_return_val_if_fail (hwaddr_len <= NM_UTILS_HWADDR_LEN_MAX, FALSE);

	priv = NM_IP6_MANAGER_GET_PRIVATE (manager);

	device = nm_ip6_device_new (manager, ifindex, hwaddr, hwaddr_len);
	g_return_val_if_fail (device != NULL, FALSE);
	g_return_val_if_fail (   strchr (device->iface, '/') == NULL
	                      && strcmp (device->iface, "all") != 0
	                      && strcmp (device->iface, "default") != 0,
	                      FALSE);

	if (s_ip6)
		method = nm_setting_ip6_config_get_method (s_ip6);
	if (!method)
		method = NM_SETTING_IP6_CONFIG_METHOD_AUTO;


	if (!strcmp (method, NM_SETTING_IP6_CONFIG_METHOD_LINK_LOCAL)) {
		device->target_state = NM_IP6_DEVICE_GOT_LINK_LOCAL;
		nm_utils_do_sysctl (accept_ra_path, "0");
	} else {
		device->target_state = NM_IP6_DEVICE_GOT_ADDRESS;
		nm_utils_do_sysctl (accept_ra_path, "2");
	}

	return TRUE;
}
