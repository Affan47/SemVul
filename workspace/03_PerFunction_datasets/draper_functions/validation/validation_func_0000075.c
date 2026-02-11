pk_client_search_groups_async (PkClient *client, PkBitfield filters, gchar **values, GCancellable *cancellable,
			      PkProgressCallback progress_callback, gpointer progress_user_data,
			      GAsyncReadyCallback callback_ready, gpointer user_data)
{
	GSimpleAsyncResult *res;
	PkClientState *state;
	GError *error = NULL;

	g_return_if_fail (PK_IS_CLIENT (client));
	g_return_if_fail (callback_ready != NULL);
	g_return_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable));

	res = g_simple_async_result_new (G_OBJECT (client), callback_ready, user_data, pk_client_search_groups_async);


	state = g_slice_new0 (PkClientState);
	state->role = PK_ROLE_ENUM_SEARCH_GROUP;
	state->res = g_object_ref (res);
	state->client = g_object_ref (client);
	state->cancellable = g_cancellable_new ();
	if (cancellable != NULL) {
		state->cancellable_client = g_object_ref (cancellable);
		state->cancellable_id = g_cancellable_connect (cancellable,
							       G_CALLBACK (pk_client_cancellable_cancel_cb),
							       state,
							       NULL);
	}
	state->filters = filters;
	state->search = g_strdupv (values);
	state->progress_callback = progress_callback;
	state->progress_user_data = progress_user_data;
	state->progress = pk_progress_new ();


	if (cancellable != NULL &&
	    g_cancellable_set_error_if_cancelled (cancellable, &error)) {
		pk_client_state_finish (state, error);
		g_error_free (error);
		goto out;
	}


	pk_client_set_role (state, state->role);


	pk_control_get_tid_async (client->priv->control,
				  cancellable,
				  (GAsyncReadyCallback) pk_client_get_tid_cb,
				  state);
out:
	g_object_unref (res);
}
