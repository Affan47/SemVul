gst_qtdemux_map_and_push_segments (GstQTDemux * qtdemux, GstSegment * segment)
{
  gint n, i;

  for (n = 0; n < qtdemux->n_streams; n++) {
    QtDemuxStream *stream = qtdemux->streams[n];

    stream->time_position = segment->start;


    for (i = 0; i < stream->n_segments; i++) {
      if (stream->segments[i].stop_time > segment->start) {
        gst_qtdemux_activate_segment (qtdemux, stream, i,
            stream->time_position);
        if (QTSEGMENT_IS_EMPTY (&stream->segments[i])) {

          gst_qtdemux_send_gap_for_segment (qtdemux, stream, i,
              stream->time_position);
          continue;
        }

        g_assert (i == stream->n_segments - 1);
      }
    }
  }
}
