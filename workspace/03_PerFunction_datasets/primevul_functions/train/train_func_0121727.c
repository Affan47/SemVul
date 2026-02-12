mpeg_ts_type_find (GstTypeFind * tf, gpointer unused)
{


  const gint pack_sizes[] = { 188, 192, 204, 208 };
  const guint8 *data = NULL;
  guint size = 0;
  guint64 skipped = 0;

  while (skipped < GST_MPEGTS_TYPEFIND_SCAN_LENGTH) {
    if (size < MPEGTS_HDR_SIZE) {
      data = gst_type_find_peek (tf, skipped, GST_MPEGTS_TYPEFIND_SYNC_SIZE);
      if (!data)
        break;
      size = GST_MPEGTS_TYPEFIND_SYNC_SIZE;
    }


    if (IS_MPEGTS_HEADER (data)) {
      gint p;

      GST_LOG ("possible mpeg-ts sync at offset %" G_GUINT64_FORMAT, skipped);

      for (p = 0; p < G_N_ELEMENTS (pack_sizes); p++) {
        gint found;


        found = mpeg_ts_probe_headers (tf, skipped, pack_sizes[p]);
        if (found >= GST_MPEGTS_TYPEFIND_MIN_HEADERS) {
          gint probability;


          probability = MIN (10 * found, GST_TYPE_FIND_MAXIMUM);

          gst_type_find_suggest_simple (tf, probability, "video/mpegts",
              "systemstream", G_TYPE_BOOLEAN, TRUE,
              "packetsize", G_TYPE_INT, pack_sizes[p], NULL);
          return;
        }
      }
    }
    data++;
    skipped++;
    size--;
  }
}
