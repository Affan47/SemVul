egg_toolbars_model_remove_toolbar (EggToolbarsModel   *model,
				   int                 position)
{
  GNode *node;
  EggTbModelFlags flags;

  g_return_if_fail (EGG_IS_TOOLBARS_MODEL (model));

  flags = egg_toolbars_model_get_flags (model, position);

  if (!(flags & EGG_TB_MODEL_NOT_REMOVABLE))
    {
      node = g_node_nth_child (model->priv->toolbars, position);
      g_return_if_fail (node != NULL);

      toolbar_node_free (node, model);

      g_signal_emit (G_OBJECT (model), signals[TOOLBAR_REMOVED],
		     0, position);
    }
}
