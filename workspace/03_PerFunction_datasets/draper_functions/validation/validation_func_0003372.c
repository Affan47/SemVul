evd_peer_manager_dispose (GObject *obj)
{
  EvdPeerManager *self = EVD_PEER_MANAGER (obj);

  if (self->priv->peers != NULL)
    {
      while (g_queue_get_length (self->priv->removal_list) > 0)
        {
          EvdPeer *peer;

          peer = EVD_PEER (g_queue_pop_head (self->priv->removal_list));
          evd_peer_manager_close_peer_internal (self, peer, FALSE);
          g_object_unref (peer);
        }
      g_queue_free (self->priv->removal_list);

      g_hash_table_unref (self->priv->peers);
      self->priv->peers = NULL;
    }

  G_OBJECT_CLASS (evd_peer_manager_parent_class)->dispose (obj);
}
