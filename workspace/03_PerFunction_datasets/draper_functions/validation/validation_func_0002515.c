convert_frame_need_data_callback (GstElement * src, guint size,
    GstVideoConvertSampleContext * context)
{
  GstFlowReturn ret = GST_FLOW_ERROR;
  GError *error;
  GstBuffer *buffer;

  g_mutex_lock (&context->mutex);

  if (context->finished)
    goto done;

  buffer = gst_sample_get_buffer (context->sample);
  g_signal_emit_by_name (src, "push-buffer", buffer, &ret);
  gst_sample_unref (context->sample);
  context->sample = NULL;

  if (ret != GST_FLOW_OK) {
    GST_ERROR ("Could not push video frame: %s", gst_flow_get_name (ret));

    error = g_error_new (GST_CORE_ERROR, GST_CORE_ERROR_FAILED,
        "Could not push video frame: %s", gst_flow_get_name (ret));

    convert_frame_finish (context, NULL, error);
  }

  g_signal_handlers_disconnect_by_func (src, convert_frame_need_data_callback,
      context);

done:
  g_mutex_unlock (&context->mutex);
}
