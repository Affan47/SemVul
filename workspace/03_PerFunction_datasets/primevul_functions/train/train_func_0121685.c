h264_video_type_find (GstTypeFind * tf, gpointer unused)
{
  DataScanCtx c = { 0, NULL, 0 };


  gboolean seen_idr = FALSE;
  gboolean seen_sps = FALSE;
  gboolean seen_pps = FALSE;
  gboolean seen_ssps = FALSE;
  int nut, ref;
  int good = 0;
  int bad = 0;

  while (c.offset < H264_MAX_PROBE_LENGTH) {
    if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 4)))
      break;

    if (IS_MPEG_HEADER (c.data)) {
      nut = c.data[3] & 0x9f;
      ref = c.data[3] & 0x60;


      if (nut > 0x1f) {
        bad++;
        break;
      }


      if ((nut >= 1 && nut <= 13) || nut == 19) {
        if ((nut == 5 && ref == 0) ||
            ((nut == 6 || (nut >= 9 && nut <= 12)) && ref != 0)) {
          bad++;
        } else {
          if (nut == 7)
            seen_sps = TRUE;
          else if (nut == 8)
            seen_pps = TRUE;
          else if (nut == 5)
            seen_idr = TRUE;

          good++;
        }
      } else if (nut >= 14 && nut <= 33) {
        if (nut == 15) {
          seen_ssps = TRUE;
          good++;
        } else if (nut == 14 || nut == 20) {


          if (seen_ssps)
            good++;
        } else {


          bad++;
        }
      } else {


      }

      GST_LOG ("good:%d, bad:%d, pps:%d, sps:%d, idr:%d ssps:%d", good, bad,
          seen_pps, seen_sps, seen_idr, seen_ssps);

      if (seen_sps && seen_pps && seen_idr && good >= 10 && bad < 4) {
        gst_type_find_suggest (tf, GST_TYPE_FIND_LIKELY, H264_VIDEO_CAPS);
        return;
      }

      data_scan_ctx_advance (tf, &c, 4);
    }
    data_scan_ctx_advance (tf, &c, 1);
  }

  GST_LOG ("good:%d, bad:%d, pps:%d, sps:%d, idr:%d ssps=%d", good, bad,
      seen_pps, seen_sps, seen_idr, seen_ssps);

  if (good >= 2 && bad == 0) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_POSSIBLE, H264_VIDEO_CAPS);
  }
}
