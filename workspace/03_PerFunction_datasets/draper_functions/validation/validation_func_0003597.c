wait_for_streams_to_be_receiving (TpBaseMediaCallChannel *self)
{
  TpBaseCallChannel *bcc = TP_BASE_CALL_CHANNEL (self);
  GList *l;

  for (l = tp_base_call_channel_get_contents (bcc); l; l = l->next)
    {
      TpBaseCallContent *content = l->data;
      GList *l_stream;

      if (tp_base_call_content_get_disposition (content) !=
              TP_CALL_CONTENT_DISPOSITION_INITIAL)
        continue;

      for (l_stream = tp_base_call_content_get_streams (content);
           l_stream;
           l_stream = l_stream->next)
        {
          TpBaseCallStream *stream = l_stream->data;

          g_signal_connect (stream, "notify::receiving-state",
              G_CALLBACK (streams_changed_cb), self);
          g_signal_connect (stream, "notify::remote-members",
              G_CALLBACK (streams_changed_cb), self);
        }
    }
}
