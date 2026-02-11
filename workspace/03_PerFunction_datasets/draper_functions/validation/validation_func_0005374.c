gtk_clutter_window_add (GtkContainer *self,
                        GtkWidget    *widget)
{
  GtkClutterWindowPrivate *priv;
  GtkWidget *bin;

  g_return_if_fail (GTK_CLUTTER_IS_WINDOW (self));
  priv = GTK_CLUTTER_WINDOW (self)->priv;

  bin = gtk_clutter_actor_get_widget (GTK_CLUTTER_ACTOR (priv->actor));
  GTK_CONTAINER_GET_CLASS (bin)->add (GTK_CONTAINER (bin), widget);
}
