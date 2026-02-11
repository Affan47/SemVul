handle(int ev)
{
  if (parent()) {
    switch (ev) {
    case FL_SHOW:
      if (!shown()) show();
      else {
#if defined(USE_X11) || defined(WIN32)
        XMapWindow(fl_display, fl_xid(this));
#elif defined(__APPLE_QUARTZ__)
	i->map();
#else
# error unsupported platform
#endif
      }
      break;
    case FL_HIDE:
      if (shown()) {


	if (visible()) {
	 Fl_Widget* p = parent(); for (;p->visible();p = p->parent()) {}
	 if (p->type() >= FL_WINDOW) break;
	}
#if defined(USE_X11) || defined(WIN32)
	XUnmapWindow(fl_display, fl_xid(this));
#elif defined(__APPLE_QUARTZ__)
	i->unmap();
#else
# error platform unsupported
#endif
      }
      break;
    }


  }

  return Fl_Group::handle(ev);
}
