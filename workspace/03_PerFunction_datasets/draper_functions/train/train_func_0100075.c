web_view_gtkhtml_link_clicked (EWebViewGtkHTML *web_view,
                               const gchar *uri)
{
	gpointer parent;

	parent = gtk_widget_get_toplevel (GTK_WIDGET (web_view));
	parent = gtk_widget_is_toplevel (parent) ? parent : NULL;

	e_show_uri (parent, uri);
}
