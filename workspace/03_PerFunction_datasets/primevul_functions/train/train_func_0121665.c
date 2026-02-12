jpeg_type_find (GstTypeFind * tf, gpointer unused)
{
  GstTypeFindProbability prob = GST_TYPE_FIND_POSSIBLE;
  DataScanCtx c = { 0, NULL, 0 };
  GstCaps *caps;
  guint num_markers;

  if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 2)))
    return;

  if (c.data[0] != 0xff || c.data[1] != 0xd8)
    return;

  num_markers = 1;
  data_scan_ctx_advance (tf, &c, 2);

  caps = gst_caps_copy (JPEG_CAPS);

  while (data_scan_ctx_ensure_data (tf, &c, 4) && c.offset < (200 * 1024)) {
    guint16 len;
    guint8 marker;

    if (c.data[0] != 0xff)
      break;

    marker = c.data[1];
    if (G_UNLIKELY (marker == 0xff)) {
      data_scan_ctx_advance (tf, &c, 1);
      continue;
    }

    data_scan_ctx_advance (tf, &c, 2);


    len = GST_READ_UINT16_BE (c.data);

    GST_LOG ("possible JPEG marker 0x%02x (@0x%04x), segment length %u",
        marker, (guint) c.offset, len);

    if (!data_scan_ctx_ensure_data (tf, &c, len))
      break;

    if (marker == 0xc4 ||
        marker == 0xcc ||
        marker == 0xdb ||
        marker == 0xdd ||
        marker == 0xfe) {
      data_scan_ctx_advance (tf, &c, len);
      ++num_markers;
    } else if (marker == 0xe0 && len >= (2 + 4) &&
        data_scan_ctx_memcmp (tf, &c, 2, "JFIF", 4)) {
      GST_LOG ("found JFIF tag");
      prob = GST_TYPE_FIND_MAXIMUM;
      data_scan_ctx_advance (tf, &c, len);
      ++num_markers;

    } else if (marker == 0xe1 && len >= (2 + 4) &&
        data_scan_ctx_memcmp (tf, &c, 2, "Exif", 4)) {
      GST_LOG ("found Exif tag");
      prob = GST_TYPE_FIND_MAXIMUM;
      data_scan_ctx_advance (tf, &c, len);
      ++num_markers;

    } else if (marker >= 0xe0 && marker <= 0xef) {
      data_scan_ctx_advance (tf, &c, len);
      ++num_markers;
    } else if (JPEG_MARKER_IS_START_OF_FRAME (marker) && len >= (2 + 8)) {
      int h, w;

      h = GST_READ_UINT16_BE (c.data + 2 + 1);
      w = GST_READ_UINT16_BE (c.data + 2 + 1 + 2);
      if (h == 0 || w == 0) {
        GST_WARNING ("bad width %u and/or height %u in SOF header", w, h);
        break;
      }

      GST_LOG ("SOF at offset %" G_GUINT64_FORMAT ", num_markers=%d, "
          "WxH=%dx%d", c.offset - 2, num_markers, w, h);

      if (num_markers >= 5 || prob == GST_TYPE_FIND_MAXIMUM)
        prob = GST_TYPE_FIND_MAXIMUM;
      else
        prob = GST_TYPE_FIND_LIKELY;

      gst_caps_set_simple (caps, "width", G_TYPE_INT, w,
          "height", G_TYPE_INT, h, "sof-marker", G_TYPE_INT, marker & 0xf,
          NULL);

      break;
    } else {
      GST_WARNING ("bad length or unexpected JPEG marker 0xff 0x%02x", marker);
      break;
    }
  }

  gst_type_find_suggest (tf, prob, caps);
  gst_caps_unref (caps);
}
