image_put_and_destroy (Display* dpy, Drawable drawable, GC gcontext,
                                   XImage* im, int src_x, int src_y,
                                   int x, int y, unsigned int w, unsigned int h)
{
  begin_x_call();
  XPutImage (dpy, drawable, gcontext, im, src_x, src_y, x,y,w,h);
  XDestroyImage (im);
  end_x_call();
  dprintf (("\nXPutImage (.., src_x=%d, src_y=%d, x=%d,y=%d,w=%d,h=%d);",
            src_x, src_y, x,y,w,h));
}
