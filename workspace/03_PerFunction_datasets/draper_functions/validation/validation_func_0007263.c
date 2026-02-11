mail_auth_run_in_thread_func (GSimpleAsyncResult *res, GObject *object, GCancellable *cancellable)
{
  GError *error;
  gboolean op_res;

  op_res = FALSE;

  error = NULL;
  if (!goa_mail_auth_run_sync (GOA_MAIL_AUTH (object), cancellable, &error))
    {
      g_simple_async_result_take_error (res, error);
      goto out;
    }

  op_res = TRUE;

 out:
  g_simple_async_result_set_op_res_gboolean (res, op_res);
}
