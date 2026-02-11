get_cmap (GdkPixmap *pixmap)
{
  GdkColormap *cmap;

  cmap = gdk_drawable_get_colormap (pixmap);
  if (cmap)
    g_object_ref (G_OBJECT (cmap));

  if (cmap == NULL)
    {
      if (gdk_drawable_get_depth (pixmap) == 1)
        {

          cmap = NULL;
        }
      else
        {

          GdkScreen *screen = gdk_drawable_get_screen (GDK_DRAWABLE (pixmap));
          cmap = gdk_screen_get_system_colormap (screen);
          g_object_ref (G_OBJECT (cmap));
        }
    }


  if (cmap &&
      (gdk_colormap_get_visual (cmap)->depth !=
       gdk_drawable_get_depth (pixmap)))
    cmap = NULL;

  return cmap;
}
