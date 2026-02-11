ges_track_text_overlay_create_element (GESTrackObject * object)
{
  GstElement *ret, *text, *iconv, *oconv;
  GstPad *src_target, *sink_target;
  GstPad *src, *sink;
  GESTrackTextOverlay *self = GES_TRACK_TEXT_OVERLAY (object);

  text = gst_element_factory_make ("textoverlay", NULL);
  iconv = gst_element_factory_make ("ffmpegcolorspace", NULL);
  oconv = gst_element_factory_make ("ffmpegcolorspace", NULL);
  self->priv->text_el = text;
  g_object_ref (text);

  if (self->priv->text)
    g_object_set (text, "text", (gchar *) self->priv->text, NULL);
  if (self->priv->font_desc)
    g_object_set (text, "font-desc", (gchar *) self->priv->font_desc, NULL);

  g_object_set (text, "halignment", (gint) self->priv->halign, "valignment",
      (gint) self->priv->valign, NULL);

  ret = gst_bin_new ("overlay-bin");
  gst_bin_add_many (GST_BIN (ret), text, iconv, oconv, NULL);
  gst_element_link_many (iconv, text, oconv, NULL);

  src_target = gst_element_get_static_pad (oconv, "src");
  sink_target = gst_element_get_static_pad (iconv, "sink");

  src = gst_ghost_pad_new ("src", src_target);
  sink = gst_ghost_pad_new ("video_sink", sink_target);
  g_object_unref (src_target);
  g_object_unref (sink_target);

  gst_element_add_pad (ret, src);
  gst_element_add_pad (ret, sink);

  return ret;
}
