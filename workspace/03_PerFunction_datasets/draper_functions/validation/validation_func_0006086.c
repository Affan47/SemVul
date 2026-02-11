act_stage2_config (NMDevice *dev, NMDeviceStateReason *reason)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (dev);
	GSList *iter;


	for (iter = priv->slaves; iter; iter = g_slist_next (iter)) {
		SlaveInfo *info = iter->data;

		if (nm_device_get_state (info->slave) == NM_DEVICE_STATE_IP_CONFIG)
			nm_device_enslave_slave (dev, info->slave, nm_device_get_connection (info->slave));
	}


	return NM_ACT_STAGE_RETURN_SUCCESS;
}
