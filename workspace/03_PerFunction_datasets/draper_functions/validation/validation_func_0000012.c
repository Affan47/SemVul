g_vfs_goa_volume_dispose (GObject *_self)
{
  GVfsGoaVolume *self = G_VFS_GOA_VOLUME (_self);

  if (self->account_attention_needed_id != 0)
    {
      GoaAccount *account;

      account = goa_object_peek_account (self->object);
      g_signal_handler_disconnect (account, self->account_attention_needed_id);
      self->account_attention_needed_id = 0;
    }

  g_clear_object (&self->root);
  g_clear_object (&self->mount);
  g_clear_object (&self->object);

  G_OBJECT_CLASS (g_vfs_goa_volume_parent_class)->dispose (_self);
}
