static void XDrawBeveledMatte(Display *display,const XWindowInfo *window_info,
  const XWidgetInfo *matte_info)
{


  XDrawBevel(display,window_info,matte_info);
  XDrawMatte(display,window_info,matte_info);
}
