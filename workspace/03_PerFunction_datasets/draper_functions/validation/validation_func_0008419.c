viewer_event_cb (GtkWidget    *widget,
	         GdkEvent     *event,
	         GthSlideshow *self)
{
	if (event->type == GDK_MOTION_NOTIFY) {
		gth_image_viewer_show_cursor (GTH_IMAGE_VIEWER (self->priv->viewer));
		if (self->priv->hide_cursor_event != 0)
			g_source_remove (self->priv->hide_cursor_event);
		self->priv->hide_cursor_event = g_timeout_add_seconds (HIDE_CURSOR_DELAY, hide_cursor_cb, self);
	}
	else if (event->type == GDK_BUTTON_PRESS) {
		switch (((GdkEventButton *) event)->button) {
		case 1:
			_gth_slideshow_load_next_image (self);
			break;
		case 3:
			_gth_slideshow_load_prev_image (self);
			break;
		default:
			break;
		}
	}
	else if (event->type == GDK_KEY_PRESS) {
		switch (((GdkEventKey *) event)->keyval) {
		case GDK_KEY_F5:
			_gth_slideshow_close (self);
			break;
		}
	}
	else if (event->type == GDK_KEY_RELEASE) {
		switch (((GdkEventKey *) event)->keyval) {
		case GDK_KEY_Escape:
		case GDK_KEY_q:
			_gth_slideshow_close (self);
			break;
		case GDK_KEY_p:
			_gth_slideshow_toggle_pause (self);
			break;

		case GDK_KEY_space:
		case GDK_KEY_Down:
		case GDK_KEY_Right:
		case GDK_KEY_Page_Down:
			if (self->priv->paused)
				_gth_slideshow_toggle_pause (self);
			else
				_gth_slideshow_load_next_image (self);
			break;

		case GDK_KEY_BackSpace:
		case GDK_KEY_Up:
		case GDK_KEY_Left:
		case GDK_KEY_Page_Up:
			_gth_slideshow_load_prev_image (self);
			break;
		}
	}
}
