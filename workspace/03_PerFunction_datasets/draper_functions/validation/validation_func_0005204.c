e_gdbus_signal_emission_hook_strv (GSignalInvocationHint *ihint,
                                   guint n_param_values,
                                   const GValue *param_values,
                                   const gchar *signal_name,
                                   const gchar *iface_name)
{
	GObject *object;
	GDBusConnection *connection;
	const gchar *path;
	GVariant *params;
	GVariant *item;
	GVariantBuilder *builder;
	const gchar * const *arg_strv;

	if (n_param_values < 1 || !G_VALUE_HOLDS (&param_values[0], G_TYPE_OBJECT))
		return FALSE;

	object = g_value_get_object (&param_values[0]);
	path = g_object_get_data (object, "gdbus-codegen-path");
	connection = g_object_get_data (object, "gdbus-codegen-connection");
	if (connection == NULL || path == NULL)
		return FALSE;

	builder = g_variant_builder_new (G_VARIANT_TYPE_TUPLE);
	g_assert_cmpint (n_param_values - 1, ==, 1);
	param_values++;
	arg_strv = g_value_get_boxed (param_values);
	item = g_variant_new_strv (arg_strv, -1);
	g_variant_builder_add_value (builder, item);
	param_values++;
	params = g_variant_builder_end (builder);
	g_variant_builder_unref (builder);

	g_dbus_connection_emit_signal (connection, NULL, path, iface_name, signal_name, params, NULL);

	return TRUE;
}
