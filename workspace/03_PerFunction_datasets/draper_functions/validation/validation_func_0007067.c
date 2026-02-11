gtkhash_properties_list_filter(GtkTreeModel *model,
	GtkTreeIter *iter, struct page_s *page)
{
	gboolean enabled;
	gtk_tree_model_get(model, iter, COL_ENABLED, &enabled, -1);

	if (!enabled && !gtk_check_menu_item_get_active(page->menuitem_show_funcs))
		return false;

	return true;
}
