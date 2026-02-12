aac_type_find (GstTypeFind * tf, gpointer unused)
{
  DataScanCtx c = { 0, NULL, 0 };
  GstTypeFindProbability best_probability = GST_TYPE_FIND_NONE;
  GstCaps *best_caps = NULL;
  guint best_count = 0;

  while (c.offset < AAC_AMOUNT) {
    guint snc, len, offset, i;


    if (G_UNLIKELY (!data_scan_ctx_ensure_data (tf, &c, 6)))
      break;

    snc = GST_READ_UINT16_BE (c.data);
    if (G_UNLIKELY ((snc & 0xfff6) == 0xfff0)) {

      GST_DEBUG ("Found one ADTS syncpoint at offset 0x%" G_GINT64_MODIFIER
          "x, tracing next...", c.offset);
      len = ((c.data[3] & 0x03) << 11) |
          (c.data[4] << 3) | ((c.data[5] & 0xe0) >> 5);

      if (len == 0 || !data_scan_ctx_ensure_data (tf, &c, len + 6)) {
        GST_DEBUG ("Wrong sync or next frame not within reach, len=%u", len);
        goto next;
      }

      offset = len;

      snc = GST_READ_UINT16_BE (c.data + offset);
      if ((snc & 0xfff6) == 0xfff0) {
        GstCaps *caps;
        guint mpegversion, sample_freq_idx, channel_config, profile_idx, rate;
        guint8 audio_config[2];

        mpegversion = (c.data[1] & 0x08) ? 2 : 4;
        profile_idx = c.data[2] >> 6;
        sample_freq_idx = ((c.data[2] & 0x3c) >> 2);
        channel_config = ((c.data[2] & 0x01) << 2) + (c.data[3] >> 6);

        GST_DEBUG ("Found second ADTS-%d syncpoint at offset 0x%"
            G_GINT64_MODIFIER "x, framelen %u", mpegversion, c.offset, len);


        if (sample_freq_idx > 0xc) {
          GST_DEBUG ("Unexpected sample frequency index %d or wrong sync",
              sample_freq_idx);
          goto next;
        }

        rate = gst_codec_utils_aac_get_sample_rate_from_index (sample_freq_idx);
        GST_LOG ("ADTS: profile=%u, rate=%u", profile_idx, rate);


        audio_config[0] = (profile_idx + 1) << 3;
        audio_config[0] |= (sample_freq_idx >> 1) & 0x7;
        audio_config[1] = (sample_freq_idx & 0x1) << 7;
        audio_config[1] |= (channel_config & 0xf) << 3;

        caps = gst_caps_new_simple ("audio/mpeg",
            "framed", G_TYPE_BOOLEAN, FALSE,
            "mpegversion", G_TYPE_INT, mpegversion,
            "stream-format", G_TYPE_STRING, "adts", NULL);

        gst_codec_utils_aac_caps_set_level_and_profile (caps, audio_config, 2);


        if (channel_config != 0 && channel_config <= 7) {
          const guint channels_map[] = { 0, 1, 2, 3, 4, 5, 6, 8 };

          gst_caps_set_simple (caps, "channels", G_TYPE_INT,
              channels_map[channel_config], "rate", G_TYPE_INT, rate, NULL);
        }


        len = ((c.data[offset + 3] & 0x03) << 11) |
            (c.data[offset + 4] << 3) | ((c.data[offset + 5] & 0xe0) >> 5);

        if (len == 0 || !data_scan_ctx_ensure_data (tf, &c, offset + len + 6)) {
          GST_DEBUG ("Wrong sync or next frame not within reach, len=%u", len);
          gst_type_find_suggest (tf, GST_TYPE_FIND_LIKELY, caps);
        } else {
          offset += len;


          for (i = 3; i <= 6; i++) {
            len = ((c.data[offset + 3] & 0x03) << 11) |
                (c.data[offset + 4] << 3) | ((c.data[offset + 5] & 0xe0) >> 5);
            if (len == 0
                || !data_scan_ctx_ensure_data (tf, &c, offset + len + 6)) {
              GST_DEBUG ("Wrong sync or next frame not within reach, len=%u",
                  len);
              break;
            }
            snc = GST_READ_UINT16_BE (c.data + offset);
            if ((snc & 0xfff6) == 0xfff0) {
              GST_DEBUG ("Find %und Sync..probability is %u ", i,
                  GST_TYPE_FIND_LIKELY + 5 * (i - 2));
              offset += len;
            } else {
              break;
            }
          }
          gst_type_find_suggest (tf, GST_TYPE_FIND_LIKELY + 5 * (i - 3), caps);

        }
        gst_caps_unref (caps);
        break;
      }

      GST_DEBUG ("No next frame found... (should have been at 0x%x)", len);
    } else if (G_UNLIKELY ((snc & 0xffe0) == 0x56e0 || snc == 0x4de1)) {
      gint count;


      GST_INFO ("Possible LOAS syncword at offset 0x%" G_GINT64_MODIFIER
          "x, scanning for more frames...", c.offset);

      if (snc == 0x4de1)
        count = aac_type_find_scan_loas_frames_ep (tf, &c, 20);
      else
        count = aac_type_find_scan_loas_frames (tf, &c, 20);

      if (count >= 3 && count > best_count) {
        gst_caps_replace (&best_caps, NULL);
        best_caps = gst_caps_new_simple ("audio/mpeg",
            "framed", G_TYPE_BOOLEAN, FALSE,
            "mpegversion", G_TYPE_INT, 4,
            "stream-format", G_TYPE_STRING, "loas", NULL);
        best_count = count;
        best_probability = GST_TYPE_FIND_POSSIBLE - 10 + count * 3;
        if (best_probability >= GST_TYPE_FIND_LIKELY)
          break;
      }
    } else if (!memcmp (c.data, "ADIF", 4)) {

      gst_type_find_suggest_simple (tf, GST_TYPE_FIND_LIKELY, "audio/mpeg",
          "framed", G_TYPE_BOOLEAN, FALSE, "mpegversion", G_TYPE_INT, 4,
          "stream-format", G_TYPE_STRING, "adif", NULL);
      break;
    }

  next:

    data_scan_ctx_advance (tf, &c, 1);
  }

  if (best_probability > GST_TYPE_FIND_NONE) {
    gst_type_find_suggest (tf, best_probability, best_caps);
    gst_caps_unref (best_caps);
  }
}
