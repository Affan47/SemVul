wait_for_indi_cb(gpointer data)
{
	GtkWidget *window = data;
	GtkWidget *gwindow;
	struct camera_t *camera;
	struct tele_t *tele;

	tele = tele_find(window);
	if (! tele)
		tele = (void *)1;
	camera = camera_find(window, CAMERA_GUIDE);
	if (tele && camera) {
		gwindow = gtk_object_get_data(GTK_OBJECT(window), "guide_window");
		gtk_widget_set_sensitive(
			GTK_WIDGET(gtk_object_get_data(GTK_OBJECT(gwindow), "guide_calibrate")),
			TRUE);
		gtk_widget_set_sensitive(
			GTK_WIDGET(gtk_object_get_data(GTK_OBJECT(gwindow), "guide_run")),
			TRUE);
		return FALSE;
	}
	return TRUE;
}
