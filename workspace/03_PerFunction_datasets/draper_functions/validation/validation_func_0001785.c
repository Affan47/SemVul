egg_toolbars_model_item_nth (EggToolbarsModel *model,
			     int	       toolbar_position,
			     int               position)
{
  GNode *toolbar;
  GNode *item;
  EggToolbarsItem *idata;

  toolbar = g_node_nth_child (model->priv->toolbars, toolbar_position);
  g_return_val_if_fail (toolbar != NULL, NULL);

  item = g_node_nth_child (toolbar, position);
  g_return_val_if_fail (item != NULL, NULL);

  idata = item->data;
  return idata->name;
}
