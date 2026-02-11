mx_window_actor_removed_cb (ClutterContainer *container,
                            ClutterActor     *actor,
                            MxWindow         *self)
{
  MxWindowPrivate *priv = self->priv;

  if (actor == priv->child)
    {
      g_object_set (G_OBJECT (priv->child),
                    "natural-width-set", FALSE,
                    "natural-height-set", FALSE,
                    NULL);
      priv->child = NULL;
      g_object_notify (G_OBJECT (self), "child");
    }
}
