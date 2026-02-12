_packetize_common_section (GstMpegtsSection * section, gsize length)
{
  guint8 *data;

  section->section_length = length;
  data = section->data = g_malloc (length);


  *data++ = section->table_id;


  switch (section->section_type) {
    case GST_MPEGTS_SECTION_PAT:
    case GST_MPEGTS_SECTION_PMT:
    case GST_MPEGTS_SECTION_CAT:
    case GST_MPEGTS_SECTION_TSDT:


      GST_WRITE_UINT16_BE (data, (section->section_length - 3) | 0x3000);
      break;
    default:
      GST_WRITE_UINT16_BE (data, (section->section_length - 3) | 0x7000);
  }


  if (section->short_section)
    return;


  *data |= 0x80;
  data += 2;


  GST_WRITE_UINT16_BE (data, section->subtable_extension);
  data += 2;


  *data++ = 0xC0 |
      ((section->version_number & 0x1F) << 1) |
      (section->current_next_indicator & 0x01);


  *data++ = section->section_number;

  *data++ = section->last_section_number;
}
