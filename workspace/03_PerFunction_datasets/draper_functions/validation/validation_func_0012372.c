SetCursor(Cursor curs) {


	if (curs == cursorLast)
		return;

	cursorLast = curs;
	GdkCursor *gdkCurs;
	switch (curs) {
	case cursorText:
		gdkCurs = gdk_cursor_new(GDK_XTERM);
		break;
	case cursorArrow:
		gdkCurs = gdk_cursor_new(GDK_LEFT_PTR);
		break;
	case cursorUp:
		gdkCurs = gdk_cursor_new(GDK_CENTER_PTR);
		break;
	case cursorWait:
		gdkCurs = gdk_cursor_new(GDK_WATCH);
		break;
	case cursorHand:
		gdkCurs = gdk_cursor_new(GDK_HAND2);
		break;
	case cursorReverseArrow:
		gdkCurs = gdk_cursor_new(GDK_RIGHT_PTR);
		break;
	default:
		gdkCurs = gdk_cursor_new(GDK_LEFT_PTR);
		cursorLast = cursorArrow;
		break;
	}

	if (WindowFromWidget(PWidget(wid)))
		gdk_window_set_cursor(WindowFromWidget(PWidget(wid)), gdkCurs);
#if GTK_CHECK_VERSION(3,0,0)
	g_object_unref(gdkCurs);
#else
	gdk_cursor_unref(gdkCurs);
#endif
}
