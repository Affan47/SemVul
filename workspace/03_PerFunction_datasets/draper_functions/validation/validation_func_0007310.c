gst_auto_audio_src_dispose (GstAutoAudioSrc * src)
{
  gst_auto_audio_src_clear_kid (src);

  if (src->filter_caps)
    gst_caps_unref (src->filter_caps);
  src->filter_caps = NULL;

  G_OBJECT_CLASS (parent_class)->dispose ((GObject *) src);
}
