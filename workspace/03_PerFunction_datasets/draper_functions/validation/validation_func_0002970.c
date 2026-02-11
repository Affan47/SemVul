mouse_press
	(
	GdkEventButton *event
	)
	{
	dragging = false;
	if (event->button != 1)
		return FALSE;

	int mx = (int) event->x, my = (int) event->y;
	int draww = draw->allocation.width,
	    drawh = draw->allocation.height;

	if (((GdkEvent *) event)->type == GDK_2BUTTON_PRESS)
		{
		goto_mouse(mx, my);
		return TRUE;
		}

	if (mx < viewbox.x - 3 || my < viewbox.y - 3 ||
	    mx > viewbox.x + viewbox.width + 6 ||
	    my > viewbox.y + viewbox.height + 6)
		return FALSE;
	dragging = true;
	drag_relx = mx - viewbox.x;
	drag_rely = my - viewbox.y;
	return (TRUE);
	}
