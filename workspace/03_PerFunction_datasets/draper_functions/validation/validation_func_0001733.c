sset_node_info (GtkCMCTree     *ctree,
	       GtkCMCTreeNode *node,
	       const gchar  *text,
	       guint8        spacing,
	       GdkPixbuf    *pixbuf_closed,
	       GdkPixbuf    *pixbuf_opened,
	       gboolean      is_leaf,
	       gboolean      expanded)
{
  if (GTK_CMCTREE_ROW (node)->pixbuf_opened)
    {
      g_object_unref (GTK_CMCTREE_ROW (node)->pixbuf_opened);
    }
  if (GTK_CMCTREE_ROW (node)->pixbuf_closed)
    {
      g_object_unref (GTK_CMCTREE_ROW (node)->pixbuf_closed);
    }

  GTK_CMCTREE_ROW (node)->pixbuf_opened = NULL;
  GTK_CMCTREE_ROW (node)->pixbuf_closed = NULL;

  if (pixbuf_closed)
    {
      GTK_CMCTREE_ROW (node)->pixbuf_closed = g_object_ref (pixbuf_closed);
    }
  if (pixbuf_opened)
    {
      GTK_CMCTREE_ROW (node)->pixbuf_opened = g_object_ref (pixbuf_opened);
    }

  GTK_CMCTREE_ROW (node)->is_leaf  = is_leaf;
  GTK_CMCTREE_ROW (node)->expanded = (is_leaf) ? FALSE : expanded;

  if (GTK_CMCTREE_ROW (node)->expanded)
    gtk_cmctree_node_set_pixtext (ctree, node, ctree->tree_column,
				text, spacing, pixbuf_opened);
  else
    gtk_cmctree_node_set_pixtext (ctree, node, ctree->tree_column,
				text, spacing, pixbuf_closed);
}
