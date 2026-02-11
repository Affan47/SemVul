gst_base_sink_do_preroll (GstBaseSink * sink, GstMiniObject * obj)
{
  GstFlowReturn ret;

  while (G_UNLIKELY (sink->need_preroll)) {
    GST_DEBUG_OBJECT (sink, "prerolling object %p", obj);


    if (sink->priv->call_preroll) {
      GstBaseSinkClass *bclass;
      GstBuffer *buf;

      if (GST_IS_BUFFER_LIST (obj)) {
        buf = gst_buffer_list_get (GST_BUFFER_LIST_CAST (obj), 0);
        g_assert (NULL != buf);
      } else if (GST_IS_BUFFER (obj)) {
        buf = GST_BUFFER_CAST (obj);

        gst_base_sink_set_last_buffer (sink, buf);
      } else
        buf = NULL;

      if (buf) {
        GST_DEBUG_OBJECT (sink, "preroll buffer %" GST_TIME_FORMAT,
            GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));

        bclass = GST_BASE_SINK_GET_CLASS (sink);

        if (bclass->prepare)
          if ((ret = bclass->prepare (sink, buf)) != GST_FLOW_OK)
            goto prepare_canceled;

        if (bclass->preroll)
          if ((ret = bclass->preroll (sink, buf)) != GST_FLOW_OK)
            goto preroll_canceled;

        sink->priv->call_preroll = FALSE;
      }
    }


    if (G_LIKELY (sink->playing_async)) {
      if (G_UNLIKELY (!gst_base_sink_commit_state (sink)))
        goto stopping;
    }


    if (G_LIKELY (sink->need_preroll)) {

      ret = gst_base_sink_wait_preroll (sink);
      if ((ret != GST_FLOW_OK) && (ret != GST_FLOW_STEP))
        goto preroll_failed;
    }
  }
  return GST_FLOW_OK;


prepare_canceled:
  {
    GST_DEBUG_OBJECT (sink, "prepare failed, abort state");
    gst_element_abort_state (GST_ELEMENT_CAST (sink));
    return ret;
  }
preroll_canceled:
  {
    GST_DEBUG_OBJECT (sink, "preroll failed, abort state");
    gst_element_abort_state (GST_ELEMENT_CAST (sink));
    return ret;
  }
stopping:
  {
    GST_DEBUG_OBJECT (sink, "stopping while commiting state");
    return GST_FLOW_FLUSHING;
  }
preroll_failed:
  {
    GST_DEBUG_OBJECT (sink, "preroll failed: %s", gst_flow_get_name (ret));
    return ret;
  }
}
