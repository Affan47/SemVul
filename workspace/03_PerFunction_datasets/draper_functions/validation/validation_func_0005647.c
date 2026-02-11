results_sort(results_t * r, results_sort_e field, results_sort_dir_e direction)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection(r->summary_view);
	GtkTreeIter iter;
	int f;
	result_item_t *item;
#ifndef NDEBUG
	results_sort_e sort;
	results_sort_dir_e dir;
#endif
	if (!gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		return;
	}
	gtk_tree_model_get(GTK_TREE_MODEL(r->summary_tree), &iter, RESULTS_SUMMARY_COLUMN_FORM, &f,
			   RESULTS_SUMMARY_COLUMN_ITEM, &item, -1);
	poldiff_form_e form = (poldiff_form_e) f;
	assert(item != NULL && item == r->current_item && form == r->current_form
	       && result_item_get_current_sort(item, form, &sort, &dir) != 0);
	result_item_set_current_sort(item, form, field, direction);
	if (result_item_is_render_slow(r->current_item, form)) {
		results_get_slow_buffer(r, "Sorting Items");
	} else {
		result_item_get_buffer(item, form);
	}
}
