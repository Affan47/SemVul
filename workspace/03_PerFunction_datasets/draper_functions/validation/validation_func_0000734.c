parent_filter_map (GdkXEvent *xevent,
    GdkEvent *event, gpointer user_data)
{
  XEvent *xev = (XEvent *)xevent;

  if (xev->xany.type == MapNotify) {

   if (debug) printf ("map notify\n");

   gtk_main_quit();

  }

  return GDK_FILTER_CONTINUE;
}
