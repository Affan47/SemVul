evd_peer_manager_cleanup_peers (EvdPeerManager *self)
{
  if (g_timer_elapsed (self->priv->peer_cleanup_timer, NULL) <=
      self->priv->peer_cleanup_interval)
    return;

  g_timer_start (self->priv->peer_cleanup_timer);

  g_hash_table_foreach_remove (self->priv->peers,
                               evd_peer_manager_check_peer,
                               self);

  while (g_queue_get_length (self->priv->removal_list) > 0)
    {
      EvdPeer *peer;

      peer = EVD_PEER (g_queue_pop_head (self->priv->removal_list));

      evd_peer_manager_close_peer_internal (self, peer, FALSE);
      g_object_unref (peer);
    }
}
