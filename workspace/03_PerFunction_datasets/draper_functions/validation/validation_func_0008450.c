dispatcher_done_cb (DBusGProxy *proxy, DBusGProxyCall *call, gpointer user_data)
{
	DispatchInfo *info = user_data;
	GError *error = NULL;
	GPtrArray *results = NULL;
	guint i;

	if (dbus_g_proxy_end_call (proxy, call, &error,
	                           DISPATCHER_TYPE_RESULT_ARRAY, &results,
	                           G_TYPE_INVALID)) {
		for (i = 0; results && (i < results->len); i++) {
			GValueArray *item = g_ptr_array_index (results, i);
			GValue *tmp;
			const char *script, *err;
			DispatchResult result;

			if (   (G_VALUE_TYPE (g_value_array_get_nth (item, 0)) == G_TYPE_STRING)
			    && (G_VALUE_TYPE (g_value_array_get_nth (item, 1)) == G_TYPE_UINT)
			    && (G_VALUE_TYPE (g_value_array_get_nth (item, 2)) == G_TYPE_STRING)) {

				tmp = g_value_array_get_nth (item, 1);
				result = g_value_get_uint (tmp);
				if (result != DISPATCH_RESULT_SUCCESS) {

					tmp = g_value_array_get_nth (item, 0);
					script = g_value_get_string (tmp);


					tmp = g_value_array_get_nth (item, 2);
					err = g_value_get_string (tmp);

					nm_log_warn (LOGD_CORE, "Dispatcher script %s: %s",
					             dispatch_result_to_string (result), err);
				}
			} else
				nm_log_dbg (LOGD_CORE, "Dispatcher result element %d invalid type", i);

			g_value_array_free (item);
		}
		g_ptr_array_free (results, TRUE);
	} else {
		g_assert (error);
		nm_log_warn (LOGD_CORE, "Dispatcher failed: (%d) %s", error->code, error->message);
	}

	if (info->callback)
		info->callback (info, info->user_data);

	g_clear_error (&error);
	g_object_unref (proxy);
}
