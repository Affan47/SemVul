gsl_unselect_all(GtkWidget *window)
{
	GSList *selection = NULL;

	selection = get_selection_from_window(GTK_WIDGET(window), TYPE_MASK_ALL);
	if (selection != NULL) {
		toggle_selection(window, selection);
		g_slist_free(selection);
	}
}
