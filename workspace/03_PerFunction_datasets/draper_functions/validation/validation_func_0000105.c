wm_state_set (Display *display,
	      Window   window)
{
	gulong  nitems;
	gulong  bytes_after;
	gulong *prop;
	Atom    ret_type = None;
	int     ret_format;
	int     result;

	gdk_error_trap_push ();
	result = XGetWindowProperty (display, window, wm_state_atom,
				     0, G_MAXLONG, False, wm_state_atom,
				     &ret_type, &ret_format, &nitems,
				     &bytes_after, (gpointer) &prop);

	if (gdk_error_trap_pop ())
		return FALSE;

	if (result != Success)
		return FALSE;

	XFree (prop);

	if (ret_type != wm_state_atom)
		return FALSE;

	return TRUE;
}
