image_loaded_cb (Screen *screen, Window window, Drawable pixmap,
                             const char *name, XRectangle *geometry,
                             void *closure)
{


  struct state *st = (struct state *) closure;
  int i;
  int this = -1;
  int next = -1;

  if (!st->image_loading_p) abort();
  st->image_loading_p = False;

  for (i = 0; i < MAX_STATIONS; i++) {
    if (! st->chansettings[i].image_loaded_p) {
      if (this == -1) this = i;
      else if (next == -1) next = i;
    }
  }
  if (this == -1) abort();


  {
    analogtv_input *input = st->stations[this];
    int width=ANALOGTV_PIC_LEN;
    int height=width*3/4;
    XImage *image = XGetImage (st->dpy, pixmap, 0, 0,
                               width, height, ~0L, ZPixmap);
    XFreePixmap(st->dpy, pixmap);

    analogtv_setup_sync(input, 1, (random()%20)==0);
    analogtv_load_ximage(st->tv, input, image);
    if (image) XDestroyImage(image);
    st->chansettings[this].image_loaded_p = True;
#if 0
    if (name) {
      const char *s = strrchr (name, '/');
      if (s) s++;
      else s = name;
      st->chansettings[this].filename = strdup (s);
    }
    fprintf(stderr, "%s: loaded channel %d, %s\n", progname, this,
            st->chansettings[this].filename);
#endif
  }


  if (next != -1)
    analogtv_load_random_image (st);
}
