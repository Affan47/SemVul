callbacks_window_key_press_event (GtkWidget *widget, GdkEventKey *event)
{
	switch (event->keyval) {
	case GDK_Escape:
		if (screen.tool == POINTER) {
			selection_clear (&screen.selectionInfo);
			update_selected_object_message (FALSE);
		}


		screen.state = NORMAL;
		render_refresh_rendered_image_on_screen();

		break;
	default:
		break;
	}

	return TRUE;
}
