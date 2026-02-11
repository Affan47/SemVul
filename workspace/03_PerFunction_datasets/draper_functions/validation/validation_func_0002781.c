verify (NMSetting *setting, GSList *all_settings, GError **error)
{
	NMSettingWirelessPrivate *priv = NM_SETTING_WIRELESS_GET_PRIVATE (setting);
	const char *valid_modes[] = { NM_SETTING_WIRELESS_MODE_INFRA, NM_SETTING_WIRELESS_MODE_ADHOC, NM_SETTING_WIRELESS_MODE_AP, NULL };
	const char *valid_bands[] = { "a", "bg", NULL };
	GSList *iter;

	if (!priv->ssid) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_MISSING_PROPERTY,
		             NM_SETTING_WIRELESS_SSID);
		return FALSE;
	}

	if (!priv->ssid->len || priv->ssid->len > 32) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_SSID);
		return FALSE;
	}

	if (priv->mode && !_nm_utils_string_in_list (priv->mode, valid_modes)) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_MODE);
		return FALSE;
	}

	if (priv->band && !_nm_utils_string_in_list (priv->band, valid_bands)) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_BAND);
		return FALSE;
	}

	if (priv->channel && !priv->band) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_CHANNEL_REQUIRES_BAND,
		             NM_SETTING_WIRELESS_BAND);
		return FALSE;
	}

	if (priv->channel) {
		if (!nm_utils_wifi_is_channel_valid (priv->channel, priv->band)) {
			g_set_error (error,
			             NM_SETTING_WIRELESS_ERROR,
			             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
			             NM_SETTING_WIRELESS_CHANNEL);
			return FALSE;
		}
	}

	if (priv->bssid && priv->bssid->len != ETH_ALEN) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_BSSID);
		return FALSE;
	}

	if (priv->device_mac_address && priv->device_mac_address->len != ETH_ALEN) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_MAC_ADDRESS);
		return FALSE;
	}

	if (priv->cloned_mac_address && priv->cloned_mac_address->len != ETH_ALEN) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
		             NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS);
		return FALSE;
	}

	for (iter = priv->mac_address_blacklist; iter; iter = iter->next) {
		struct ether_addr addr;

		if (!ether_aton_r (iter->data, &addr)) {
			g_set_error (error,
			             NM_SETTING_WIRELESS_ERROR,
			             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
			             NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST);
			return FALSE;
		}
	}

	for (iter = priv->seen_bssids; iter; iter = iter->next) {
		struct ether_addr addr;

		if (!ether_aton_r (iter->data, &addr)) {
			g_set_error (error,
			             NM_SETTING_WIRELESS_ERROR,
			             NM_SETTING_WIRELESS_ERROR_INVALID_PROPERTY,
			             NM_SETTING_WIRELESS_SEEN_BSSIDS);
			return FALSE;
		}
	}

	if (   priv->security
	    && !g_slist_find_custom (all_settings, priv->security, find_setting_by_name)) {
		g_set_error (error,
		             NM_SETTING_WIRELESS_ERROR,
		             NM_SETTING_WIRELESS_ERROR_MISSING_SECURITY_SETTING,
		             NULL);
		return FALSE;
	}

	return TRUE;
}
