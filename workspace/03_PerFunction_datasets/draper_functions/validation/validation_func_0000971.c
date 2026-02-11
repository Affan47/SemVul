gst_qt_mux_setup_metadata (GstQTMux * qtmux)
{
  const GstTagList *tags;

  GST_OBJECT_LOCK (qtmux);
  tags = gst_tag_setter_get_tag_list (GST_TAG_SETTER (qtmux));
  GST_OBJECT_UNLOCK (qtmux);

  GST_LOG_OBJECT (qtmux, "tags: %" GST_PTR_FORMAT, tags);

  if (tags && !gst_tag_list_is_empty (tags)) {
    GstTagList *copy = gst_tag_list_copy (tags);

    GST_DEBUG_OBJECT (qtmux, "Removing bogus tags");
    gst_tag_list_remove_tag (copy, GST_TAG_VIDEO_CODEC);
    gst_tag_list_remove_tag (copy, GST_TAG_AUDIO_CODEC);
    gst_tag_list_remove_tag (copy, GST_TAG_CONTAINER_FORMAT);

    GST_DEBUG_OBJECT (qtmux, "Formatting tags");
    gst_qt_mux_add_metadata_tags (qtmux, copy);
    gst_qt_mux_add_xmp_tags (qtmux, copy);
    gst_tag_list_unref (copy);
  } else {
    GST_DEBUG_OBJECT (qtmux, "No tags received");
  }
}
