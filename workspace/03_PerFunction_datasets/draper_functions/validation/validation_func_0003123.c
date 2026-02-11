file_print_title (void)
{
	gchar *str;

	str = g_strdup_printf (_("%s - gnome-paint"), file_title);

	if (!b_saved)
	{
		gchar *copy;
		copy = g_strdup_printf ("%c%s", '*', str);
		g_free (str);
		str = copy;
	}

	gtk_window_set_title ( parent_window, str);

	g_free (str);
}
