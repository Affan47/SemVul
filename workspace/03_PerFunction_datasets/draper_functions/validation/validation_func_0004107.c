mxf_metadata_source_clip_resolve (MXFMetadataBase * m, GHashTable * metadata)
{
  MXFMetadataSourceClip *self = MXF_METADATA_SOURCE_CLIP (m);
  MXFMetadataBase *current = NULL;
  GHashTableIter iter;
#ifndef GST_DISABLE_GST_DEBUG
  gchar str[96];
#endif

  g_hash_table_iter_init (&iter, metadata);

  while (g_hash_table_iter_next (&iter, NULL, (gpointer) & current)) {
    if (MXF_IS_METADATA_SOURCE_PACKAGE (current)) {
      MXFMetadataGenericPackage *p = MXF_METADATA_GENERIC_PACKAGE (current);

      if (mxf_umid_is_equal (&p->package_uid, &self->source_package_id)) {
        self->source_package = MXF_METADATA_SOURCE_PACKAGE (current);
        break;
      }
    }
  }

  if (!self->source_package) {
    GST_ERROR ("Couldn't find source package %s",
        mxf_umid_to_string (&self->source_package_id, str));
  }

  return
      MXF_METADATA_BASE_CLASS (mxf_metadata_source_clip_parent_class)->resolve
      (m, metadata);
}
