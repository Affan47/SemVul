ImageClassInit(ic, dpy)
ImageClass *ic;
Display *dpy;
{


  ic->icount = 0;
  ic->init = True;
  ic->gc = XCreateGC(dpy, RootWindow(dpy, DefaultScreen(dpy)), 0, NULL);

  if (getenv("CHIMERA_MAX_SPECIAL_COLORS"))
  {
    ic->special_max = atoi(getenv("CHIMERA_MAX_SPECIAL_COLORS"));
  }
  else
  {
    ic->special_max = 64;
  }

  return;
}
