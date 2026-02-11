gst_audio_visualizer_src_query (GstPad * pad, GstObject * parent,
    GstQuery * query)
{
  gboolean res = FALSE;
  GstAudioVisualizer *scope;

  scope = GST_AUDIO_VISUALIZER (parent);

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_LATENCY:
    {


      GstClockTime min_latency, max_latency;
      gboolean us_live;
      GstClockTime our_latency;
      guint max_samples;
      gint rate = GST_AUDIO_INFO_RATE (&scope->ainfo);

      if (rate == 0)
        break;

      if ((res = gst_pad_peer_query (scope->sinkpad, query))) {
        gst_query_parse_latency (query, &us_live, &min_latency, &max_latency);

        GST_DEBUG_OBJECT (scope, "Peer latency: min %"
            GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
            GST_TIME_ARGS (min_latency), GST_TIME_ARGS (max_latency));


        max_samples = MAX (scope->req_spf, scope->spf);
        our_latency = gst_util_uint64_scale_int (max_samples, GST_SECOND, rate);

        GST_DEBUG_OBJECT (scope, "Our latency: %" GST_TIME_FORMAT,
            GST_TIME_ARGS (our_latency));


        min_latency += our_latency;
        if (max_latency != -1)
          max_latency += our_latency;

        GST_DEBUG_OBJECT (scope, "Calculated total latency : min %"
            GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
            GST_TIME_ARGS (min_latency), GST_TIME_ARGS (max_latency));

        gst_query_set_latency (query, TRUE, min_latency, max_latency);
      }
      break;
    }
    default:
      res = gst_pad_query_default (pad, parent, query);
      break;
  }

  return res;
}
