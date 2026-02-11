mail_signature_script_dialog_commit_cb (GObject *object,
                                        GAsyncResult *result,
                                        gpointer user_data)
{
	GSimpleAsyncResult *simple;
	AsyncContext *async_context;
	GError *error = NULL;

	simple = G_SIMPLE_ASYNC_RESULT (user_data);
	async_context = g_simple_async_result_get_op_res_gpointer (simple);

	e_source_registry_commit_source_finish (
		E_SOURCE_REGISTRY (object), result, &error);

	if (error != NULL) {
		g_simple_async_result_take_error (simple, error);
		g_simple_async_result_complete (simple);
		g_object_unref (simple);
		return;
	}


	e_source_mail_signature_symlink (
		async_context->source,
		async_context->symlink_target,
		G_PRIORITY_DEFAULT,
		async_context->cancellable,
		mail_signature_script_dialog_symlink_cb,
		simple);
}
