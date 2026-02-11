mx_texture_cache_destroy_meta_entry (gpointer data)
{
  MxTextureCacheMetaEntry *entry = data;

  if (entry->destroy_func)
    entry->destroy_func (entry->ident);

  if (entry->texture)
    cogl_handle_unref (entry->texture);

  g_slice_free (MxTextureCacheMetaEntry, entry);
}
