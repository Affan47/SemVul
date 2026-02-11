ui_to_setting (CEPageWifi *self)
{
	CEPageWifiPrivate *priv = CE_PAGE_WIFI_GET_PRIVATE (self);
	GByteArray *ssid;
	GByteArray *bssid = NULL;
	GByteArray *device_mac = NULL;
	GByteArray *cloned_mac = NULL;
	const char *mode;
	const char *band;
	GtkWidget *entry;

	ssid = ce_page_wifi_get_ssid (self);

	if (gtk_combo_box_get_active (priv->mode) == 1)
		mode = "adhoc";
	else
		mode = "infrastructure";

	switch (gtk_combo_box_get_active (priv->band)) {
	case 1:
		band = "a";
		break;
	case 2:
		band = "bg";
		break;
	case 0:
	default:
		band = NULL;
		break;
	}

	entry = gtk_bin_get_child (GTK_BIN (priv->bssid));

	if (entry && mode && strcmp (mode, "adhoc") != 0)
		bssid = ce_page_entry_to_mac (GTK_ENTRY (entry), ARPHRD_ETHER, NULL);
	entry = gtk_bin_get_child (GTK_BIN (priv->device_mac));
	if (entry)
		device_mac = ce_page_entry_to_mac (GTK_ENTRY (entry), ARPHRD_ETHER, NULL);
	cloned_mac = ce_page_entry_to_mac (priv->cloned_mac, ARPHRD_ETHER, NULL);

	g_object_set (priv->setting,
	              NM_SETTING_WIRELESS_SSID, ssid,
	              NM_SETTING_WIRELESS_BSSID, bssid,
	              NM_SETTING_WIRELESS_MAC_ADDRESS, device_mac,
	              NM_SETTING_WIRELESS_CLONED_MAC_ADDRESS, cloned_mac,
	              NM_SETTING_WIRELESS_MODE, mode,
	              NM_SETTING_WIRELESS_BAND, band,
	              NM_SETTING_WIRELESS_CHANNEL, gtk_spin_button_get_value_as_int (priv->channel),
	              NM_SETTING_WIRELESS_RATE, gtk_spin_button_get_value_as_int (priv->rate),
	              NM_SETTING_WIRELESS_TX_POWER, gtk_spin_button_get_value_as_int (priv->tx_power),
	              NM_SETTING_WIRELESS_MTU, gtk_spin_button_get_value_as_int (priv->mtu),
	              NULL);

	if (ssid)
		g_byte_array_free (ssid, TRUE);
	if (device_mac)
		g_byte_array_free (device_mac, TRUE);
	if (cloned_mac)
		g_byte_array_free (cloned_mac, TRUE);
	if (bssid)
		g_byte_array_free (bssid, TRUE);
}
