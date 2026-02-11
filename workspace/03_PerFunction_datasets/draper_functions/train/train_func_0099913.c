gtk_clutter_embed_hide (GtkWidget *widget)
{
  GtkClutterEmbedPrivate *priv = GTK_CLUTTER_EMBED (widget)->priv;


  if (priv->stage != NULL)
    clutter_actor_hide (priv->stage);

  GTK_WIDGET_CLASS (gtk_clutter_embed_parent_class)->hide (widget);
}
