gst_rtp_ssrc_demux_rtcp_sink_event (GstPad * pad, GstEvent * event)
{
  GstRtpSsrcDemux *demux;
  gboolean res = FALSE;

  demux = GST_RTP_SSRC_DEMUX (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_NEWSEGMENT:
    default:
    {
      GSList *walk;
      GSList *pads = NULL;

      res = TRUE;
      GST_PAD_LOCK (demux);
      for (walk = demux->srcpads; walk; walk = g_slist_next (walk)) {
        GstRtpSsrcDemuxPad *pad = (GstRtpSsrcDemuxPad *) walk->data;

        pads = g_slist_prepend (pads, gst_object_ref (pad->rtcp_pad));
      }
      GST_PAD_UNLOCK (demux);
      for (walk = pads; walk; walk = g_slist_next (walk)) {
        GstPad *pad = (GstPad *) walk->data;

        gst_event_ref (event);
        res &= gst_pad_push_event (pad, event);
        gst_object_unref (pad);
      }
      g_slist_free (pads);
      gst_event_unref (event);
      break;
    }
  }
  gst_object_unref (demux);
  return res;
}
