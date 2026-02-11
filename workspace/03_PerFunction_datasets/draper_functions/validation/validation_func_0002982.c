ui_pay_comboboxentry_test (GtkCellLayout   *cell_layout,
		   GtkCellRenderer *cell,
		   GtkTreeModel    *tree_model,
		   GtkTreeIter     *iter,
		   gpointer         data)
{
gchar *name;

	gtk_tree_model_get(tree_model, iter,
		0, &name,
		-1);

	if( !name )
		g_object_set(cell, "text", _("(no payee)"), NULL);
	else
		g_object_set(cell, "text", name, NULL);

}
