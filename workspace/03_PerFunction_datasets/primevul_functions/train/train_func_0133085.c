_parse_cat (GstMpegtsSection * section)
{
  guint8 *data;
  guint desc_len;


  data = section->data + 8;


  desc_len = section->section_length - 4 - 8;
  return (gpointer) gst_mpegts_parse_descriptors (data, desc_len);
}
