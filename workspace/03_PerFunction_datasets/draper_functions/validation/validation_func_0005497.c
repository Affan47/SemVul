e_ag_account_windows_live_got_me_cb (RestProxyCall *call,
                                     const GError *error,
                                     GObject *weak_object,
                                     gpointer user_data)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;
	JsonParser *json_parser;
	JsonObject *json_object;
	JsonNode *json_node;
	const gchar *json_string;
	gchar *id;
	gchar *email;
	GError *local_error = NULL;

	simple = G_SIMPLE_ASYNC_RESULT (user_data);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	if (error != NULL) {
		g_simple_async_result_set_from_error (simple, error);
		goto exit;
	}


	if (rest_proxy_call_get_status_code (call) != 200) {
		g_simple_async_result_set_error (
			simple, G_IO_ERROR, G_IO_ERROR_FAILED,
			_("Expected status 200 when requesting your "
			"identity, instead got status %d (%s)"),
			rest_proxy_call_get_status_code (call),
			rest_proxy_call_get_status_message (call));
		goto exit;
	}

	json_parser = json_parser_new ();
	json_parser_load_from_data (
		json_parser,
		rest_proxy_call_get_payload (call),
		rest_proxy_call_get_payload_length (call),
		&local_error);

	if (local_error != NULL) {
		g_prefix_error (
			&local_error,
			_("Error parsing response as JSON: "));
		g_simple_async_result_take_error (simple, local_error);
		g_object_unref (json_parser);
		goto exit;
	}

	json_node = json_parser_get_root (json_parser);
	json_object = json_node_get_object (json_node);
	json_string = json_object_get_string_member (json_object, "id");
	id = g_strdup (json_string);

	json_object = json_object_get_object_member (json_object, "emails");
	json_string = json_object_get_string_member (json_object, "account");
	email = g_strdup (json_string);

	if (id == NULL) {
		g_simple_async_result_set_error (
			simple, G_IO_ERROR, G_IO_ERROR_FAILED,
			_("Didn't find 'id' in JSON data"));
		g_free (email);
	} else if (email == NULL) {
		g_simple_async_result_set_error (
			simple, G_IO_ERROR, G_IO_ERROR_FAILED,
			_("Didn't find 'emails.account' in JSON data"));
	} else {
		async_context->user_identity = id;
		async_context->email_address = email;
		async_context->imap_user_name = g_strdup (email);
		async_context->smtp_user_name = g_strdup (email);
	}

	g_object_unref (json_parser);

exit:
	g_simple_async_result_complete (simple);

	g_object_unref (simple);
}
