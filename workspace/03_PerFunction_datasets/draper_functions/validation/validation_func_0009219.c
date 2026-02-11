get_value_tab (GType type, const gchar *value, GCompareFunc cmpfunc)
{
  GList *values, *tab_iter;
  gpointer klass;
  ValueTab *tab;

  if (!values_hash) return NULL;

  klass = g_type_class_ref (type);

  if ((values = g_hash_table_lookup (values_hash, klass)) != NULL &&
      (tab_iter = g_list_find_custom (values, value, cmpfunc)) != NULL)
    tab = tab_iter->data;
  else
    tab = NULL;

  g_type_class_unref (klass);

  return tab;
}
