secret_service_create_collection_dbus_path (SecretService *self,
                                            GHashTable *properties,
                                            const gchar *alias,
                                            SecretCollectionCreateFlags flags,
                                            GCancellable *cancellable,
                                            GAsyncReadyCallback callback,
                                            gpointer user_data)
{
	GSimpleAsyncResult *res;
	CollectionClosure *closure;
	GVariant *params;
	GVariant *props;
	GDBusProxy *proxy;

	g_return_if_fail (SECRET_IS_SERVICE (self));
	g_return_if_fail (properties != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	if (alias == NULL)
		alias = "";

	res = g_simple_async_result_new (G_OBJECT (self), callback, user_data,
	                                 secret_service_create_collection_dbus_path);
	closure = g_slice_new0 (CollectionClosure);
	closure->cancellable = cancellable ? g_object_ref (cancellable) : NULL;
	g_simple_async_result_set_op_res_gpointer (res, closure, collection_closure_free);

	props = _secret_util_variant_for_properties (properties);
	params = g_variant_new ("(@a{sv}s)", props, alias);
	proxy = G_DBUS_PROXY (self);

	g_dbus_connection_call (g_dbus_proxy_get_connection (proxy),
	                        g_dbus_proxy_get_name (proxy),
	                        g_dbus_proxy_get_object_path (proxy),
	                        SECRET_SERVICE_INTERFACE,
	                        "CreateCollection", params, G_VARIANT_TYPE ("(oo)"),
	                        G_DBUS_CALL_FLAGS_NONE, -1,
	                        closure->cancellable,
	                        on_create_collection_called,
	                        g_object_ref (res));

	g_object_unref (res);

}
