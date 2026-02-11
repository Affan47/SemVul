gst_stream_splitter_sink_getcaps (GstPad * pad)
{
  GstStreamSplitter *stream_splitter =
      (GstStreamSplitter *) GST_PAD_PARENT (pad);
  guint32 cookie;
  GList *tmp;
  GstCaps *res = NULL;


  STREAMS_LOCK (stream_splitter);

resync:
  if (G_UNLIKELY (stream_splitter->srcpads == NULL)) {
    res = gst_caps_new_any ();
    goto beach;
  }

  res = NULL;
  cookie = stream_splitter->cookie;
  tmp = stream_splitter->srcpads;

  while (tmp) {
    GstPad *srcpad = (GstPad *) tmp->data;

    STREAMS_UNLOCK (stream_splitter);
    if (res) {
      GstCaps *peercaps = gst_pad_peer_get_caps_reffed (srcpad);
      if (peercaps)
        gst_caps_merge (res, gst_caps_make_writable (peercaps));
    } else {
      res = gst_pad_peer_get_caps (srcpad);
    }
    STREAMS_LOCK (stream_splitter);

    if (G_UNLIKELY (cookie != stream_splitter->cookie)) {
      if (res)
        gst_caps_unref (res);
      goto resync;
    }
    tmp = tmp->next;
  }

beach:
  STREAMS_UNLOCK (stream_splitter);
  return res;
}
