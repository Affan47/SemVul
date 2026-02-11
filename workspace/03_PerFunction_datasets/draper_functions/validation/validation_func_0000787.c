gedit_panel_focus_document (GeditPanel *panel)
{
	GtkWidget *toplevel;

	toplevel = gtk_widget_get_toplevel (GTK_WIDGET (panel));

	if (gtk_widget_is_toplevel (toplevel) && GEDIT_IS_WINDOW (toplevel))
	{
		GeditView *view;

		view = gedit_window_get_active_view (GEDIT_WINDOW (toplevel));
		if (view != NULL)
		{
			gtk_widget_grab_focus (GTK_WIDGET (view));
		}
	}
}
