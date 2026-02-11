gst_matroska_mux_best_pad (GstMatroskaMux * mux, gboolean * popped)
{
  GSList *collected;
  GstMatroskaPad *best = NULL;

  *popped = FALSE;
  for (collected = mux->collect->data; collected;
      collected = g_slist_next (collected)) {
    GstMatroskaPad *collect_pad;

    collect_pad = (GstMatroskaPad *) collected->data;

    if (collect_pad->buffer == NULL) {
      collect_pad->buffer = gst_collect_pads_pop (mux->collect,
          (GstCollectData *) collect_pad);

      if (collect_pad->buffer != NULL) {
        GstClockTime time;

        *popped = TRUE;

        time = GST_BUFFER_TIMESTAMP (collect_pad->buffer);

        if (G_LIKELY (GST_CLOCK_TIME_IS_VALID (time))) {
          time = gst_segment_to_running_time (&collect_pad->collect.segment,
              GST_FORMAT_TIME, time);
          if (G_UNLIKELY (!GST_CLOCK_TIME_IS_VALID (time))) {
            GST_DEBUG_OBJECT (mux, "clipping buffer on pad %s outside segment",
                GST_PAD_NAME (collect_pad->collect.pad));
            gst_buffer_unref (collect_pad->buffer);
            collect_pad->buffer = NULL;
            return NULL;
          } else {
            GST_LOG_OBJECT (mux, "buffer ts %" GST_TIME_FORMAT " -> %"
                GST_TIME_FORMAT " running time",
                GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (collect_pad->buffer)),
                GST_TIME_ARGS (time));
            collect_pad->buffer =
                gst_buffer_make_metadata_writable (collect_pad->buffer);
            GST_BUFFER_TIMESTAMP (collect_pad->buffer) = time;
          }
        }
      }
    }


    if (collect_pad->buffer != NULL) {
      if (best == NULL || !GST_BUFFER_TIMESTAMP_IS_VALID (collect_pad->buffer)
          || (GST_BUFFER_TIMESTAMP_IS_VALID (best->buffer)
              && GST_BUFFER_TIMESTAMP (collect_pad->buffer) <
              GST_BUFFER_TIMESTAMP (best->buffer))) {
        best = collect_pad;
      }
    }
  }

  return best;
}
