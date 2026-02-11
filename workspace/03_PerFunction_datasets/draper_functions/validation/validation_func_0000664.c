modify_view_on_export_click(GtkButton * button __attribute__ ((unused)), gpointer user_data)
{
	struct modify_view *mv = (struct modify_view *)user_data;
	char *path = util_save_file(GTK_WINDOW(mv->dialog), "Export Filter", mv->filter_filename);
	seaudit_filter_t *filter = modify_view_get_current_filter(mv);
	assert(filter != NULL);
	if (path == NULL) {
		return;
	}
	g_free(mv->filter_filename);
	mv->filter_filename = path;
	if (seaudit_filter_save_to_file(filter, mv->filter_filename) < 0) {
		toplevel_ERR(mv->top, "Error exporting filter: %s", strerror(errno));
	}
}
