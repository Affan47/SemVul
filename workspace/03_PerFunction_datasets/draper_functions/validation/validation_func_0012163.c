cb_col_check_autofit_clicked (GtkToggleButton *togglebutton, gpointer _i)
{
	int i = GPOINTER_TO_INT (_i);
	StfDialogData *pagedata =
		g_object_get_data (G_OBJECT (togglebutton), "pagedata");
	gboolean active = gtk_toggle_button_get_active (togglebutton);

	g_return_if_fail (i < pagedata->format.col_import_array_len);

	pagedata->format.col_autofit_array[i] = active;

	return;
}
