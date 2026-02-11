basic_scan_monitors (Display *dpy, char **errP)
{
  int nscreens = ScreenCount (dpy);
  int i;
  monitor **monitors = (monitor **) calloc (nscreens + 1, sizeof(*monitors));
  if (!monitors) return 0;

  for (i = 0; i < nscreens; i++)
    {
      Screen *screen = ScreenOfDisplay (dpy, i);
      monitor *m = (monitor *) calloc (1, sizeof (monitor));
      monitors[i] = m;
      m->id       = i;
      m->screen   = screen;
      m->x        = 0;
      m->y        = 0;
      m->width    = WidthOfScreen (screen);
      m->height   = HeightOfScreen (screen);
    }
  return monitors;
}
