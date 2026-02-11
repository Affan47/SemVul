photos_source_manager_refresh_accounts (PhotosSourceManager *self)
{
  PhotosSourceManagerPrivate *priv = self->priv;
  GList *accounts;
  GList *l;

  accounts = goa_client_get_accounts (priv->client);
  for (l = accounts; l != NULL; l = l->next)
    {
      GoaObject *object = GOA_OBJECT (l->data);
      PhotosSource *source;

      if (goa_object_peek_account (object) == NULL)
        continue;

      if (goa_object_peek_photos (object) == NULL)
        continue;

      source = photos_source_new_from_goa_object (GOA_OBJECT (l->data));
      photos_base_manager_add_object (PHOTOS_BASE_MANAGER (self), G_OBJECT (source));
      g_object_unref (source);
    }

  g_list_free_full (accounts, g_object_unref);
}
