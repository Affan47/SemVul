not_clipped(int x, int y, int w, int h) {
  if (x+w <= 0 || y+h <= 0) return 0;
  Fl_Region r = rstack[rstackptr];
  if (!r) return 1;
#if defined (USE_X11)

  if (clip_to_short(x,y,w,h)) return 0;
  return XRectInRegion(r, x, y, w, h);
#elif defined(WIN32)
  RECT rect;
  if (Fl_Surface_Device::surface() != Fl_Display_Device::display_device()) {
    POINT pt[2] = { {x, y}, {x + w, y + h} };
    LPtoDP(fl_gc, pt, 2);
    rect.left = pt[0].x; rect.top = pt[0].y; rect.right = pt[1].x; rect.bottom = pt[1].y;
  } else {
    rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
  }
  return RectInRegion(r,&rect);
#elif defined(__APPLE_QUARTZ__)
  CGRect arg = fl_cgrectmake_cocoa(x, y, w, h);
  for (int i = 0; i < r->count; i++) {
    CGRect test = CGRectIntersection(r->rects[i], arg);
    if (!CGRectIsEmpty(test)) return 1;
  }
  return 0;
#else
# error unsupported platform
#endif
}
