mxf_metadata_essence_container_data_write_tags (MXFMetadataBase * m,
    MXFPrimerPack * primer)
{
  MXFMetadataEssenceContainerData *self =
      MXF_METADATA_ESSENCE_CONTAINER_DATA (m);
  GList *ret =
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_essence_container_data_parent_class)->write_tags (m,
      primer);
  MXFLocalTag *t;

  t = g_slice_new0 (MXFLocalTag);
  memcpy (&t->ul, MXF_UL (LINKED_PACKAGE_UID), 16);
  t->size = 32;
  t->data = g_slice_alloc0 (32);
  t->g_slice = TRUE;
  if (self->linked_package)
    memcpy (t->data, &self->linked_package->parent.package_uid, 32);
  mxf_primer_pack_add_mapping (primer, 0x2701, &t->ul);
  ret = g_list_prepend (ret, t);

  t = g_slice_new0 (MXFLocalTag);
  memcpy (&t->ul, MXF_UL (BODY_SID), 16);
  t->size = 4;
  t->data = g_slice_alloc (4);
  t->g_slice = TRUE;
  GST_WRITE_UINT32_BE (t->data, self->body_sid);
  mxf_primer_pack_add_mapping (primer, 0x3f07, &t->ul);
  ret = g_list_prepend (ret, t);

  if (self->index_sid) {
    t = g_slice_new0 (MXFLocalTag);
    memcpy (&t->ul, MXF_UL (INDEX_SID), 16);
    t->size = 4;
    t->data = g_slice_alloc (4);
    t->g_slice = TRUE;
    GST_WRITE_UINT32_BE (t->data, self->index_sid);
    mxf_primer_pack_add_mapping (primer, 0x3f07, &t->ul);
    ret = g_list_prepend (ret, t);
  }

  return ret;
}
