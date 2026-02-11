ges_simple_timeline_layer_nth (GESSimpleTimelineLayer * layer, gint position)
{
  GList *list;
  GESSimpleTimelineLayerPrivate *priv = layer->priv;

  list = g_list_nth (priv->objects, position);

  if (list)
    return GES_TIMELINE_OBJECT (list->data);

  return NULL;
}
