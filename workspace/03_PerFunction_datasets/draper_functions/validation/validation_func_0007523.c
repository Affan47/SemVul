e_ews_connection_get_folder_info (EEwsConnection *cnc,
                                  gint pri,
                                  const gchar *mail_id,
                                  const EwsFolderId *folder_id,
                                  GCancellable *cancellable,
                                  GAsyncReadyCallback callback,
                                  gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;

	g_return_if_fail (cnc != NULL);
	g_return_if_fail (folder_id != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"GetFolder",
			NULL,
			NULL,
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE);

	e_soap_message_start_element (msg, "FolderShape", "messages", NULL);
	e_ews_message_write_string_parameter (msg, "BaseShape", NULL, "Default");
	e_soap_message_start_element (msg, "AdditionalProperties", NULL, NULL);
	e_ews_message_write_string_parameter_with_attribute (msg, "FieldURI", NULL, NULL, "FieldURI", "folder:FolderClass");
	e_ews_message_write_string_parameter_with_attribute (msg, "FieldURI", NULL, NULL, "FieldURI", "folder:ParentFolderId");
	e_soap_message_end_element (msg);
	e_soap_message_end_element (msg);

	e_soap_message_start_element (msg, "FolderIds", "messages", NULL);
	ews_append_folder_id_to_msg (msg, mail_id, folder_id);
	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_get_folder_info);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, get_folder_info_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}
