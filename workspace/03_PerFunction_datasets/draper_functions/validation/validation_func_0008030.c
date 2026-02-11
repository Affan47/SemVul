gst_real_audio_demux_reset (GstRealAudioDemux * demux)
{
  gst_adapter_clear (demux->adapter);

  if (demux->srcpad) {
    GST_DEBUG_OBJECT (demux, "Removing source pad");
    gst_element_remove_pad (GST_ELEMENT (demux), demux->srcpad);
    demux->srcpad = NULL;
  }

  if (demux->pending_tags) {
    gst_tag_list_free (demux->pending_tags);
    demux->pending_tags = NULL;
  }

  demux->state = REAL_AUDIO_DEMUX_STATE_MARKER;
  demux->ra_version = 0;
  demux->data_offset = 0;
  demux->packet_size = 0;

  demux->sample_rate = 0;
  demux->sample_width = 0;
  demux->channels = 0;
  demux->fourcc = 0;

  demux->need_newsegment = TRUE;

  demux->segment_running = FALSE;

  demux->byterate_num = 0;
  demux->byterate_denom = 0;

  demux->duration = 0;
  demux->upstream_size = 0;

  demux->offset = 0;

  gst_adapter_clear (demux->adapter);
}
