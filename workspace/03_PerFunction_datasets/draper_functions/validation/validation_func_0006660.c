device_changed (GdkDeviceManager *device_manager,
		GdkDevice        *device,
		GtkBuilder       *dialog)
{
	gboolean present;

	present = touchpad_is_present ();
	gtk_widget_set_visible (WID ("touchpad_vbox"), present);

	if (present) {
		changing_scroll = TRUE;
		synaptics_check_capabilities (dialog);
		setup_scrollmethod_radios (dialog);
		changing_scroll = FALSE;
	}

	present = mouse_is_present ();
	gtk_widget_set_visible (WID ("mouse_vbox"), present);
}
