visu_rendering_getByName(const gchar *name)
{
  if (!tableOfMethods)
    g_type_class_ref(VISU_TYPE_RENDERING);
  if (g_hash_table_size(tableOfMethods) == 0)
    setupAllMethods();

  return (VisuRendering*)g_hash_table_lookup(tableOfMethods, (gpointer)name);
}
