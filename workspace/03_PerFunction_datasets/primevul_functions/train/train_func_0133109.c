gst_mpegts_section_packetize (GstMpegtsSection * section, gsize * output_size)
{
  guint8 *crc;
  g_return_val_if_fail (section != NULL, NULL);
  g_return_val_if_fail (output_size != NULL, NULL);
  g_return_val_if_fail (section->packetizer != NULL, NULL);


  if (section->data) {
    *output_size = section->section_length;
    return section->data;
  }

  if (!section->packetizer (section))
    return NULL;

  if (!section->short_section) {

    crc = section->data + section->section_length - 4;
    GST_WRITE_UINT32_BE (crc, _calc_crc32 (section->data, crc - section->data));
  }

  *output_size = section->section_length;

  return section->data;
}
