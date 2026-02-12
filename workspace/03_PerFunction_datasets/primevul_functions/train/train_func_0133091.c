_packetize_pmt (GstMpegtsSection * section)
{
  const GstMpegtsPMT *pmt;
  GstMpegtsPMTStream *stream;
  GstMpegtsDescriptor *descriptor;
  gsize length, pgm_info_length, stream_length;
  guint8 *data;
  guint i, j;

  pmt = gst_mpegts_section_get_pmt (section);

  if (pmt == NULL)
    return FALSE;


  length = 16;


  pgm_info_length = 0;
  if (pmt->descriptors) {
    for (i = 0; i < pmt->descriptors->len; i++) {
      descriptor = g_ptr_array_index (pmt->descriptors, i);
      pgm_info_length += descriptor->length + 2;
    }
  }


  stream_length = 0;
  if (pmt->streams) {
    for (i = 0; i < pmt->streams->len; i++) {
      stream = g_ptr_array_index (pmt->streams, i);


      stream_length += 5;

      if (stream->descriptors) {
        for (j = 0; j < stream->descriptors->len; j++) {
          descriptor = g_ptr_array_index (stream->descriptors, j);
          stream_length += descriptor->length + 2;
        }
      }
    }
  }

  length += pgm_info_length + stream_length;

  _packetize_common_section (section, length);
  data = section->data + 8;


  GST_WRITE_UINT16_BE (data, pmt->pcr_pid | 0xE000);
  data += 2;


  GST_WRITE_UINT16_BE (data, pgm_info_length | 0xF000);
  data += 2;

  _packetize_descriptor_array (pmt->descriptors, &data);

  if (pmt->streams) {
    guint8 *pos;

    for (i = 0; i < pmt->streams->len; i++) {
      stream = g_ptr_array_index (pmt->streams, i);

      *data++ = stream->stream_type;


      GST_WRITE_UINT16_BE (data, stream->pid | 0xE000);
      data += 2;


      pos = data;
      data += 2;
      _packetize_descriptor_array (stream->descriptors, &data);


      GST_WRITE_UINT16_BE (pos, (data - pos - 2) | 0xF000);
    }
  }

  return TRUE;
}
