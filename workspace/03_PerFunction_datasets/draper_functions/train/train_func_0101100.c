pr_mouse_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	PixbufRenderer *pr;
	GtkWidget *parent;

	pr = PIXBUF_RENDERER(widget);

	if (pr->scroller_id) return TRUE;

	switch (bevent->button)
		{
		case MOUSE_BUTTON_LEFT:
			pr->in_drag = TRUE;
			pr->drag_last_x = bevent->x;
			pr->drag_last_y = bevent->y;
			pr->drag_moved = 0;
			gdk_pointer_grab(widget->window, FALSE,
					 GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK | GDK_BUTTON_RELEASE_MASK,
					 NULL, NULL, bevent->time);
			gtk_grab_add(widget);
			break;
		case MOUSE_BUTTON_MIDDLE:
			pr->drag_moved = 0;
			break;
		case MOUSE_BUTTON_RIGHT:
			pr_clicked_signal(pr, bevent);
			break;
		default:
			break;
		}

	parent = gtk_widget_get_parent(widget);
#if GTK_CHECK_VERSION(2,20,0)
	if (widget && gtk_widget_get_can_focus(parent))
#else
	if (widget && GTK_WIDGET_CAN_FOCUS(parent))
#endif
		{
		gtk_widget_grab_focus(parent);
		}

	return FALSE;
}
