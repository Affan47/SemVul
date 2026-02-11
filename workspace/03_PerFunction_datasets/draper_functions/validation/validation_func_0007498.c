attachment_save_check_for_error (SaveContext *save_context,
                                 GError *error)
{
	GSimpleAsyncResult *simple;

	if (error == NULL)
		return FALSE;

	simple = save_context->simple;
	g_simple_async_result_take_error (simple, error);
	g_simple_async_result_complete (simple);

	attachment_save_context_free (save_context);

	return TRUE;
}
