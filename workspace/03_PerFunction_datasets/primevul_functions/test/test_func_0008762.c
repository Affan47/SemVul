callbacks_print_activate (GtkMenuItem *menuitem, gpointer user_data)
{
	GtkPrintOperation *print;


	print = gtk_print_operation_new ();

	g_signal_connect (print, "begin_print", G_CALLBACK (callbacks_begin_print), NULL);
	g_signal_connect (print, "draw_page", G_CALLBACK (callbacks_print_render_page), NULL);


	(void) gtk_print_operation_run (print, GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
	                              (GtkWindow *) screen.win.topLevelWindow , NULL);

	g_object_unref (print);
}
