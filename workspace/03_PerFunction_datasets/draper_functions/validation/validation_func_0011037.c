parse_mpsub (ParserState * state, const gchar * line)
{
  gchar *ret;
  float t1, t2;

  switch (state->state) {
    case 0:

      if (sscanf (line, "%f %f", &t1, &t2) == 2) {
        state->state = 1;
        state->start_time += state->duration + GST_SECOND * t1;
        state->duration = GST_SECOND * t2;
      }
      return NULL;
    case 1:
    {
      guint64 clip_start = 0, clip_stop = 0;
      gboolean in_seg = FALSE;


      in_seg = gst_segment_clip (state->segment, GST_FORMAT_TIME,
          state->start_time, state->start_time + state->duration,
          &clip_start, &clip_stop);

      if (in_seg) {
        state->start_time = clip_start;
        state->duration = clip_stop - clip_start;
      } else {
        state->state = 0;
        return NULL;
      }
    }


      if (state->buf->len)
        g_string_append_c (state->buf, '\n');
      g_string_append (state->buf, line);
      if (strlen (line) == 0) {
        ret = g_strdup (state->buf->str);
        g_string_truncate (state->buf, 0);
        state->state = 0;
        return ret;
      }
      return NULL;
    default:
      g_assert_not_reached ();
      return NULL;
  }
}
