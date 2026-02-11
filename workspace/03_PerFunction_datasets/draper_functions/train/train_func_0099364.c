user_prompter_prompt_invoke (EDBusUserPrompter *dbus_prompter,
                             struct _PrompterAsyncData *async_data,
                             GCancellable *cancellable,
                             GError **error)
{
	GPtrArray *captions;
	GList *list, *link;
	GError *local_error = NULL;

	g_return_val_if_fail (dbus_prompter != NULL, FALSE);
	g_return_val_if_fail (async_data != NULL, FALSE);

	list = async_data->button_captions;

	captions = g_ptr_array_new ();

	for (link = list; link != NULL; link = g_list_next (link)) {
		gchar *caption = link->data;

		g_ptr_array_add (captions, caption ? caption : (gchar *) "");
	}


	g_ptr_array_add (captions, NULL);

	e_dbus_user_prompter_call_prompt_sync (
		dbus_prompter,
		async_data->type ? async_data->type : "",
		async_data->title ? async_data->title : "",
		async_data->primary_text ? async_data->primary_text : "",
		async_data->secondary_text ? async_data->secondary_text : "",
		async_data->use_markup,
		(const gchar *const *) captions->pdata,
		&async_data->prompt_id,
		cancellable, &local_error);

	g_ptr_array_free (captions, TRUE);

	if (local_error != NULL) {
		g_dbus_error_strip_remote_error (local_error);
		g_propagate_error (error, local_error);
		return FALSE;
	}

	return TRUE;
}
