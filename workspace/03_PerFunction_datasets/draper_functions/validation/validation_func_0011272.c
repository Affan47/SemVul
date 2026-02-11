close_window (Window window)
{

  XClientMessageEvent ev;


  if (debug) printf ("close window\n");

  ev.type = ClientMessage;

  ev.window = window;
  ev.message_type =net_close_window;
  ev.format = 32;
  ev.data.l[0] = 0;
  ev.data.l[1] = 0;
  ev.data.l[2] = 0;
  ev.data.l[3] =0;
  ev.data.l[4] = 0;

  gdk_error_trap_push ();
  XSendEvent (GDK_DISPLAY(), GDK_ROOT_WINDOW(), False,
  SubstructureNotifyMask | SubstructureRedirectMask, (XEvent *)&ev);
  gdk_error_trap_pop ();

}
