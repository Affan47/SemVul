on_temporary_account_created_for_identity (GoaIdentityService *self,
                                           GAsyncResult       *result,
                                           GoaIdentity        *identity)
{
  GoaObject   *object;
  const char  *principal;
  GError      *error;

  principal = goa_identity_get_identifier (identity);
  g_hash_table_remove (self->priv->pending_temporary_account_results,
                       principal);

  error = NULL;
  if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (result), &error))
    {
      const char *identifier;

      identifier = goa_identity_get_identifier (identity);
      goa_debug ("Could not add temporary account for identity %s: %s",
                 identifier,
                 error->message);
      g_error_free (error);
      return;
    }

  object = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));

  if (object != NULL)
    ensure_account_credentials (self, object);
}
