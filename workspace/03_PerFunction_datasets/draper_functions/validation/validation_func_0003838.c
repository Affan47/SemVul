img_changed_cb( GtkWidget *widget, gpointer data )
{
	GtkWidget *main_window = gtk_object_get_data(GTK_OBJECT(data), "image_window");
	long *disable_signals = gtk_object_get_data(GTK_OBJECT(data), "disable_signals");
	struct camera_t *camera = camera_find(main_window, CAMERA_MAIN);
	if(! camera) {
		err_printf("no camera connected\n");
		return;
	}
	if (! disable_signals)
		set_exp_from_img_dialog(camera, GTK_WIDGET(data));
}
