clutter_im_multicontext_focus_in (ClutterIMContext   *context)
{
  ClutterIMMulticontext *multicontext = CLUTTER_IM_MULTICONTEXT (context);
  ClutterIMContext *slave;


  if (multicontext->context_id == NULL ||
      global_context_id == NULL ||
      strcmp (global_context_id, multicontext->context_id) != 0)
    clutter_im_multicontext_set_slave (multicontext, NULL, FALSE);

  slave = clutter_im_multicontext_get_slave (multicontext);

  multicontext->priv->focus_in = TRUE;

  if (slave)
    clutter_im_context_focus_in (slave);
}
