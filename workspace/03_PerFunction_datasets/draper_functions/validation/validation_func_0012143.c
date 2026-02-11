_secret_util_set_property (GDBusProxy *proxy,
                           const gchar *property,
                           GVariant *value,
                           gpointer result_tag,
                           GCancellable *cancellable,
                           GAsyncReadyCallback callback,
                           gpointer user_data)
{
	GSimpleAsyncResult *res;
	SetClosure *closure;

	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	res = g_simple_async_result_new (G_OBJECT (proxy), callback, user_data, result_tag);
	closure = g_slice_new0 (SetClosure);
	closure->property = g_strdup (property);
	closure->value = g_variant_ref_sink (value);
	g_simple_async_result_set_op_res_gpointer (res, closure, set_closure_free);

	g_dbus_connection_call (g_dbus_proxy_get_connection (proxy),
	                        g_dbus_proxy_get_name (proxy),
	                        g_dbus_proxy_get_object_path (proxy),
	                        SECRET_PROPERTIES_INTERFACE,
	                        "Set",
	                        g_variant_new ("(ssv)",
	                                       g_dbus_proxy_get_interface_name (proxy),
	                                       property,
	                                       closure->value),
	                        G_VARIANT_TYPE ("()"),
	                        G_DBUS_CALL_FLAGS_NO_AUTO_START, -1,
	                        cancellable, on_set_property,
	                        g_object_ref (res));

	g_object_unref (res);
}
