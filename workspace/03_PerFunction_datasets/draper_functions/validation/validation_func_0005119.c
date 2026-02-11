grab_mouse (saver_info *si, Window w, Cursor cursor, int screen_no)
{
  saver_preferences *p = &si->prefs;
  int status = XGrabPointer (si->dpy, w, True, ALL_POINTER_EVENTS,
			     GrabModeAsync, GrabModeAsync, w,
			     cursor, CurrentTime);
  if (status == GrabSuccess)
    {
      si->mouse_grab_window = w;
      si->mouse_grab_screen = screen_no;
    }

  if (p->verbose_p)
    fprintf(stderr, "%s: %d: grabbing mouse on 0x%lx... %s.\n",
	    blurb(), screen_no, (unsigned long) w, grab_string(status));
  return status;
}
