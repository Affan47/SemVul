flac_type_find (GstTypeFind * tf, gpointer unused)
{
  DataScanCtx c = { 0, NULL, 0 };

  if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 4)))
    return;


  if (memcmp (c.data, "fLaC", 4) == 0) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, FLAC_CAPS);
    return;
  }

  if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 6)))
    return;


  if (memcmp (c.data, "\177FLAC\001", 6) == 0) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_MAXIMUM, FLAC_CAPS);
    return;
  }


#if 0


  while (c.offset < (64 * 1024)) {
    if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 4)))
      break;


    if (c.data[0] == 0xff && (c.data[1] >> 2) == 0x3e) {

      if (((c.data[1] >> 1) & 0x01) == 0x01)
        goto advance;


      if ((c.data[2] >> 4) == 0x00)
        goto advance;


      if ((c.data[2] & 0x0f) == 0x0f)
        goto advance;


      if ((c.data[2] & 0x0f) == 0x00)
        goto advance;


      if ((c.data[3] >> 4) >= 11)
        goto advance;


      if (((c.data[3] >> 1) & 0x07) == 0x07)
        goto advance;
      if (((c.data[3] >> 1) & 0x07) == 0x05)
        goto advance;


      if (((c.data[3] >> 1) & 0x07) == 0x00)
        goto advance;


      if ((c.data[3] & 0x01) == 0x01)
        goto advance;


      GST_DEBUG ("Found flac without headers at %d", (gint) c.offset);
      gst_type_find_suggest (tf, GST_TYPE_FIND_POSSIBLE, FLAC_CAPS);
      return;
    }
  advance:
    data_scan_ctx_advance (tf, &c, 1);
  }
#endif
}
