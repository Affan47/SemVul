dynamic_lookup_handle (TpHandleRepoIface *irepo,
    const char *id,
    gpointer context,
    GError **error)
{
  TpDynamicHandleRepo *self = TP_DYNAMIC_HANDLE_REPO (irepo);
  TpHandle handle;
  gchar *normal_id = NULL;

  if (context == NULL)
    context = self->default_normalize_context;

  if (self->normalize_function)
    {
      normal_id = (self->normalize_function) (irepo, id, context, error);
      if (normal_id == NULL)
        return 0;
      id = normal_id;
    }

  handle = GPOINTER_TO_UINT (g_hash_table_lookup (self->string_to_handle, id));

  if (handle == 0)
    {
      g_set_error (error, TP_ERROR, TP_ERROR_NOT_AVAILABLE,
          "no %s handle (type %u) currently exists for ID \"%s\"",
          tp_handle_type_to_string (self->handle_type),
          self->handle_type, id);
    }

  g_free (normal_id);
  return handle;
}
