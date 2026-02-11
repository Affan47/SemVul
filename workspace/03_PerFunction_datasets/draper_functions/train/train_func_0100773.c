moire2_init_1 (struct state *st)
{
  XWindowAttributes xgwa;
  XGetWindowAttributes (st->dpy, st->window, &xgwa);

  st->othickness = get_integer_resource(st->dpy, "thickness", "Thickness");

  if (mono_p)
    st->ncolors = 2;
  else
    st->ncolors = get_integer_resource (st->dpy, "colors", "Colors");
  if (st->ncolors < 2) st->ncolors = 2;
  if (st->ncolors <= 2) mono_p = True;

  if (mono_p)
    st->colors = 0;
  else
    st->colors = (XColor *) malloc(sizeof(*st->colors) * (st->ncolors+1));

  if (mono_p)
    ;
  else
    make_smooth_colormap (xgwa.screen, xgwa.visual, xgwa.colormap,
                          st->colors, &st->ncolors,
			  True, 0, True);

  st->bg_pixel = get_pixel_resource(st->dpy,
				xgwa.colormap, "background", "Background");
  st->fg_pixel = get_pixel_resource(st->dpy,
				xgwa.colormap, "foreground", "Foreground");

#ifdef HAVE_DOUBLE_BUFFER_EXTENSION
  st->back_buf = xdbe_get_backbuffer (st->dpy, st->window, XdbeUndefined);
#endif
}
