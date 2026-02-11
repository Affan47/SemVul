grl_dmap_source_new (DMAPMdnsBrowserService *service)
{
  gchar *source_desc;
  gchar *source_id;

  GrlDmapSource *source;

  GRL_DEBUG ("grl_dmap_source_new");

  source_desc = g_strdup_printf (SOURCE_DESC_TEMPLATE, service->name);
  source_id = g_strdup_printf (SOURCE_ID_TEMPLATE, service->name);

  source = g_object_new (GRL_DMAP_SOURCE_TYPE,
                         "source-id",   source_id,
                         "source-name", service->name,
                         "source-desc", source_desc,
                         NULL);

  source->priv->service = service;

  g_free (source_desc);
  g_free (source_id);

  return source;
}
