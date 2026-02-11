e_ews_connection_create_items (EEwsConnection *cnc,
                               gint pri,
                               const gchar *msg_disposition,
                               const gchar *send_invites,
                               const EwsFolderId *fid,
                               EEwsRequestCreationCallback create_cb,
                               gpointer create_user_data,
                               GCancellable *cancellable,
                               GAsyncReadyCallback callback,
                               gpointer user_data)
{
	ESoapMessage *msg;
	GSimpleAsyncResult *simple;
	EwsAsyncData *async_data;

	g_return_if_fail (cnc != NULL);

	msg = e_ews_message_new_with_header (
			cnc->priv->uri,
			cnc->priv->impersonate_user,
			"CreateItem",
			NULL,
			NULL,
			cnc->priv->version,
			E_EWS_EXCHANGE_2007_SP1,
			FALSE);

	if (msg_disposition)
		e_soap_message_add_attribute (
			msg, "MessageDisposition",
			msg_disposition, NULL, NULL);
	if (send_invites)
		e_soap_message_add_attribute (
			msg, "SendMeetingInvitations",
			send_invites, NULL, NULL);

	if (fid) {
		e_soap_message_start_element (msg, "SavedItemFolderId", "messages", NULL);
		ews_append_folder_id_to_msg (msg, cnc->priv->email, fid);
		e_soap_message_end_element (msg);
	}

	e_soap_message_start_element (msg, "Items", "messages", NULL);

	create_cb (msg, create_user_data);

	e_soap_message_end_element (msg);

	e_ews_message_write_footer (msg);

	simple = g_simple_async_result_new (
		G_OBJECT (cnc), callback, user_data,
		e_ews_connection_create_items);

	async_data = g_new0 (EwsAsyncData, 1);
	g_simple_async_result_set_op_res_gpointer (
		simple, async_data, (GDestroyNotify) async_data_free);

	e_ews_connection_queue_request (
		cnc, msg, get_items_response_cb,
		pri, cancellable, simple);

	g_object_unref (simple);
}
