swsmi_rfkill_query(struct rfkill *rfkill, void *priv)
{
	struct samsung_rfkill *srfkill = priv;
	struct samsung_laptop *samsung = srfkill->samsung;
	struct sabi_data data;
	int ret;

	ret = swsmi_wireless_status(samsung, &data);
	if (ret)
		return ;

	if (srfkill->type == RFKILL_TYPE_WLAN)
		ret = data.data[WL_STATUS_WLAN];
	else if (srfkill->type == RFKILL_TYPE_BLUETOOTH)
		ret = data.data[WL_STATUS_BT];
	else
		return ;

	rfkill_set_sw_state(rfkill, !ret);
}
