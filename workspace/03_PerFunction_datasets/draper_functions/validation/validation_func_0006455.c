gtk_clutter_embed_show (GtkWidget *widget)
{
  GtkClutterEmbedPrivate *priv = GTK_CLUTTER_EMBED (widget)->priv;

  if (gtk_widget_get_realized (widget) && priv->stage != NULL)
    clutter_actor_show (priv->stage);

  GTK_WIDGET_CLASS (gtk_clutter_embed_parent_class)->show (widget);
}
