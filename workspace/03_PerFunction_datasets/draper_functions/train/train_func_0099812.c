gcr_system_prompt_close_finish (GcrSystemPrompt *self,
                                GAsyncResult *result,
                                GError **error)
{
	g_return_val_if_fail (GCR_IS_SYSTEM_PROMPT (self), FALSE);
	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	g_return_val_if_fail (g_simple_async_result_is_valid (result, NULL,
	                      gcr_system_prompt_close_async), FALSE);

	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result), error))
		return FALSE;

	return TRUE;
}
