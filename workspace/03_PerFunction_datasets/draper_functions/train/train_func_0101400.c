on_about_activate ( GtkWidget *menuitem,
                    gpointer user_data )
{
	GtkWidget * win = lookup_widget( menuitem, "about_window" );
	if ( win )
	{
		gtk_window_set_transient_for(GTK_WINDOW(win), GTK_WINDOW(main_window));
		gtk_widget_show( win );
	}
}
