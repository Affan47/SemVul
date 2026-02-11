key_pressed(GtkWidget *widget, GdkEventKey *event,
			MessageView *messageview)
{
	if (event && event->keyval == GDK_KEY_Escape && messageview->window) {
		messageview_destroy(messageview);
		return TRUE;
	}

	if (event && (event->state & (GDK_MOD1_MASK|GDK_CONTROL_MASK)) != 0)
		return FALSE;
	if (event && (event->state & GDK_SHIFT_MASK) && event->keyval != GDK_KEY_space)
		return FALSE;

	return mimeview_pass_key_press_event(messageview->mimeview, event);
}
