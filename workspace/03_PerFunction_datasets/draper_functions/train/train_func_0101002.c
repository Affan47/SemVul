assert_cell_parented (GObject *parent,
		      GObject *child)
{
  GList *cells;

  cells = gtk_cell_layout_get_cells (GTK_CELL_LAYOUT (parent));
  g_assert (g_list_find (cells, child) != NULL);
  g_list_free (cells);
}
