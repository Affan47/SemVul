gst_ogm_parse_plugin_init (GstPlugin * plugin)
{
  gst_riff_init ();

  GST_DEBUG_CATEGORY_INIT (gst_ogm_parse_debug, "ogmparse", 0, "ogm parser");

  return gst_element_register (plugin, "ogmaudioparse", GST_RANK_PRIMARY,
      GST_TYPE_OGM_AUDIO_PARSE) &&
      gst_element_register (plugin, "ogmvideoparse", GST_RANK_PRIMARY,
      GST_TYPE_OGM_VIDEO_PARSE) &&
      gst_element_register (plugin, "ogmtextparse", GST_RANK_PRIMARY,
      GST_TYPE_OGM_TEXT_PARSE);
}
