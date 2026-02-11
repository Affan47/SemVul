_tpl_action_chain_free (TplActionChain *self)
{
  g_queue_foreach (self->chain, (GFunc) link_free, NULL);
  g_queue_free (self->chain);
  g_object_unref (self->simple);
  g_slice_free (TplActionChain, self);
}
