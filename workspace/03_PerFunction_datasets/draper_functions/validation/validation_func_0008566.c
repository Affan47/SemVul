_dbus_dvb_id_bus_manager_GetDeviceGroup (DVBIDBusManager* self, GVariant* parameters, GDBusMethodInvocation* invocation) {
	GError* error = NULL;
	GVariantIter _arguments_iter;
	guint group_id = 0U;
	GVariant* _tmp163_;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	char* opath = NULL;
	gboolean result;
	g_variant_iter_init (&_arguments_iter, parameters);
	_tmp163_ = g_variant_iter_next_value (&_arguments_iter);
	group_id = g_variant_get_uint32 (_tmp163_);
	g_variant_unref (_tmp163_);
	result = dvb_id_bus_manager_GetDeviceGroup (self, group_id, &opath, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	g_variant_builder_add_value (&_reply_builder, g_variant_new_object_path (opath));
	g_variant_builder_add_value (&_reply_builder, g_variant_new_boolean (result));
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	_g_free0 (opath);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
