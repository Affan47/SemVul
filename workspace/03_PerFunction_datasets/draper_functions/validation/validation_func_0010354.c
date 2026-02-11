mxf_metadata_track_resolve (MXFMetadataBase * m, GHashTable * metadata)
{
  MXFMetadataTrack *self = MXF_METADATA_TRACK (m);
  MXFMetadataBase *current = NULL;
  guint i;
#ifndef GST_DISABLE_GST_DEBUG
  gchar str[48];
#endif

  current = g_hash_table_lookup (metadata, &self->sequence_uid);
  if (current && MXF_IS_METADATA_SEQUENCE (current)) {
    if (mxf_metadata_base_resolve (current, metadata)) {
      self->sequence = MXF_METADATA_SEQUENCE (current);
    } else {
      GST_ERROR ("Couldn't resolve sequence %s",
          mxf_uuid_to_string (&self->sequence_uid, str));
      return FALSE;
    }
  } else {
    GST_ERROR ("Couldn't find sequence %s",
        mxf_uuid_to_string (&self->sequence_uid, str));
    return FALSE;
  }

  self->type =
      mxf_metadata_track_identifier_parse (&self->sequence->data_definition);
  if (self->type == MXF_METADATA_TRACK_UNKNOWN) {
    MXFMetadataSequence *sequence = self->sequence;

    for (i = 0; i < sequence->n_structural_components; i++) {
      MXFMetadataStructuralComponent *component =
          sequence->structural_components[i];

      if (!component)
        continue;

      self->type =
          mxf_metadata_track_identifier_parse (&component->data_definition);
      if (self->type != MXF_METADATA_TRACK_UNKNOWN)
        break;
    }
  }

  return MXF_METADATA_BASE_CLASS (mxf_metadata_track_parent_class)->resolve (m,
      metadata);
}
