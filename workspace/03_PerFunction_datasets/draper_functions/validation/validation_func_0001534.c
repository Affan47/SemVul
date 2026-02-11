mp3parse_bytepos_to_time (GstMPEGAudioParse * mp3parse,
    gint64 bytepos, GstClockTime * ts, gboolean from_total_time)
{
  gint64 total_bytes;
  GstClockTime total_time;

  if (bytepos == -1) {
    *ts = GST_CLOCK_TIME_NONE;
    return TRUE;
  }

  if (bytepos == 0) {
    *ts = 0;
    return TRUE;
  }


  if (!from_total_time && (mp3parse->xing_flags & XING_TOC_FLAG) &&
      (total_bytes = mp3parse->xing_bytes) &&
      (total_time = mp3parse->xing_total_time)) {
    gdouble fa, fb, fx;
    gdouble pos;
    gint index;

    pos = CLAMP ((bytepos * 256.0) / total_bytes, 0.0, 256.0);
    index = CLAMP (pos, 0, 255);
    fa = mp3parse->xing_seek_table_inverse[index];
    if (index < 255)
      fb = mp3parse->xing_seek_table_inverse[index + 1];
    else
      fb = 10000.0;

    fx = fa + (fb - fa) * (pos - index);

    *ts = (1.0 / 10000.0) * fx * gst_util_guint64_to_gdouble (total_time);

    return TRUE;
  }

  if (!from_total_time && mp3parse->vbri_seek_table &&
      (total_bytes = mp3parse->vbri_bytes) &&
      (total_time = mp3parse->vbri_total_time)) {
    gint i = 0;
    guint64 sum = 0;
    gdouble a, b, fa, fb;

    do {
      sum += mp3parse->vbri_seek_table[i];
      i++;
    } while (i + 1 < mp3parse->vbri_seek_points
        && sum + mp3parse->vbri_seek_table[i] < bytepos);
    i--;

    a = gst_guint64_to_gdouble (sum);
    fa = gst_guint64_to_gdouble (gst_util_uint64_scale (i, total_time,
            mp3parse->vbri_seek_points));

    if (i + 1 < mp3parse->vbri_seek_points) {
      b = a + mp3parse->vbri_seek_table[i + 1];
      fb = gst_guint64_to_gdouble (gst_util_uint64_scale (i + 1, total_time,
              mp3parse->vbri_seek_points));
    } else {
      b = total_bytes;
      fb = gst_guint64_to_gdouble (total_time);
    }

    *ts = gst_gdouble_to_guint64 (fa + ((fb - fa) / (b - a)) * (bytepos - a));

    return TRUE;
  }


  if (mp3parse->avg_bitrate == 0)
    return FALSE;

  *ts = (GstClockTime) gst_util_uint64_scale (GST_SECOND, bytepos * 8,
      mp3parse->avg_bitrate);
  return TRUE;
}
