gst_qtdemux_activate_segment (GstQTDemux * qtdemux, QtDemuxStream * stream,
    guint32 seg_idx, GstClockTime offset)
{
  QtDemuxSegment *segment;
  guint32 index, kf_index;
  GstClockTime start = 0, stop = GST_CLOCK_TIME_NONE;

  GST_LOG_OBJECT (stream->pad, "activate segment %d, offset %" GST_TIME_FORMAT,
      seg_idx, GST_TIME_ARGS (offset));

  if (!gst_qtdemux_stream_update_segment (qtdemux, stream, seg_idx, offset,
          &start, &stop))
    return FALSE;

  segment = &stream->segments[stream->segment_index];


  if (qtdemux->fragmented) {
    stream->to_sample = G_MAXUINT32;
    return TRUE;
  }


  if (!qtdemux->pullbased)
    return TRUE;


  if (G_LIKELY (!QTSEGMENT_IS_EMPTY (segment))) {
    if (qtdemux->segment.rate >= 0) {
      index = gst_qtdemux_find_index_linear (qtdemux, stream, start);
      stream->to_sample = G_MAXUINT32;
      GST_DEBUG_OBJECT (stream->pad,
          "moving data pointer to %" GST_TIME_FORMAT ", index: %u, pts %"
          GST_TIME_FORMAT, GST_TIME_ARGS (start), index,
          GST_TIME_ARGS (QTSAMPLE_PTS (stream, &stream->samples[index])));
    } else {
      index = gst_qtdemux_find_index_linear (qtdemux, stream, stop);
      stream->to_sample = index;
      GST_DEBUG_OBJECT (stream->pad,
          "moving data pointer to %" GST_TIME_FORMAT ", index: %u, pts %"
          GST_TIME_FORMAT, GST_TIME_ARGS (stop), index,
          GST_TIME_ARGS (QTSAMPLE_PTS (stream, &stream->samples[index])));
    }
  } else {
    GST_DEBUG_OBJECT (stream->pad, "No need to look for keyframe, "
        "this is an empty segment");
    return TRUE;
  }


  if (index == -1)
    return FALSE;


  if (index == stream->sample_index) {
    GST_DEBUG_OBJECT (stream->pad, "we are at the right index");
    return TRUE;
  }


  kf_index = gst_qtdemux_find_keyframe (qtdemux, stream, index);


  if (index > stream->sample_index) {

    if (kf_index > stream->sample_index) {
      GST_DEBUG_OBJECT (stream->pad,
           "moving forwards to keyframe at %u (pts %" GST_TIME_FORMAT " dts %"GST_TIME_FORMAT" )", kf_index,
           GST_TIME_ARGS (QTSAMPLE_PTS(stream, &stream->samples[kf_index])),
           GST_TIME_ARGS (QTSAMPLE_DTS(stream, &stream->samples[kf_index])));
      gst_qtdemux_move_stream (qtdemux, stream, kf_index);
    } else {
      GST_DEBUG_OBJECT (stream->pad,
          "moving forwards, keyframe at %u (pts %" GST_TIME_FORMAT " dts %"GST_TIME_FORMAT" ) already sent", kf_index,
          GST_TIME_ARGS (QTSAMPLE_PTS (stream, &stream->samples[kf_index])),
          GST_TIME_ARGS (QTSAMPLE_DTS (stream, &stream->samples[kf_index])));
    }
  } else {
    GST_DEBUG_OBJECT (stream->pad,
        "moving backwards to keyframe at %u (pts %" GST_TIME_FORMAT " dts %"GST_TIME_FORMAT" )", kf_index,
        GST_TIME_ARGS (QTSAMPLE_PTS(stream, &stream->samples[kf_index])),
        GST_TIME_ARGS (QTSAMPLE_DTS(stream, &stream->samples[kf_index])));
    gst_qtdemux_move_stream (qtdemux, stream, kf_index);
  }


  return TRUE;
}
