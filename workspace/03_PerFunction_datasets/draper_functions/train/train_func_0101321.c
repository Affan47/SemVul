row_removed_cb (ClutterModel     *model,
                ClutterModelIter *iter,
                MxItemView       *item_view)
{
  GList *children;
  GList *l;
  ClutterActor *child;

  if (item_view->priv->is_frozen)
    return;

  children = clutter_container_get_children (CLUTTER_CONTAINER (item_view));
  l = g_list_nth (children, clutter_model_iter_get_row (iter));
  child = (ClutterActor *) l->data;
  clutter_container_remove_actor (CLUTTER_CONTAINER (item_view), child);
  g_list_free (children);
}
