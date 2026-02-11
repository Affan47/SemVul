data_cal_complete_get_attachment_uris_cb (GObject *source_object,
                                          GAsyncResult *result,
                                          gpointer user_data)
{
	AsyncContext *async_context = user_data;
	GQueue queue = G_QUEUE_INIT;
	GError *error = NULL;

	e_cal_backend_get_attachment_uris_finish (
		E_CAL_BACKEND (source_object), result, &queue, &error);

	if (error == NULL) {
		gchar **strv;
		gint ii = 0;

		strv = g_new0 (gchar *, queue.length + 1);

		while (!g_queue_is_empty (&queue)) {
			gchar *uri;

			uri = g_queue_pop_head (&queue);
			strv[ii++] = e_util_utf8_make_valid (uri);
			g_free (uri);
		}

		e_dbus_calendar_complete_get_attachment_uris (
			async_context->interface,
			async_context->invocation,
			(const gchar * const *) strv);

		g_strfreev (strv);
	} else {
		data_cal_convert_to_client_error (error);
		g_dbus_method_invocation_take_error (
			async_context->invocation, error);
	}

	async_context_free (async_context);
}
