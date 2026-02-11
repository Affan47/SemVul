gst_sdp_demux_create_stream (GstSDPDemux * demux, GstSDPMessage * sdp, gint idx)
{
  GstSDPStream *stream;
  const gchar *payload;
  const GstSDPMedia *media;
  const GstSDPConnection *conn;


  media = gst_sdp_message_get_media (sdp, idx);
  if (media == NULL)
    return NULL;

  stream = g_new0 (GstSDPStream, 1);
  stream->parent = demux;


  stream->last_ret = GST_FLOW_OK;
  stream->added = FALSE;
  stream->disabled = FALSE;
  stream->id = demux->numstreams++;
  stream->eos = FALSE;


  if ((payload = gst_sdp_media_get_format (media, 0))) {
    stream->pt = atoi (payload);

    stream->caps = gst_sdp_demux_media_to_caps (stream->pt, media);

    if (stream->pt >= 96) {


      if (find_stream (demux, GINT_TO_POINTER (stream->pt),
              (gpointer) find_stream_by_pt)) {
        stream->container = TRUE;
      }
    }
  }
  if (!(conn = gst_sdp_media_get_connection (media, 0))) {
    if (!(conn = gst_sdp_message_get_connection (sdp)))
      goto no_connection;
  }

  if (!conn->address)
    goto no_connection;

  stream->destination = conn->address;
  stream->ttl = conn->ttl;
  stream->multicast = is_multicast_address (stream->destination);

  stream->rtp_port = gst_sdp_media_get_port (media);
  if (gst_sdp_media_get_attribute_val (media, "rtcp")) {

    stream->rtcp_port = stream->rtp_port + 1;
  } else {
    stream->rtcp_port = stream->rtp_port + 1;
  }

  GST_DEBUG_OBJECT (demux, "stream %d, (%p)", stream->id, stream);
  GST_DEBUG_OBJECT (demux, " pt: %d", stream->pt);
  GST_DEBUG_OBJECT (demux, " container: %d", stream->container);
  GST_DEBUG_OBJECT (demux, " caps: %" GST_PTR_FORMAT, stream->caps);


  demux->streams = g_list_append (demux->streams, stream);

  return stream;


no_connection:
  {
    gst_sdp_demux_stream_free (demux, stream);
    return NULL;
  }
}
