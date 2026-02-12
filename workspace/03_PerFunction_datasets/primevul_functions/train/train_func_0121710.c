h265_video_type_find (GstTypeFind * tf, gpointer unused)
{
  DataScanCtx c = { 0, NULL, 0 };


  gboolean seen_irap = FALSE;
  gboolean seen_vps = FALSE;
  gboolean seen_sps = FALSE;
  gboolean seen_pps = FALSE;
  int nut;
  int good = 0;
  int bad = 0;

  while (c.offset < H265_MAX_PROBE_LENGTH) {
    if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 5)))
      break;

    if (IS_MPEG_HEADER (c.data)) {

      nut = c.data[3] & 0xfe;


      if (nut > 0x7e) {
        bad++;
        break;
      }
      nut = nut >> 1;


      if ((c.data[3] & 0x01) || (c.data[4] & 0xf8) || !(c.data[4] & 0x07)) {
        bad++;
        break;
      }


      if ((nut >= 0 && nut <= 9) || (nut >= 16 && nut <= 21) || (nut >= 32
              && nut <= 40)) {
        if (nut == 32)
          seen_vps = TRUE;
        else if (nut == 33)
          seen_sps = TRUE;
        else if (nut == 34)
          seen_pps = TRUE;
        else if (nut >= 16 && nut <= 21) {


          seen_irap = TRUE;
        }

        good++;
      } else if ((nut >= 10 && nut <= 15) || (nut >= 22 && nut <= 31)
          || (nut >= 41 && nut <= 47)) {

        bad++;
      } else {


      }

      GST_LOG ("good:%d, bad:%d, pps:%d, sps:%d, vps:%d, irap:%d", good, bad,
          seen_pps, seen_sps, seen_vps, seen_irap);

      if (seen_sps && seen_pps && seen_irap && good >= 10 && bad < 4) {
        gst_type_find_suggest (tf, GST_TYPE_FIND_LIKELY, H265_VIDEO_CAPS);
        return;
      }

      data_scan_ctx_advance (tf, &c, 5);
    }
    data_scan_ctx_advance (tf, &c, 1);
  }

  GST_LOG ("good:%d, bad:%d, pps:%d, sps:%d, vps:%d, irap:%d", good, bad,
      seen_pps, seen_sps, seen_vps, seen_irap);

  if (good >= 2 && bad == 0) {
    gst_type_find_suggest (tf, GST_TYPE_FIND_POSSIBLE, H265_VIDEO_CAPS);
  }
}
