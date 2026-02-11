exo_toolbars_model_real_get_item_id (ExoToolbarsModel *model,
                                     const gchar      *type,
                                     const gchar      *data)
{
  if (exo_str_is_equal (type, EXO_TOOLBARS_ITEM_TYPE))
    return g_strdup (data);
  return NULL;
}
