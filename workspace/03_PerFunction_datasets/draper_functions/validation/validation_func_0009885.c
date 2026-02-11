_dbus_unity_protocol_scope_service_open_channel_ready (GObject * source_object, GAsyncResult * _res_, gpointer _user_data_) {
	GDBusMethodInvocation * invocation;
	GError* error = NULL;
	GDBusMessage* _reply_message;
	GVariant* _reply;
	GVariantBuilder _reply_builder;
	GHashTable* out_hints = NULL;
	GVariantBuilder _tmp100_;
	GHashTableIter _tmp101_;
	gpointer _tmp102_;
	gpointer _tmp103_;
	gchar* result;
	invocation = _user_data_;
	result = unity_protocol_scope_service_open_channel_finish ((UnityProtocolScopeService*) source_object, _res_, &out_hints, &error);
	if (error) {
		g_dbus_method_invocation_return_gerror (invocation, error);
		return;
	}
	_reply_message = g_dbus_message_new_method_reply (g_dbus_method_invocation_get_message (invocation));
	g_variant_builder_init (&_reply_builder, G_VARIANT_TYPE_TUPLE);
	g_hash_table_iter_init (&_tmp101_, out_hints);
	g_variant_builder_init (&_tmp100_, G_VARIANT_TYPE ("a{sv}"));
	while (g_hash_table_iter_next (&_tmp101_, &_tmp102_, &_tmp103_)) {
		gchar* _key;
		GVariant* _value;
		_key = (gchar*) _tmp102_;
		_value = (GVariant*) _tmp103_;
		g_variant_builder_add (&_tmp100_, "{?*}", g_variant_new_string (_key), g_variant_new_variant (_value));
	}
	g_variant_builder_add_value (&_reply_builder, g_variant_builder_end (&_tmp100_));
	g_variant_builder_add_value (&_reply_builder, g_variant_new_string (result));
	_g_free0 (result);
	_reply = g_variant_builder_end (&_reply_builder);
	g_dbus_message_set_body (_reply_message, _reply);
	_g_hash_table_unref0 (out_hints);
	g_dbus_connection_send_message (g_dbus_method_invocation_get_connection (invocation), _reply_message, G_DBUS_SEND_MESSAGE_FLAGS_NONE, NULL, NULL);
	g_object_unref (invocation);
	g_object_unref (_reply_message);
}
