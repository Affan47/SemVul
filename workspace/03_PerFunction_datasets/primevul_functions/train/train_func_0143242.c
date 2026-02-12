gst_matroska_demux_handle_sink_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  gboolean res = TRUE;
  GstMatroskaDemux *demux = GST_MATROSKA_DEMUX (parent);

  GST_DEBUG_OBJECT (demux,
      "have event type %s: %p on sink pad", GST_EVENT_TYPE_NAME (event), event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEGMENT:
    {
      const GstSegment *segment;


      gst_event_parse_segment (event, &segment);

      GST_DEBUG_OBJECT (demux,
          "received format %d segment %" GST_SEGMENT_FORMAT, segment->format,
          segment);

      if (demux->common.state < GST_MATROSKA_READ_STATE_DATA) {
        GST_DEBUG_OBJECT (demux, "still starting");
        goto exit;
      }


      if (segment->format != GST_FORMAT_BYTES) {
        GST_DEBUG_OBJECT (demux, "unsupported segment format, ignoring");
        goto exit;
      }

      GST_DEBUG_OBJECT (demux, "clearing segment state");
      GST_OBJECT_LOCK (demux);

      gst_adapter_clear (demux->common.adapter);

      demux->common.offset = segment->start;

      if (GST_CLOCK_TIME_IS_VALID (demux->common.segment.position))
        demux->common.segment.base +=
            (MAX (demux->common.segment.position, demux->stream_start_time)
            - demux->stream_start_time) / fabs (demux->common.segment.rate);


      demux->common.segment.position = GST_CLOCK_TIME_NONE;
      demux->cluster_time = GST_CLOCK_TIME_NONE;
      demux->cluster_offset = 0;
      demux->cluster_prevsize = 0;
      demux->need_segment = TRUE;
      demux->segment_seqnum = gst_event_get_seqnum (event);

      demux->common.segment.rate = segment->rate;
      demux->common.segment.flags = segment->flags;

      if (demux->seek_offset == segment->start) {
        GST_DEBUG_OBJECT (demux, "position matches requested seek");
        demux->common.segment.position = demux->requested_seek_time;
      } else {
        GST_DEBUG_OBJECT (demux, "unexpected segment position");
      }
      demux->requested_seek_time = GST_CLOCK_TIME_NONE;
      demux->seek_offset = -1;
      GST_OBJECT_UNLOCK (demux);
    exit:


      GST_DEBUG_OBJECT (demux, "eating event");
      gst_event_unref (event);
      res = TRUE;
      break;
    }
    case GST_EVENT_EOS:
    {
      if (demux->common.state != GST_MATROSKA_READ_STATE_DATA
          && demux->common.state != GST_MATROSKA_READ_STATE_SCANNING) {
        gst_event_unref (event);
        GST_ELEMENT_ERROR (demux, STREAM, DEMUX,
            (NULL), ("got eos and didn't receive a complete header object"));
      } else if (demux->common.num_streams == 0) {
        GST_ELEMENT_ERROR (demux, STREAM, DEMUX,
            (NULL), ("got eos but no streams (yet)"));
      } else {
        gst_matroska_demux_send_event (demux, event);
      }
      break;
    }
    case GST_EVENT_FLUSH_STOP:
    {
      guint64 dur;

      gst_adapter_clear (demux->common.adapter);
      GST_OBJECT_LOCK (demux);
      gst_matroska_read_common_reset_streams (&demux->common,
          GST_CLOCK_TIME_NONE, TRUE);
      gst_flow_combiner_reset (demux->flowcombiner);
      dur = demux->common.segment.duration;
      gst_segment_init (&demux->common.segment, GST_FORMAT_TIME);
      demux->common.segment.duration = dur;
      demux->cluster_time = GST_CLOCK_TIME_NONE;
      demux->cluster_offset = 0;
      demux->cluster_prevsize = 0;
      GST_OBJECT_UNLOCK (demux);

    }
    default:
      res = gst_pad_event_default (pad, parent, event);
      break;
  }

  return res;
}
