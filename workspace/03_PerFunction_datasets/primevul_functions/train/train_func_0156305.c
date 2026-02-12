gst_qtdemux_advance_sample (GstQTDemux * qtdemux, QtDemuxStream * stream)
{
  QtDemuxSample *sample;
  QtDemuxSegment *segment;


  segment = &stream->segments[stream->segment_index];

  if (G_UNLIKELY (QTSEGMENT_IS_EMPTY (segment))) {
    GST_DEBUG_OBJECT (qtdemux, "Empty segment, no samples to advance");
    goto next_segment;
  }

  if (G_UNLIKELY (stream->sample_index >= stream->to_sample)) {

    GST_DEBUG_OBJECT (qtdemux,
        "reached max allowed sample %u, mark EOS", stream->to_sample);
    stream->time_position = GST_CLOCK_TIME_NONE;
    return;
  }


  stream->sample_index++;
  stream->offset_in_sample = 0;


  if (G_UNLIKELY (stream->sample_index >= stream->n_samples))
    goto next_segment;

  if (!qtdemux_parse_samples (qtdemux, stream, stream->sample_index)) {
    GST_LOG_OBJECT (qtdemux, "Parsing of index %u failed!",
        stream->sample_index);
    return;
  }


  sample = &stream->samples[stream->sample_index];


  if (G_UNLIKELY (QTSAMPLE_DTS (stream, sample) >= segment->media_stop))
    goto next_segment;

  if (QTSAMPLE_DTS (stream, sample) >= segment->media_start) {


    stream->time_position =
        QTSAMPLE_DTS (stream, sample) - segment->media_start + segment->time;
  } else {


    stream->time_position = segment->time;
  }
  return;


next_segment:
  {
    GST_DEBUG_OBJECT (qtdemux, "segment %d ended ", stream->segment_index);

    if (stream->segment_index == stream->n_segments - 1) {

      stream->time_position = GST_CLOCK_TIME_NONE;
    } else {

      stream->time_position = segment->stop_time;
    }


    if (GST_CLOCK_TIME_IS_VALID (stream->segment.stop))
      stream->accumulated_base +=
          (stream->segment.stop -
          stream->segment.start) / ABS (stream->segment.rate);

    stream->segment_index = -1;
  }
}
