qtdemux_find_stream (GstQTDemux * qtdemux, guint32 id)
{
  QtDemuxStream *stream;
  gint i;


  if (G_UNLIKELY (!id)) {
    GST_DEBUG_OBJECT (qtdemux, "invalid track id 0");
    return NULL;
  }


  if (G_LIKELY (id <= qtdemux->n_streams)) {
    stream = qtdemux->streams[id - 1];
    if (G_LIKELY (stream->track_id == id))
      return stream;
  }


  for (i = 0; i < qtdemux->n_streams; i++) {
    stream = qtdemux->streams[i];
    if (stream->track_id == id)
      return stream;
  }
  if (qtdemux->mss_mode) {

    return qtdemux->streams[0];
  }

  return NULL;
}
