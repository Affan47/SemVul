gst_query_parse_latency (GstQuery * query, gboolean * live,
    GstClockTime * min_latency, GstClockTime * max_latency)
{
  GstStructure *structure;

  g_return_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_LATENCY);

  structure = query->structure;
  if (live)
    *live =
        g_value_get_boolean (gst_structure_id_get_value (structure,
            GST_QUARK (LIVE)));
  if (min_latency)
    *min_latency = g_value_get_uint64 (gst_structure_id_get_value (structure,
            GST_QUARK (MIN_LATENCY)));
  if (max_latency)
    *max_latency = g_value_get_uint64 (gst_structure_id_get_value (structure,
            GST_QUARK (MAX_LATENCY)));
}
