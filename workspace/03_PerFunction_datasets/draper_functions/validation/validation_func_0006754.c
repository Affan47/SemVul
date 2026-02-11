window_cancel_find (GtkWidget    *widget,
		    GiggleWindow *window)
{
	GiggleWindowPriv *priv;
	GiggleView       *view;

	priv = window->priv;

	view = giggle_view_shell_get_selected (GIGGLE_VIEW_SHELL (priv->view_shell));
	g_return_if_fail (GIGGLE_IS_SEARCHABLE (view));

	giggle_searchable_cancel (GIGGLE_SEARCHABLE (view));

	gtk_widget_hide (widget);
}
