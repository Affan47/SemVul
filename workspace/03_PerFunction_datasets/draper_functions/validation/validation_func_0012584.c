fl_init_workarea() {
  fl_open_display();

  Atom actual;
  unsigned long count, remaining;
  int format;
  unsigned *xywh;


  if (Fl::screen_count() > 1 || XGetWindowProperty(fl_display, RootWindow(fl_display, fl_screen),
			 fl_NET_WORKAREA, 0, 4 * sizeof(unsigned), False,
                         XA_CARDINAL, &actual, &format, &count, &remaining,
                         (unsigned char **)&xywh) || !xywh || !xywh[2] ||
                         !xywh[3])
  {
    Fl::screen_xywh(fl_workarea_xywh[0],
		    fl_workarea_xywh[1],
		    fl_workarea_xywh[2],
		    fl_workarea_xywh[3], 0);
  }
  else
  {
    fl_workarea_xywh[0] = (int)xywh[0];
    fl_workarea_xywh[1] = (int)xywh[1];
    fl_workarea_xywh[2] = (int)xywh[2];
    fl_workarea_xywh[3] = (int)xywh[3];
    XFree(xywh);
  }
}
