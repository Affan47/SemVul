gst_matroska_parse_flac_stream_headers (gpointer codec_data,
    gsize codec_data_size)
{
  GstBufferList *list = NULL;
  GstBuffer *hdr;
  guint8 *pdata = codec_data;
  guint len, off;

  GST_MEMDUMP ("flac codec data", codec_data, codec_data_size);


  if (codec_data == NULL || codec_data_size < ((4) + (4 + 34))) {
    GST_WARNING ("not enough codec priv data for flac headers");
    return NULL;
  }

  if (memcmp (pdata, "fLaC", 4) != 0) {
    GST_WARNING ("no flac marker at start of stream headers");
    return NULL;
  }

  list = gst_buffer_list_new ();

  hdr = gst_buffer_new_wrapped (g_memdup (pdata, 4), 4);
  gst_buffer_list_add (list, hdr);


  off = 4;


  while (off < codec_data_size) {
    len = GST_READ_UINT8 (pdata + off + 1) << 16;
    len |= GST_READ_UINT8 (pdata + off + 2) << 8;
    len |= GST_READ_UINT8 (pdata + off + 3);

    GST_DEBUG ("header packet: len=%u bytes, flags=0x%02x", len, pdata[off]);


    hdr = gst_buffer_new_wrapped (g_memdup (pdata + off, len + 4), len + 4);
    gst_buffer_list_add (list, hdr);

    off += 4 + len;
  }
  return list;
}
