add_blob_cb (DBusGProxy *proxy, DBusGProxyCall *call_id, gpointer user_data)
{
	NMSupplicantInfo *info = (NMSupplicantInfo *) user_data;
	NMSupplicantInterfacePrivate *priv = NM_SUPPLICANT_INTERFACE_GET_PRIVATE (info->interface);
	GError *err = NULL;
	guint tmp;

	priv->blobs_left--;

	if (!dbus_g_proxy_end_call (proxy, call_id, &err, G_TYPE_UINT, &tmp, G_TYPE_INVALID)) {
		nm_log_warn (LOGD_SUPPLICANT, "Couldn't set network certificates: %s.", err->message);
		emit_error_helper (info->interface, err);
		g_error_free (err);
	} else
		call_select_network (info->interface);
}
