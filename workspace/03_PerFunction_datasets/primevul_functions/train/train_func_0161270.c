gst_mpegts_section_new (guint16 pid, guint8 * data, gsize data_size)
{
  GstMpegtsSection *res = NULL;
  guint8 tmp;
  guint8 table_id;
  guint16 section_length = 0;


  if (G_UNLIKELY (data_size < 3))
    goto short_packet;


  section_length = GST_READ_UINT16_BE (data + 1) & 0x0FFF;
  if (G_UNLIKELY (data_size < section_length + 3))
    goto short_packet;

  GST_LOG ("data_size:%" G_GSIZE_FORMAT " section_length:%u",
      data_size, section_length);


  table_id = *data;

  res = _gst_mpegts_section_init (pid, table_id);

  res->data = data;

  data++;


  res->short_section = (*data & 0x80) == 0x00;

  res->section_length = section_length + 3;
  if (!res->short_section) {


    if (G_UNLIKELY (data_size < 11))
      goto bad_long_packet;


    res->crc = GST_READ_UINT32_BE (res->data + res->section_length - 4);

    data += 2;

    res->subtable_extension = GST_READ_UINT16_BE (data);
    data += 2;


    tmp = *data++;
    res->version_number = tmp >> 1 & 0x1f;
    res->current_next_indicator = tmp & 0x01;

    res->section_number = *data++;

    res->last_section_number = *data;
  }

  return res;

short_packet:
  {
    GST_WARNING
        ("PID 0x%04x section extends past provided data (got:%" G_GSIZE_FORMAT
        ", need:%d)", pid, data_size, section_length + 3);
    g_free (data);
    return NULL;
  }
bad_long_packet:
  {
    GST_WARNING ("PID 0x%04x long section is too short (%" G_GSIZE_FORMAT
        " bytes, need at least 11)", pid, data_size);
    gst_mpegts_section_unref (res);
    return NULL;
  }
}
