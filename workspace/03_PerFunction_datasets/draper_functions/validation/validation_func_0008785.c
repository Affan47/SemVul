handle_button_press_event (GtkWidget *popup,
			   Display *display,
			   Window subwindow)
{
	Window window;

	remove_popup (popup);

	if (subwindow == None)
		return;

	if (wm_state_atom == None)
		wm_state_atom = XInternAtom (display, "WM_STATE", FALSE);

	window = find_managed_window (display, subwindow);

	if (window != None) {
		if (!gdk_x11_window_lookup_for_display (gdk_x11_lookup_xdisplay (display), window))
			kill_window_question ((gpointer) window);
	}
}
