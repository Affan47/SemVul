tp_svc_media_stream_handler_emit_start_telephony_event (gpointer instance,
    guchar arg_Event)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_StartTelephonyEvent],
      0,
      arg_Event);
}
