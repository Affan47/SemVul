nm_manager_get_ipw_rfkill_state (NMManager *self)
{
	NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (self);
	GSList *iter;
	RfKillState ipw_state = RFKILL_UNBLOCKED;

	for (iter = priv->devices; iter; iter = g_slist_next (iter)) {
		NMDevice *candidate = NM_DEVICE (iter->data);
		RfKillState candidate_state;

		if (nm_device_get_device_type (candidate) == NM_DEVICE_TYPE_WIFI) {
			candidate_state = nm_device_wifi_get_ipw_rfkill_state (NM_DEVICE_WIFI (candidate));

			if (candidate_state > ipw_state)
				ipw_state = candidate_state;
		}
	}

	return ipw_state;
}
