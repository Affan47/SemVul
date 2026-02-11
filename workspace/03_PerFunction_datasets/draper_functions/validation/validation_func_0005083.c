tp_base_media_call_stream_set_sending (TpBaseCallStream *bcs,
    gboolean sending,
    GError **error)
{
  TpBaseMediaCallStream *self = TP_BASE_MEDIA_CALL_STREAM (bcs);
  TpBaseMediaCallStreamClass *klass =
      TP_BASE_MEDIA_CALL_STREAM_GET_CLASS (self);

  if (sending)
    {
      if (klass->set_sending != NULL &&
          !klass->set_sending (self, sending, error))
        return FALSE;
    }
  else
   {
     tp_base_media_call_stream_set_local_sending (self, FALSE);


     if (self->priv->sending_state == TP_STREAM_FLOW_STATE_STOPPED &&
         klass->set_sending != NULL)
       return klass->set_sending (self, sending, error);
     else
       self->priv->sending_stop_requested = TRUE;
   }

  return TRUE;
}
