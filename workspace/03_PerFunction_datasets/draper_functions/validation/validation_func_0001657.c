create_clock(double x, double y, int value)
{
  GdkPixbuf   *pixmap = NULL;
  char	      *str = NULL;

  if(value<0)
    return;

  str = g_strdup_printf("%s%d.png", "timers/clock",value);

  pixmap = gc_skin_pixmap_load(str);

  clock_image_item = goo_canvas_image_new (boardRootItem,
					   pixmap,
					   x,
					   y,
					   NULL);

#if GDK_PIXBUF_MAJOR <= 2 && GDK_PIXBUF_MINOR <= 24
  gdk_pixbuf_unref(pixmap);
#else
  g_object_unref(pixmap);
#endif
  g_free(str);
}
