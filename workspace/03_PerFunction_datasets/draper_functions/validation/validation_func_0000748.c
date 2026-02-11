mx_image_pixbuf_new (const gchar  *filename,
                     guchar       *buffer,
                     gsize         count,
                     gint          width,
                     gint          height,
                     guint         width_threshold,
                     guint         height_threshold,
                     gboolean      upscale,
                     gboolean     *scaled,
                     GError      **error)
{
  GdkPixbuf *pixbuf;
  GdkPixbufLoader *loader;
  MxImageSizeRequest constraints;

  GError *err = NULL;

  loader = gdk_pixbuf_loader_new ();

  constraints.width = width;
  constraints.height = height;
  constraints.width_threshold = width_threshold;
  constraints.height_threshold = height_threshold;
  constraints.upscale = upscale;

  g_signal_connect (loader, "size-prepared",
                    G_CALLBACK (mx_image_size_prepared_cb),
                    &constraints);

  if (filename)
    {
      if (!g_file_get_contents (filename, (gchar **)&buffer, &count, &err))
        {
          if (error)
            g_propagate_error (error, err);
          gdk_pixbuf_loader_close (loader, NULL);
          g_object_unref (loader);
          return NULL;
        }

      g_object_weak_ref (G_OBJECT (loader), (GWeakNotify)g_free, buffer);
    }

  if (!buffer)
    {
      gdk_pixbuf_loader_close (loader, NULL);
      g_object_unref (loader);
      return NULL;
    }

  if (!gdk_pixbuf_loader_write (loader, buffer, count, &err))
    {
      if (error)
        g_propagate_error (error, err);
      gdk_pixbuf_loader_close (loader, NULL);
      g_object_unref (loader);
      return NULL;
    }


  if (!gdk_pixbuf_loader_close (loader, &err))
    {
      if (error)
        g_propagate_error (error, err);
      g_object_unref (loader);
      return NULL;
    }

  pixbuf = g_object_ref (gdk_pixbuf_loader_get_pixbuf (loader));

  g_object_unref (loader);

  if (scaled)
    *scaled = constraints.scaled;

  return pixbuf;
}
