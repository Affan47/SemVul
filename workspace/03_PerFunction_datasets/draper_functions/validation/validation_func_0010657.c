gst_qtdemux_base_init (gpointer klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  gst_element_class_add_static_pad_template (element_class,
      &gst_qtdemux_sink_template);
  gst_element_class_add_static_pad_template (element_class,
      &gst_qtdemux_videosrc_template);
  gst_element_class_add_static_pad_template (element_class,
      &gst_qtdemux_audiosrc_template);
  gst_element_class_add_static_pad_template (element_class,
      &gst_qtdemux_subsrc_template);
  gst_element_class_set_details_simple (element_class, "QuickTime demuxer",
      "Codec/Demuxer",
      "Demultiplex a QuickTime file into audio and video streams",
      "David Schleef <ds@schleef.org>, Wim Taymans <wim@fluendo.com>");

  GST_DEBUG_CATEGORY_INIT (qtdemux_debug, "qtdemux", 0, "qtdemux plugin");
}
