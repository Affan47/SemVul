_nm_device_type_for_path (DBusGConnection *connection,
                          const char *path)
{
	DBusGProxy *proxy;
	GError *err = NULL;
	GValue value = {0,};
	NMDeviceType nm_dtype;

	proxy = dbus_g_proxy_new_for_name (connection,
									   NM_DBUS_SERVICE,
									   path,
									   "org.freedesktop.DBus.Properties");
	if (!proxy) {
		g_warning ("%s: couldn't create D-Bus object proxy.", __func__);
		return G_TYPE_INVALID;
	}

	if (!dbus_g_proxy_call (proxy,
						    "Get", &err,
						    G_TYPE_STRING, NM_DBUS_INTERFACE_DEVICE,
						    G_TYPE_STRING, "DeviceType",
						    G_TYPE_INVALID,
						    G_TYPE_VALUE, &value, G_TYPE_INVALID)) {
		g_object_unref (proxy);
		g_warning ("Error in get_property: %s\n", err->message);
		g_error_free (err);
	}
	g_object_unref (proxy);

	nm_dtype = g_value_get_uint (&value);
	return _nm_device_gtype_from_dtype (nm_dtype);
}
