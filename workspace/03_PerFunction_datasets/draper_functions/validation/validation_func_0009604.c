tpl_log_manager_search_finish (TplLogManager *self,
    GAsyncResult *result,
    GList **hits,
    GError **error)
{
  GSimpleAsyncResult *simple;

  g_return_val_if_fail (TPL_IS_LOG_MANAGER (self), FALSE);
  g_return_val_if_fail (G_IS_SIMPLE_ASYNC_RESULT (result), FALSE);
  g_return_val_if_fail (g_simple_async_result_is_valid (result,
        G_OBJECT (self), tpl_log_manager_search_async), FALSE);

  simple = G_SIMPLE_ASYNC_RESULT (result);

  if (g_simple_async_result_propagate_error (simple, error))
    return FALSE;

  if (hits != NULL)
    *hits = _take_list (g_simple_async_result_get_op_res_gpointer (simple));
  return TRUE;
}
