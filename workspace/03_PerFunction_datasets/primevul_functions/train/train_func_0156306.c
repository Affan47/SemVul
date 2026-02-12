gst_qtdemux_loop_state_movie (GstQTDemux * qtdemux)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstBuffer *buf = NULL;
  QtDemuxStream *stream;
  GstClockTime min_time;
  guint64 offset = 0;
  GstClockTime dts = GST_CLOCK_TIME_NONE;
  GstClockTime pts = GST_CLOCK_TIME_NONE;
  GstClockTime duration = 0;
  gboolean keyframe = FALSE;
  guint sample_size = 0;
  gboolean empty = 0;
  guint size;
  gint index;
  gint i;

  gst_qtdemux_push_pending_newsegment (qtdemux);

  if (qtdemux->fragmented_seek_pending) {
    GST_INFO_OBJECT (qtdemux, "pending fragmented seek");
    gst_qtdemux_do_fragmented_seek (qtdemux);
    GST_INFO_OBJECT (qtdemux, "fragmented seek done!");
    qtdemux->fragmented_seek_pending = FALSE;
  }


  min_time = G_MAXUINT64;
  index = -1;
  for (i = 0; i < qtdemux->n_streams; i++) {
    GstClockTime position;

    stream = qtdemux->streams[i];
    position = stream->time_position;


    if (position != GST_CLOCK_TIME_NONE && position < min_time) {
      min_time = position;
      index = i;
    }
  }

  if (G_UNLIKELY (index == -1)) {
    GST_DEBUG_OBJECT (qtdemux, "all streams are EOS");
    goto eos;
  }


  if (G_UNLIKELY (qtdemux->segment.stop != -1
          && ((qtdemux->segment.rate >= 0 && qtdemux->segment.stop <= min_time)
              || (qtdemux->segment.rate < 0
                  && qtdemux->segment.start > min_time))
          && qtdemux->streams[index]->on_keyframe)) {
    GST_DEBUG_OBJECT (qtdemux, "we reached the end of our segment.");
    qtdemux->streams[index]->time_position = GST_CLOCK_TIME_NONE;
    goto eos_stream;
  }


  for (i = 0; i < qtdemux->n_streams; i++) {
    stream = qtdemux->streams[i];
    if (stream->pad && (stream->subtype == FOURCC_subp
            || stream->subtype == FOURCC_text
            || stream->subtype == FOURCC_sbtl)) {


      while (GST_CLOCK_TIME_IS_VALID (stream->segment.stop) &&
          GST_CLOCK_TIME_IS_VALID (stream->segment.position) &&
          stream->segment.position + GST_SECOND < min_time) {
        GstEvent *gap =
            gst_event_new_gap (stream->segment.position, GST_SECOND);
        gst_pad_push_event (stream->pad, gap);
        stream->segment.position += GST_SECOND;
      }
    }
  }

  stream = qtdemux->streams[index];
  if (stream->new_caps) {
    gst_qtdemux_configure_stream (qtdemux, stream);
    qtdemux_do_allocation (qtdemux, stream);
  }


  if (G_UNLIKELY (!gst_qtdemux_prepare_current_sample (qtdemux, stream, &empty,
              &offset, &sample_size, &dts, &pts, &duration, &keyframe)))
    goto eos_stream;


  if (G_UNLIKELY (qtdemux->
          segment.flags & GST_SEGMENT_FLAG_TRICKMODE_KEY_UNITS)) {
    if (stream->subtype == FOURCC_vide && !keyframe) {
      GST_LOG_OBJECT (qtdemux, "Skipping non-keyframe on stream %d", index);
      goto next;
    }
  }

  GST_DEBUG_OBJECT (qtdemux,
      "pushing from stream %d, empty %d offset %" G_GUINT64_FORMAT
      ", size %d, dts=%" GST_TIME_FORMAT ", pts=%" GST_TIME_FORMAT
      ", duration %" GST_TIME_FORMAT, index, empty, offset, sample_size,
      GST_TIME_ARGS (dts), GST_TIME_ARGS (pts), GST_TIME_ARGS (duration));

  if (G_UNLIKELY (empty)) {

    gst_pad_push_event (stream->pad, gst_event_new_gap (pts, duration));
    stream->segment.position = pts + duration;
    goto next;
  }


  if (G_UNLIKELY (sample_size <= 0))
    goto next;


  if (G_UNLIKELY (GST_PAD_LAST_FLOW_RETURN (stream->pad) == GST_FLOW_EOS))
    goto next;

  if (stream->max_buffer_size == 0 || sample_size <= stream->max_buffer_size) {
    size = sample_size;
  } else {
    GST_DEBUG_OBJECT (qtdemux,
        "size %d larger than stream max_buffer_size %d, trimming",
        sample_size, stream->max_buffer_size);
    size =
        MIN (sample_size - stream->offset_in_sample, stream->max_buffer_size);
  }

  if (qtdemux->cenc_aux_info_offset > 0) {
    GstMapInfo map;
    GstByteReader br;
    GstBuffer *aux_info = NULL;


    ret =
        gst_qtdemux_pull_atom (qtdemux, qtdemux->offset,
        offset + stream->offset_in_sample - qtdemux->offset, &aux_info);
    if (G_UNLIKELY (ret != GST_FLOW_OK))
      goto beach;
    gst_buffer_map (aux_info, &map, GST_MAP_READ);
    GST_DEBUG_OBJECT (qtdemux, "parsing cenc auxiliary info");
    gst_byte_reader_init (&br, map.data + 8, map.size);
    if (!qtdemux_parse_cenc_aux_info (qtdemux, stream, &br,
            qtdemux->cenc_aux_info_sizes, qtdemux->cenc_aux_sample_count)) {
      GST_ERROR_OBJECT (qtdemux, "failed to parse cenc auxiliary info");
      gst_buffer_unmap (aux_info, &map);
      gst_buffer_unref (aux_info);
      ret = GST_FLOW_ERROR;
      goto beach;
    }
    gst_buffer_unmap (aux_info, &map);
    gst_buffer_unref (aux_info);
  }

  GST_LOG_OBJECT (qtdemux, "reading %d bytes @ %" G_GUINT64_FORMAT, size,
      offset);

  if (stream->use_allocator) {

    buf = gst_buffer_new_allocate (stream->allocator, size, &stream->params);
  }

  ret = gst_qtdemux_pull_atom (qtdemux, offset + stream->offset_in_sample,
      size, &buf);
  if (G_UNLIKELY (ret != GST_FLOW_OK))
    goto beach;

  if (size != sample_size) {
    pts += gst_util_uint64_scale_int (GST_SECOND,
        stream->offset_in_sample / stream->bytes_per_frame, stream->timescale);
    dts += gst_util_uint64_scale_int (GST_SECOND,
        stream->offset_in_sample / stream->bytes_per_frame, stream->timescale);
    duration = gst_util_uint64_scale_int (GST_SECOND,
        size / stream->bytes_per_frame, stream->timescale);
  }

  ret = gst_qtdemux_decorate_and_push_buffer (qtdemux, stream, buf,
      dts, pts, duration, keyframe, min_time, offset);

  if (size != sample_size) {
    QtDemuxSample *sample = &stream->samples[stream->sample_index];
    QtDemuxSegment *segment = &stream->segments[stream->segment_index];

    GstClockTime time_position = QTSTREAMTIME_TO_GSTTIME (stream,
        sample->timestamp + stream->offset_in_sample / stream->bytes_per_frame);
    if (time_position >= segment->media_start) {


      stream->time_position = (time_position - segment->media_start) +
          segment->time;
    } else {


      stream->time_position = segment->time;
    }
  }


  ret = gst_qtdemux_combine_flows (qtdemux, stream, ret);


  if (ret == GST_FLOW_EOS)
    ret = GST_FLOW_OK;

  stream->offset_in_sample += size;
  if (stream->offset_in_sample >= sample_size) {
    gst_qtdemux_advance_sample (qtdemux, stream);
  }
  goto beach;

next:
  gst_qtdemux_advance_sample (qtdemux, stream);

beach:
  return ret;


eos:
  {
    GST_DEBUG_OBJECT (qtdemux, "No samples left for any streams - EOS");
    ret = GST_FLOW_EOS;
    goto beach;
  }
eos_stream:
  {
    GST_DEBUG_OBJECT (qtdemux, "No samples left for stream");

    ret = GST_FLOW_OK;
    goto beach;
  }
}
