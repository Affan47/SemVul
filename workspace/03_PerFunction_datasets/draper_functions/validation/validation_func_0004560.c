mxf_metadata_timecode_component_handle_tag (MXFMetadataBase * metadata,
    MXFPrimerPack * primer, guint16 tag, const guint8 * tag_data,
    guint tag_size)
{
  MXFMetadataTimecodeComponent *self =
      MXF_METADATA_TIMECODE_COMPONENT (metadata);
  gboolean ret = TRUE;

  switch (tag) {
    case 0x1502:
      if (tag_size != 2)
        goto error;
      self->rounded_timecode_base = GST_READ_UINT16_BE (tag_data);
      GST_DEBUG ("  rounded timecode base = %u", self->rounded_timecode_base);
      break;
    case 0x1501:
      if (tag_size != 8)
        goto error;
      self->start_timecode = GST_READ_UINT64_BE (tag_data);
      GST_DEBUG ("  start timecode = %" G_GINT64_FORMAT, self->start_timecode);
      break;
    case 0x1503:
      if (tag_size != 1)
        goto error;
      self->drop_frame = (GST_READ_UINT8 (tag_data) != 0);
      GST_DEBUG ("  drop frame = %s", (self->drop_frame) ? "yes" : "no");
      break;
    default:
      ret =
          MXF_METADATA_BASE_CLASS
          (mxf_metadata_timecode_component_parent_class)->handle_tag (metadata,
          primer, tag, tag_data, tag_size);
      break;
  }

  return ret;

error:

  GST_ERROR ("Invalid timecode component local tag 0x%04x of size %u", tag,
      tag_size);

  return FALSE;
}
