gst_base_text_overlay_finalize (GObject * object)
{
  GstBaseTextOverlay *overlay = GST_BASE_TEXT_OVERLAY (object);

  g_free (overlay->default_text);

  if (overlay->composition) {
    gst_video_overlay_composition_unref (overlay->composition);
    overlay->composition = NULL;
  }

  if (overlay->text_image) {
    gst_buffer_unref (overlay->text_image);
    overlay->text_image = NULL;
  }

  if (overlay->layout) {
    g_object_unref (overlay->layout);
    overlay->layout = NULL;
  }

  if (overlay->text_buffer) {
    gst_buffer_unref (overlay->text_buffer);
    overlay->text_buffer = NULL;
  }

  g_mutex_clear (&overlay->lock);
  g_cond_clear (&overlay->cond);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
