exo_icon_chooser_model_get_value (GtkTreeModel *tree_model,
                                  GtkTreeIter  *iter,
                                  gint          column,
                                  GValue       *value)
{
  ExoIconChooserModelItem *item;
  ExoIconChooserModel     *model = EXO_ICON_CHOOSER_MODEL (tree_model);

  _exo_return_if_fail (EXO_IS_ICON_CHOOSER_MODEL (model));
  _exo_return_if_fail (iter->stamp == model->stamp);


  item = ((GList *) iter->user_data)->data;

  switch (column)
    {
    case EXO_ICON_CHOOSER_MODEL_COLUMN_CONTEXT:
      g_value_init (value, G_TYPE_UINT);
      g_value_set_uint (value, item->context);
      break;

    case EXO_ICON_CHOOSER_MODEL_COLUMN_ICON_NAME:
      g_value_init (value, G_TYPE_STRING);
      g_value_set_static_string (value, item->icon_name);
      break;

    default:
      _exo_assert_not_reached ();
      break;
    }
}
