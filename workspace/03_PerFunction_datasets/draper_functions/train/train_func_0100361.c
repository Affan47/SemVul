infc_request_manager_dispose(GObject* object)
{
  InfcRequestManager* request_manager;
  InfcRequestManagerPrivate* priv;

  request_manager = INFC_REQUEST_MANAGER(object);
  priv = INFC_REQUEST_MANAGER_PRIVATE(request_manager);

  g_hash_table_destroy(priv->requests);
  priv->requests = NULL;

  if(parent_class->dispose != NULL)
    parent_class->dispose(object);
}
