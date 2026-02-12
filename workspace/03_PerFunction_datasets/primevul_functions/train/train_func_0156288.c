gst_qtdemux_stream_seek_fragment (GstQTDemux * qtdemux, QtDemuxStream * stream,
    GstClockTime pos, gboolean after)
{
  QtDemuxRandomAccessEntry *entries = stream->ra_entries;
  guint n_entries = stream->n_ra_entries;
  guint i;


  for (i = 0; i < n_entries; ++i) {
    if (entries[i].ts > pos)
      break;
  }


  if (i == 0)
    return &entries[0];

  if (after)
    return &entries[i];
  else
    return &entries[i - 1];
}
