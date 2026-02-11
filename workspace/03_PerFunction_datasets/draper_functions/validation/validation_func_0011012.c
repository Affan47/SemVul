_set_status (NmaBtDevice *device, const char *fmt, ...)
{
	NmaBtDevicePrivate *priv = NMA_BT_DEVICE_GET_PRIVATE (device);
	va_list args;

	g_free (priv->status);
	priv->status = NULL;

	if (fmt) {
		va_start (args, fmt);
		priv->status = g_strdup_vprintf (fmt, args);
		va_end (args);
		g_message ("%s", priv->status);
	}

	g_object_notify (G_OBJECT (device), NMA_BT_DEVICE_STATUS);
}
