gegl_eval_mgr_new     (GeglNode *node,
                                     const gchar *pad_name)
{
  GeglEvalMgr *self = g_object_new (GEGL_TYPE_EVAL_MGR, NULL);
  g_assert (GEGL_IS_NODE (node));
  self->node = node;
  if (pad_name)
    self->pad_name = g_strdup (pad_name);
  else
    self->pad_name = g_strdup ("output");

  g_signal_connect (G_OBJECT (self->node), "invalidated", G_CALLBACK (gegl_eval_mgr_change_notification), self);
  g_signal_connect (G_OBJECT (self->node), "notify", G_CALLBACK (gegl_eval_mgr_change_notification), self);
  return self;
}
