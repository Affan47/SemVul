fs_nice_stream_transmitter_finalize (GObject *object)
{
  FsNiceStreamTransmitter *self = FS_NICE_STREAM_TRANSMITTER (object);

  fs_candidate_list_destroy (self->priv->preferred_local_candidates);

  fs_candidate_list_destroy (self->priv->remote_candidates);
  fs_candidate_list_destroy (self->priv->local_candidates);

  if (self->priv->relay_info)
    g_value_array_free (self->priv->relay_info);

  g_free (self->priv->stun_ip);

  g_mutex_free (self->priv->mutex);

  g_free (self->priv->username);
  g_free (self->priv->password);

  g_free (self->priv->component_has_been_ready);

  parent_class->finalize (object);
}
