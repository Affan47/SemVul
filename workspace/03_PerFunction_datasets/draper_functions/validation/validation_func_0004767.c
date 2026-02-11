make_current() {
  static GC gc;
  if (!gc) gc = XCreateGC(fl_display, i->xid, 0, 0);
  fl_window = i->xid;
  fl_gc = gc;
  current_ = this;
  fl_clip_region(0);

#ifdef FLTK_USE_CAIRO

  if (Fl::cairo_autolink_context()) Fl::cairo_make_current(this);
#endif
}
