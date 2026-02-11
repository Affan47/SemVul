update_bookmark_color(GigoloBookmarkEditDialog *dialog)
{
	GigoloBookmarkEditDialogPrivate *priv;
	GdkColor color;
	gchar *color_string;

	priv = GIGOLO_BOOKMARK_EDIT_DIALOG_GET_PRIVATE(dialog);

	if (! priv->color_set)

		return;

	gtk_color_button_get_color(GTK_COLOR_BUTTON(priv->color_chooser), &color);
	color_string = gdk_color_to_string(&color);
	gigolo_bookmark_set_color(priv->bookmark_update, color_string);
	g_free(color_string);
}
