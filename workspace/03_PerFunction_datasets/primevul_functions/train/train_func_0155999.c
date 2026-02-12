gst_aac_parse_check_adts_frame (GstAacParse * aacparse,
    const guint8 * data, const guint avail, gboolean drain,
    guint * framesize, guint * needed_data)
{
  guint crc_size;

  *needed_data = 0;


  if (G_UNLIKELY (avail < 3)) {
    *needed_data = 3;
    return FALSE;
  }


  if ((data[0] == 0xff) && ((data[1] & 0xf6) == 0xf0)) {


    if (G_UNLIKELY ((data[2] & 0x3C) >> 2 == 15))
      return FALSE;


    if (G_UNLIKELY (avail < 6)) {
      *needed_data = 6;
      return FALSE;
    }

    *framesize = gst_aac_parse_adts_get_frame_len (data);


    crc_size = (data[1] & 0x01) ? 0 : 2;


    if (*framesize < 7 + crc_size) {
      *needed_data = 7 + crc_size;
      return FALSE;
    }


    if (drain || !GST_BASE_PARSE_LOST_SYNC (aacparse)) {
      return TRUE;
    }

    if (*framesize + ADTS_MAX_SIZE > avail) {


      GST_DEBUG ("NEED MORE DATA: we need %d, available %d",
          *framesize + ADTS_MAX_SIZE, avail);
      *needed_data = *framesize + ADTS_MAX_SIZE;
      gst_base_parse_set_min_frame_size (GST_BASE_PARSE (aacparse),
          *framesize + ADTS_MAX_SIZE);
      return FALSE;
    }

    if ((data[*framesize] == 0xff) && ((data[*framesize + 1] & 0xf6) == 0xf0)) {
      guint nextlen = gst_aac_parse_adts_get_frame_len (data + (*framesize));

      GST_LOG ("ADTS frame found, len: %d bytes", *framesize);
      gst_base_parse_set_min_frame_size (GST_BASE_PARSE (aacparse),
          nextlen + ADTS_MAX_SIZE);
      return TRUE;
    }
  }
  return FALSE;
}
