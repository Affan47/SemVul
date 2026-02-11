lazy_list_iter_nth_child (GtkTreeModel *tree_model,
			  GtkTreeIter  *iter,
			  GtkTreeIter  *parent,
			  gint          n)
{
	GnumericLazyList *ll = (GnumericLazyList *) tree_model;

	g_return_val_if_fail (GNUMERIC_IS_LAZY_LIST (tree_model), FALSE);

	if (parent)
		return FALSE;

	iter->stamp = ll->stamp;
	iter->user_data = GINT_TO_POINTER (n);

	return (n >= 0 && n < ll->rows);
}
