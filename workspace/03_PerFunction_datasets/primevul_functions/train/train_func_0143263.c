gst_matroska_demux_parse_blockgroup_or_simpleblock (GstMatroskaDemux * demux,
    GstEbmlRead * ebml, guint64 cluster_time, guint64 cluster_offset,
    gboolean is_simpleblock)
{
  GstMatroskaTrackContext *stream = NULL;
  GstFlowReturn ret = GST_FLOW_OK;
  gboolean readblock = FALSE;
  guint32 id;
  guint64 block_duration = -1;
  gint64 block_discardpadding = 0;
  GstBuffer *buf = NULL;
  GstMapInfo map;
  gint stream_num = -1, n, laces = 0;
  guint size = 0;
  gint *lace_size = NULL;
  gint64 time = 0;
  gint flags = 0;
  gint64 referenceblock = 0;
  gint64 offset;
  GstClockTime buffer_timestamp;

  offset = gst_ebml_read_get_offset (ebml);

  while (ret == GST_FLOW_OK && gst_ebml_read_has_remaining (ebml, 1, TRUE)) {
    if (!is_simpleblock) {
      if ((ret = gst_ebml_peek_id (ebml, &id)) != GST_FLOW_OK) {
        goto data_error;
      }
    } else {
      id = GST_MATROSKA_ID_SIMPLEBLOCK;
    }

    switch (id) {


      case GST_MATROSKA_ID_SIMPLEBLOCK:
      case GST_MATROSKA_ID_BLOCK:
      {
        guint64 num;
        guint8 *data;

        if (buf) {
          gst_buffer_unmap (buf, &map);
          gst_buffer_unref (buf);
          buf = NULL;
        }
        if ((ret = gst_ebml_read_buffer (ebml, &id, &buf)) != GST_FLOW_OK)
          break;

        gst_buffer_map (buf, &map, GST_MAP_READ);
        data = map.data;
        size = map.size;


        if ((n = gst_matroska_ebmlnum_uint (data, size, &num)) < 0)
          goto data_error;
        data += n;
        size -= n;


        stream_num = gst_matroska_read_common_stream_from_num (&demux->common,
            num);
        if (G_UNLIKELY (size < 3)) {
          GST_WARNING_OBJECT (demux, "Invalid size %u", size);

          ret = GST_FLOW_OK;
          goto done;
        } else if (G_UNLIKELY (stream_num < 0 ||
                stream_num >= demux->common.num_streams)) {

          GST_WARNING_OBJECT (demux,
              "Invalid stream %d for track number %" G_GUINT64_FORMAT
              "; ignoring block", stream_num, num);
          goto done;
        }

        stream = g_ptr_array_index (demux->common.src, stream_num);


        time = ((gint16) GST_READ_UINT16_BE (data));
        data += 2;
        size -= 2;
        flags = GST_READ_UINT8 (data);
        data += 1;
        size -= 1;

        GST_LOG_OBJECT (demux, "time %" G_GUINT64_FORMAT ", flags %d", time,
            flags);

        switch ((flags & 0x06) >> 1) {
          case 0x0:
            laces = 1;
            lace_size = g_new (gint, 1);
            lace_size[0] = size;
            break;

          case 0x1:
          case 0x2:
          case 0x3:
            if (size == 0)
              goto invalid_lacing;
            laces = GST_READ_UINT8 (data) + 1;
            data += 1;
            size -= 1;
            lace_size = g_new0 (gint, laces);

            switch ((flags & 0x06) >> 1) {
              case 0x1:          {
                guint temp, total = 0;

                for (n = 0; ret == GST_FLOW_OK && n < laces - 1; n++) {
                  while (1) {
                    if (size == 0)
                      goto invalid_lacing;
                    temp = GST_READ_UINT8 (data);
                    lace_size[n] += temp;
                    data += 1;
                    size -= 1;
                    if (temp != 0xff)
                      break;
                  }
                  total += lace_size[n];
                }
                lace_size[n] = size - total;
                break;
              }

              case 0x2:
                for (n = 0; n < laces; n++)
                  lace_size[n] = size / laces;
                break;

              case 0x3:          {
                guint total;

                if ((n = gst_matroska_ebmlnum_uint (data, size, &num)) < 0)
                  goto data_error;
                data += n;
                size -= n;
                total = lace_size[0] = num;
                for (n = 1; ret == GST_FLOW_OK && n < laces - 1; n++) {
                  gint64 snum;
                  gint r;

                  if ((r = gst_matroska_ebmlnum_sint (data, size, &snum)) < 0)
                    goto data_error;
                  data += r;
                  size -= r;
                  lace_size[n] = lace_size[n - 1] + snum;
                  total += lace_size[n];
                }
                if (n < laces)
                  lace_size[n] = size - total;
                break;
              }
            }
            break;
        }

        if (ret != GST_FLOW_OK)
          break;

        readblock = TRUE;
        break;
      }

      case GST_MATROSKA_ID_BLOCKDURATION:{
        ret = gst_ebml_read_uint (ebml, &id, &block_duration);
        GST_DEBUG_OBJECT (demux, "BlockDuration: %" G_GUINT64_FORMAT,
            block_duration);
        break;
      }

      case GST_MATROSKA_ID_DISCARDPADDING:{
        ret = gst_ebml_read_sint (ebml, &id, &block_discardpadding);
        GST_DEBUG_OBJECT (demux, "DiscardPadding: %" GST_STIME_FORMAT,
            GST_STIME_ARGS (block_discardpadding));
        break;
      }

      case GST_MATROSKA_ID_REFERENCEBLOCK:{
        ret = gst_ebml_read_sint (ebml, &id, &referenceblock);
        GST_DEBUG_OBJECT (demux, "ReferenceBlock: %" G_GINT64_FORMAT,
            referenceblock);
        break;
      }

      case GST_MATROSKA_ID_CODECSTATE:{
        guint8 *data;
        guint64 data_len = 0;

        if ((ret =
                gst_ebml_read_binary (ebml, &id, &data,
                    &data_len)) != GST_FLOW_OK)
          break;

        if (G_UNLIKELY (stream == NULL)) {
          GST_WARNING_OBJECT (demux,
              "Unexpected CodecState subelement - ignoring");
          break;
        }

        g_free (stream->codec_state);
        stream->codec_state = data;
        stream->codec_state_size = data_len;


        if (stream->encodings && stream->encodings->len > 0
            && stream->codec_state && stream->codec_state_size > 0) {
          if (!gst_matroska_decode_data (stream->encodings,
                  &stream->codec_state, &stream->codec_state_size,
                  GST_MATROSKA_TRACK_ENCODING_SCOPE_CODEC_DATA, TRUE)) {
            GST_WARNING_OBJECT (demux, "Decoding codec state failed");
          }
        }

        GST_DEBUG_OBJECT (demux, "CodecState of %" G_GSIZE_FORMAT " bytes",
            stream->codec_state_size);
        break;
      }

      default:
        ret = gst_matroska_read_common_parse_skip (&demux->common, ebml,
            "BlockGroup", id);
        break;

      case GST_MATROSKA_ID_BLOCKVIRTUAL:
      case GST_MATROSKA_ID_BLOCKADDITIONS:
      case GST_MATROSKA_ID_REFERENCEPRIORITY:
      case GST_MATROSKA_ID_REFERENCEVIRTUAL:
      case GST_MATROSKA_ID_SLICES:
        GST_DEBUG_OBJECT (demux,
            "Skipping BlockGroup subelement 0x%x - ignoring", id);
        ret = gst_ebml_read_skip (ebml);
        break;
    }

    if (is_simpleblock)
      break;
  }


  if (ret != GST_FLOW_OK)
    goto data_error;

  if (ret == GST_FLOW_OK && readblock) {
    gboolean invisible_frame = FALSE;
    gboolean delta_unit = FALSE;
    guint64 duration = 0;
    gint64 lace_time = 0;
    GstEvent *protect_event;

    stream = g_ptr_array_index (demux->common.src, stream_num);

    if (cluster_time != GST_CLOCK_TIME_NONE) {


      if (time < 0 && (-time) > cluster_time) {
        lace_time = 0;
      } else {
        if (stream->timecodescale == 1.0)
          lace_time = (cluster_time + time) * demux->common.time_scale;
        else
          lace_time =
              gst_util_guint64_to_gdouble ((cluster_time + time) *
              demux->common.time_scale) * stream->timecodescale;
      }
    } else {
      lace_time = GST_CLOCK_TIME_NONE;
    }

    while ((protect_event = g_queue_pop_head (&stream->protection_event_queue))) {
      GST_TRACE_OBJECT (demux, "pushing protection event for stream %d:%s",
          stream->index, GST_STR_NULL (stream->name));
      gst_pad_push_event (stream->pad, protect_event);
    }


    if (GST_CLOCK_TIME_IS_VALID (lace_time) && demux->need_segment) {
      GstSegment *segment = &demux->common.segment;
      guint64 clace_time;
      GstEvent *segment_event;

      if (!GST_CLOCK_TIME_IS_VALID (demux->stream_start_time)) {
        demux->stream_start_time = lace_time;
        GST_DEBUG_OBJECT (demux,
            "Setting stream start time to %" GST_TIME_FORMAT,
            GST_TIME_ARGS (lace_time));
      }
      clace_time = MAX (lace_time, demux->stream_start_time);
      if (GST_CLOCK_TIME_IS_VALID (demux->common.segment.position) &&
          demux->common.segment.position != 0) {
        GST_DEBUG_OBJECT (demux,
            "using stored seek position %" GST_TIME_FORMAT,
            GST_TIME_ARGS (demux->common.segment.position));
        clace_time = demux->common.segment.position;
        segment->position = GST_CLOCK_TIME_NONE;
      }
      segment->start = clace_time;
      segment->stop = GST_CLOCK_TIME_NONE;
      segment->time = segment->start - demux->stream_start_time;
      segment->position = segment->start - demux->stream_start_time;
      GST_DEBUG_OBJECT (demux,
          "generated segment starting at %" GST_TIME_FORMAT ": %"
          GST_SEGMENT_FORMAT, GST_TIME_ARGS (lace_time), segment);

      segment_event = gst_event_new_segment (segment);
      if (demux->segment_seqnum)
        gst_event_set_seqnum (segment_event, demux->segment_seqnum);
      gst_matroska_demux_send_event (demux, segment_event);
      demux->need_segment = FALSE;
      demux->segment_seqnum = 0;
    }


    gst_matroska_demux_push_codec_data_all (demux);

    if (block_duration != -1) {
      if (stream->timecodescale == 1.0)
        duration = gst_util_uint64_scale (block_duration,
            demux->common.time_scale, 1);
      else
        duration =
            gst_util_gdouble_to_guint64 (gst_util_guint64_to_gdouble
            (gst_util_uint64_scale (block_duration, demux->common.time_scale,
                    1)) * stream->timecodescale);
    } else if (stream->default_duration) {
      duration = stream->default_duration * laces;
    }


    if (stream->type == GST_MATROSKA_TRACK_TYPE_VIDEO) {


      if ((is_simpleblock && !(flags & 0x80)) || referenceblock) {
        delta_unit = TRUE;
        invisible_frame = ((flags & 0x08)) &&
            (!strcmp (stream->codec_id, GST_MATROSKA_CODEC_ID_VIDEO_VP8) ||
            !strcmp (stream->codec_id, GST_MATROSKA_CODEC_ID_VIDEO_VP9) ||
            !strcmp (stream->codec_id, GST_MATROSKA_CODEC_ID_VIDEO_AV1));
      }


      if (delta_unit
          && demux->common.segment.
          flags & GST_SEGMENT_FLAG_TRICKMODE_KEY_UNITS) {
        GST_LOG_OBJECT (demux, "Skipping non-keyframe on stream %d",
            stream->index);
        ret = GST_FLOW_OK;
        goto done;
      }
    }

    for (n = 0; n < laces; n++) {
      GstBuffer *sub;

      if (G_UNLIKELY (lace_size[n] > size)) {
        GST_WARNING_OBJECT (demux, "Invalid lace size");
        break;
      }


      if (GST_CLOCK_TIME_IS_VALID (lace_time) &&
          stream->type == GST_MATROSKA_TRACK_TYPE_VIDEO &&
          stream->index_table && demux->common.segment.rate > 0.0) {
        GstMatroskaTrackVideoContext *videocontext =
            (GstMatroskaTrackVideoContext *) stream;
        GstClockTime earliest_time;
        GstClockTime earliest_stream_time;

        GST_OBJECT_LOCK (demux);
        earliest_time = videocontext->earliest_time;
        GST_OBJECT_UNLOCK (demux);
        earliest_stream_time =
            gst_segment_position_from_running_time (&demux->common.segment,
            GST_FORMAT_TIME, earliest_time);

        if (GST_CLOCK_TIME_IS_VALID (lace_time) &&
            GST_CLOCK_TIME_IS_VALID (earliest_stream_time) &&
            lace_time <= earliest_stream_time) {

          GstMatroskaIndex *entry =
              gst_util_array_binary_search (stream->index_table->data,
              stream->index_table->len, sizeof (GstMatroskaIndex),
              (GCompareDataFunc) gst_matroska_index_seek_find,
              GST_SEARCH_MODE_BEFORE, &earliest_stream_time, NULL);


          if (entry && GST_CLOCK_TIME_IS_VALID (entry->time) &&
              entry->time > lace_time) {
            GST_LOG_OBJECT (demux, "Skipping lace before late keyframe");
            stream->set_discont = TRUE;
            goto next_lace;
          }
        }
      }

      sub = gst_buffer_copy_region (buf, GST_BUFFER_COPY_ALL,
          gst_buffer_get_size (buf) - size, lace_size[n]);
      GST_DEBUG_OBJECT (demux, "created subbuffer %p", sub);

      if (delta_unit)
        GST_BUFFER_FLAG_SET (sub, GST_BUFFER_FLAG_DELTA_UNIT);
      else
        GST_BUFFER_FLAG_UNSET (sub, GST_BUFFER_FLAG_DELTA_UNIT);

      if (invisible_frame)
        GST_BUFFER_FLAG_SET (sub, GST_BUFFER_FLAG_DECODE_ONLY);

      if (stream->encodings != NULL && stream->encodings->len > 0)
        sub = gst_matroska_decode_buffer (stream, sub);

      if (sub == NULL) {
        GST_WARNING_OBJECT (demux, "Decoding buffer failed");
        goto next_lace;
      }

      if (!stream->dts_only) {
        GST_BUFFER_PTS (sub) = lace_time;
      } else {
        GST_BUFFER_DTS (sub) = lace_time;
        if (stream->intra_only)
          GST_BUFFER_PTS (sub) = lace_time;
      }

      buffer_timestamp = gst_matroska_track_get_buffer_timestamp (stream, sub);

      if (GST_CLOCK_TIME_IS_VALID (lace_time)) {
        GstClockTime last_stop_end;


        if (GST_CLOCK_TIME_IS_VALID (demux->common.segment.stop) &&
            lace_time >= demux->common.segment.stop) {
          GST_DEBUG_OBJECT (demux,
              "Stream %d after segment stop %" GST_TIME_FORMAT, stream->index,
              GST_TIME_ARGS (demux->common.segment.stop));
          gst_buffer_unref (sub);
          goto eos;
        }
        if (offset >= stream->to_offset
            || (GST_CLOCK_TIME_IS_VALID (demux->to_time)
                && lace_time > demux->to_time)) {
          GST_DEBUG_OBJECT (demux, "Stream %d after playback section",
              stream->index);
          gst_buffer_unref (sub);
          goto eos;
        }


        GST_OBJECT_LOCK (demux);
        if (demux->max_gap_time &&
            GST_CLOCK_TIME_IS_VALID (demux->last_stop_end) &&
            demux->common.segment.rate > 0.0) {
          GstClockTimeDiff diff;


          diff = GST_CLOCK_DIFF (demux->last_stop_end, lace_time);
          if (diff > 0 && diff > demux->max_gap_time
              && lace_time > demux->common.segment.start
              && (!GST_CLOCK_TIME_IS_VALID (demux->common.segment.stop)
                  || lace_time < demux->common.segment.stop)) {
            GstEvent *event;
            GST_DEBUG_OBJECT (demux,
                "Gap of %" G_GINT64_FORMAT " ns detected in"
                "stream %d (%" GST_TIME_FORMAT " -> %" GST_TIME_FORMAT "). "
                "Sending updated SEGMENT events", diff,
                stream->index, GST_TIME_ARGS (stream->pos),
                GST_TIME_ARGS (lace_time));

            event = gst_event_new_gap (demux->last_stop_end, diff);
            GST_OBJECT_UNLOCK (demux);
            gst_pad_push_event (stream->pad, event);
            GST_OBJECT_LOCK (demux);
          }
        }

        if (!GST_CLOCK_TIME_IS_VALID (demux->common.segment.position)
            || demux->common.segment.position < lace_time) {
          demux->common.segment.position = lace_time;
        }
        GST_OBJECT_UNLOCK (demux);

        last_stop_end = lace_time;
        if (duration) {
          GST_BUFFER_DURATION (sub) = duration / laces;
          last_stop_end += GST_BUFFER_DURATION (sub);
        }

        if (!GST_CLOCK_TIME_IS_VALID (demux->last_stop_end) ||
            demux->last_stop_end < last_stop_end)
          demux->last_stop_end = last_stop_end;

        GST_OBJECT_LOCK (demux);
        if (demux->common.segment.duration == -1 ||
            demux->stream_start_time + demux->common.segment.duration <
            last_stop_end) {
          demux->common.segment.duration =
              last_stop_end - demux->stream_start_time;
          GST_OBJECT_UNLOCK (demux);
          if (!demux->invalid_duration) {
            gst_element_post_message (GST_ELEMENT_CAST (demux),
                gst_message_new_duration_changed (GST_OBJECT_CAST (demux)));
            demux->invalid_duration = TRUE;
          }
        } else {
          GST_OBJECT_UNLOCK (demux);
        }
      }

      stream->pos = lace_time;

      gst_matroska_demux_sync_streams (demux);

      if (stream->set_discont) {
        GST_DEBUG_OBJECT (demux, "marking DISCONT");
        GST_BUFFER_FLAG_SET (sub, GST_BUFFER_FLAG_DISCONT);
        stream->set_discont = FALSE;
      } else {
        GST_BUFFER_FLAG_UNSET (sub, GST_BUFFER_FLAG_DISCONT);
      }


      if (!GST_CLOCK_TIME_IS_VALID (stream->from_time))
        stream->from_time = lace_time;
      if (stream->from_offset == -1)
        stream->from_offset = offset;

      GST_DEBUG_OBJECT (demux,
          "Pushing lace %d, data of size %" G_GSIZE_FORMAT
          " for stream %d, time=%" GST_TIME_FORMAT " and duration=%"
          GST_TIME_FORMAT, n, gst_buffer_get_size (sub), stream_num,
          GST_TIME_ARGS (buffer_timestamp),
          GST_TIME_ARGS (GST_BUFFER_DURATION (sub)));

#if 0
      if (demux->common.element_index) {
        if (stream->index_writer_id == -1)
          gst_index_get_writer_id (demux->common.element_index,
              GST_OBJECT (stream->pad), &stream->index_writer_id);

        GST_LOG_OBJECT (demux, "adding association %" GST_TIME_FORMAT "-> %"
            G_GUINT64_FORMAT " for writer id %d",
            GST_TIME_ARGS (buffer_timestamp), cluster_offset,
            stream->index_writer_id);
        gst_index_add_association (demux->common.element_index,
            stream->index_writer_id, GST_BUFFER_FLAG_IS_SET (sub,
                GST_BUFFER_FLAG_DELTA_UNIT) ? 0 : GST_ASSOCIATION_FLAG_KEY_UNIT,
            GST_FORMAT_TIME, buffer_timestamp, GST_FORMAT_BYTES, cluster_offset,
            NULL);
      }
#endif


      if (stream->postprocess_frame) {
        GST_LOG_OBJECT (demux, "running post process");
        ret = stream->postprocess_frame (GST_ELEMENT (demux), stream, &sub);
      }


      sub = gst_matroska_demux_align_buffer (demux, sub, stream->alignment);

      if (!strcmp (stream->codec_id, GST_MATROSKA_CODEC_ID_AUDIO_OPUS)) {
        guint64 start_clip = 0, end_clip = 0;


        if (GST_BUFFER_PTS_IS_VALID (sub) && stream->codec_delay) {
          if (GST_BUFFER_PTS (sub) > stream->codec_delay) {
            GST_BUFFER_PTS (sub) -= stream->codec_delay;
          } else {
            GST_BUFFER_PTS (sub) = 0;


            start_clip =
                gst_util_uint64_scale_round (stream->codec_delay, 48000,
                GST_SECOND);

            if (GST_BUFFER_DURATION_IS_VALID (sub)) {
              if (GST_BUFFER_DURATION (sub) > stream->codec_delay)
                GST_BUFFER_DURATION (sub) -= stream->codec_delay;
              else
                GST_BUFFER_DURATION (sub) = 0;
            }
          }
        }

        if (block_discardpadding) {
          end_clip =
              gst_util_uint64_scale_round (block_discardpadding, 48000,
              GST_SECOND);
        }

        if (start_clip || end_clip) {
          gst_buffer_add_audio_clipping_meta (sub, GST_FORMAT_DEFAULT,
              start_clip, end_clip);
        }
      }

      if (GST_BUFFER_PTS_IS_VALID (sub)) {
        stream->pos = GST_BUFFER_PTS (sub);
        if (GST_BUFFER_DURATION_IS_VALID (sub))
          stream->pos += GST_BUFFER_DURATION (sub);
      } else if (GST_BUFFER_DTS_IS_VALID (sub)) {
        stream->pos = GST_BUFFER_DTS (sub);
        if (GST_BUFFER_DURATION_IS_VALID (sub))
          stream->pos += GST_BUFFER_DURATION (sub);
      }

      ret = gst_pad_push (stream->pad, sub);

      if (demux->common.segment.rate < 0) {
        if (lace_time > demux->common.segment.stop && ret == GST_FLOW_EOS) {


          GST_DEBUG_OBJECT (demux, "downstream has reached end of segment");
          ret = GST_FLOW_OK;
        }
      }

      ret = gst_flow_combiner_update_pad_flow (demux->flowcombiner,
          stream->pad, ret);

    next_lace:
      size -= lace_size[n];
      if (lace_time != GST_CLOCK_TIME_NONE && duration)
        lace_time += duration / laces;
      else
        lace_time = GST_CLOCK_TIME_NONE;
    }
  }

done:
  if (buf) {
    gst_buffer_unmap (buf, &map);
    gst_buffer_unref (buf);
  }
  g_free (lace_size);

  return ret;


eos:
  {
    stream->eos = TRUE;
    ret = GST_FLOW_OK;

    ret = gst_flow_combiner_update_pad_flow (demux->flowcombiner, stream->pad,
        ret);
    goto done;
  }
invalid_lacing:
  {
    GST_ELEMENT_WARNING (demux, STREAM, DEMUX, (NULL), ("Invalid lacing size"));

    ret = GST_FLOW_OK;
    goto done;
  }
data_error:
  {
    GST_ELEMENT_WARNING (demux, STREAM, DEMUX, (NULL), ("Data error"));

    ret = GST_FLOW_OK;
    goto done;
  }
}
