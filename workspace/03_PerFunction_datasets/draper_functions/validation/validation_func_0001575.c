mxf_metadata_dm_source_clip_handle_tag (MXFMetadataBase * metadata,
    MXFPrimerPack * primer, guint16 tag, const guint8 * tag_data,
    guint tag_size)
{
  MXFMetadataDMSourceClip *self = MXF_METADATA_DM_SOURCE_CLIP (metadata);
  gboolean ret = TRUE;

  switch (tag) {
    case 0x6103:
    {
      guint32 len;
      guint i;

      if (tag_size < 8)
        goto error;

      len = GST_READ_UINT32_BE (tag_data);
      GST_DEBUG ("  number of track ids = %u", len);
      if (len == 0)
        return TRUE;

      if (GST_READ_UINT32_BE (tag_data + 4) != 4)
        goto error;

      if (tag_size < 8 + 4 * len)
        goto error;

      tag_data += 8;
      tag_size -= 8;

      self->n_track_ids = len;
      self->track_ids = g_new0 (guint32, len);

      for (i = 0; i < len; i++) {
        self->track_ids[i] = GST_READ_UINT32_BE (tag_data);
        GST_DEBUG ("    track id %u = %u", i, self->track_ids[i]);
        tag_data += 4;
        tag_size -= 4;
      }
      break;
    }
    default:
      ret =
          MXF_METADATA_BASE_CLASS
          (mxf_metadata_dm_source_clip_parent_class)->handle_tag (metadata,
          primer, tag, tag_data, tag_size);
      break;
  }

  return ret;

error:

  GST_ERROR ("Invalid DM source clip local tag 0x%04x of size %u", tag,
      tag_size);

  return FALSE;
}
