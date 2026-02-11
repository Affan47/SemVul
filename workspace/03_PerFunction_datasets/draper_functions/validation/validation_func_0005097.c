search_find (GSimpleAction *action,
             GVariant      *parameter,
             gpointer       data)
{
  GucharmapWindow *guw = data;

  g_assert (GUCHARMAP_IS_WINDOW (guw));

  if (guw->search_dialog == NULL)
    {
      guw->search_dialog = gucharmap_search_dialog_new (guw);
      g_signal_connect (guw->search_dialog, "search-start", G_CALLBACK (search_start), guw);
      g_signal_connect (guw->search_dialog, "search-finish", G_CALLBACK (search_finish), guw);
    }

  gucharmap_search_dialog_present (GUCHARMAP_SEARCH_DIALOG (guw->search_dialog));
}
