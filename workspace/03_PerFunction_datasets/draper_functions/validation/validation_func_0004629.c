keyboard_shortcuts_set_section (CcPanel *panel, const char *section)
{
  GtkBuilder *builder;
  GtkTreeModel *section_model;
  GtkTreeIter iter;
  gboolean found, cont;

  builder = g_object_get_data (G_OBJECT (panel), "builder");
  if (builder == NULL)
    {

      g_object_set_data_full (G_OBJECT (panel), "section-to-set", g_strdup (section), g_free);
      return TRUE;
    }
  section_model = gtk_tree_view_get_model (GTK_TREE_VIEW (WID (builder, "section_treeview")));
  cont = gtk_tree_model_get_iter_first (section_model, &iter);
  found = FALSE;
  while (cont)
    {
      char *id;

      gtk_tree_model_get (section_model, &iter,
                          SECTION_ID_COLUMN, &id,
                          -1);

      if (g_strcmp0 (id, section) == 0)
        {
          found = TRUE;
          g_free (id);
          break;
        }
      g_free (id);
      cont = gtk_tree_model_iter_next (section_model, &iter);
    }
  if (found)
    {
      GtkTreeSelection *selection;

      selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (WID (builder, "section_treeview")));
      gtk_tree_selection_select_iter (selection, &iter);
    }
  else
    {
      g_warning ("Could not find section '%s' to switch to.", section);
    }

  return found;
}
