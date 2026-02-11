gst_dvbsub_overlay_init (GstDVBSubOverlay * render)
{
  GST_DEBUG_OBJECT (render, "init");

  render->srcpad = gst_pad_new_from_static_template (&src_factory, "src");
  render->video_sinkpad =
      gst_pad_new_from_static_template (&video_sink_factory, "video_sink");
  render->text_sinkpad =
      gst_pad_new_from_static_template (&text_sink_factory, "text_sink");

  gst_pad_set_chain_function (render->video_sinkpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_chain_video));
  gst_pad_set_chain_function (render->text_sinkpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_chain_text));

  gst_pad_set_event_function (render->video_sinkpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_event_video));
  gst_pad_set_event_function (render->text_sinkpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_event_text));
  gst_pad_set_event_function (render->srcpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_event_src));

  gst_pad_set_query_function (render->video_sinkpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_query_video));
  gst_pad_set_query_function (render->srcpad,
      GST_DEBUG_FUNCPTR (gst_dvbsub_overlay_query_src));

  GST_PAD_SET_PROXY_ALLOCATION (render->video_sinkpad);

  gst_element_add_pad (GST_ELEMENT (render), render->srcpad);
  gst_element_add_pad (GST_ELEMENT (render), render->video_sinkpad);
  gst_element_add_pad (GST_ELEMENT (render), render->text_sinkpad);

  gst_video_info_init (&render->info);

  render->current_subtitle = NULL;
  render->pending_subtitles = g_queue_new ();

  render->enable = DEFAULT_ENABLE;
  render->max_page_timeout = DEFAULT_MAX_PAGE_TIMEOUT;
  render->force_end = DEFAULT_FORCE_END;

  g_mutex_init (&render->dvbsub_mutex);
  gst_dvbsub_overlay_flush_subtitles (render);

  gst_segment_init (&render->video_segment, GST_FORMAT_TIME);
  gst_segment_init (&render->subtitle_segment, GST_FORMAT_TIME);

  GST_DEBUG_OBJECT (render, "init complete");
}
