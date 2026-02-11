legacyresample_query (GstPad * pad, GstQuery * query)
{
  GstLegacyresample *legacyresample =
      GST_LEGACYRESAMPLE (gst_pad_get_parent (pad));
  GstBaseTransform *trans = GST_BASE_TRANSFORM (legacyresample);
  gboolean res = TRUE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_LATENCY:
    {
      GstClockTime min, max;
      gboolean live;
      guint64 latency;
      GstPad *peer;
      gint rate = legacyresample->i_rate;
      gint resampler_latency = legacyresample->filter_length / 2;

      if (gst_base_transform_is_passthrough (trans))
        resampler_latency = 0;

      if ((peer = gst_pad_get_peer (trans->sinkpad))) {
        if ((res = gst_pad_query (peer, query))) {
          gst_query_parse_latency (query, &live, &min, &max);

          GST_DEBUG ("Peer latency: min %"
              GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
              GST_TIME_ARGS (min), GST_TIME_ARGS (max));


          if (rate != 0 && resampler_latency != 0)
            latency =
                gst_util_uint64_scale (resampler_latency, GST_SECOND, rate);
          else
            latency = 0;

          GST_DEBUG ("Our latency: %" GST_TIME_FORMAT, GST_TIME_ARGS (latency));

          min += latency;
          if (max != GST_CLOCK_TIME_NONE)
            max += latency;

          GST_DEBUG ("Calculated total latency : min %"
              GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
              GST_TIME_ARGS (min), GST_TIME_ARGS (max));

          gst_query_set_latency (query, live, min, max);
        }
        gst_object_unref (peer);
      }
      break;
    }
    default:
      res = gst_pad_query_default (pad, query);
      break;
  }
  gst_object_unref (legacyresample);
  return res;
}
