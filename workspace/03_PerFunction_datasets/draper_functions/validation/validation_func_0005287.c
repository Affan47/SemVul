pan_cursor(GtkWidget *window)
{
	GtkWidget *image;
	int x, y, w, h;
	GdkModifierType mask;

	image = gtk_object_get_data(GTK_OBJECT(window), "image");

	if (image == NULL) {
		err_printf("no image\n");
		return;
	}
	if (image->window) {
		gdk_window_get_pointer(image->window, &x, &y, &mask);
		gdk_window_get_size(image->window, &w, &h);

		set_scrolls(window, 1.0 * x / w, 1.0 * y / h);
	}
}
