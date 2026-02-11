tpaw_live_search_new (GtkWidget *hook)
{
  g_return_val_if_fail (hook == NULL || GTK_IS_WIDGET (hook), NULL);

  return g_object_new (TPAW_TYPE_LIVE_SEARCH,
      "hook-widget", hook,
      NULL);
}
