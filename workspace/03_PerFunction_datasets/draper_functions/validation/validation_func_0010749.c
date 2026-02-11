draw_label (char *txt, gdouble posx, gdouble posy)
{
  gint width, height;
  gint k, k2;

  if (!local_config.showpoilabel)
    {
      if (mydebug > 20)
	printf ("draw_label: drawing of label is disabled\n");
      return;
    }

  if (mydebug > 30)
    fprintf (stderr, "draw_label(%s,%g,%g)\n", txt, posx, posy);

  gdk_gc_set_foreground (kontext_map, &colors.textback);

  poi_label_layout = gtk_widget_create_pango_layout (map_drawingarea, txt);
  pfd = pango_font_description_from_string ("Sans 8");
  if (poi_list_count > 200)
    pfd = pango_font_description_from_string ("Sans 6");

  pango_layout_set_font_description (poi_label_layout, pfd);
  pango_layout_get_pixel_size (poi_label_layout, &width, &height);
  k = width + 4;
  k2 = height;

  gdk_gc_set_function (kontext_map, GDK_COPY);

  gdk_gc_set_function (kontext_map, GDK_AND);

  {

    gdk_gc_set_foreground (kontext_map, &colors.darkgrey);
    gdk_draw_rectangle (drawable, kontext_map, 1,
                        posx + 13, posy - k2 / 2, k + 1, k2);

  }

  poi_label_layout = gtk_widget_create_pango_layout (map_drawingarea, txt);
  pango_layout_set_font_description (poi_label_layout, pfd);

  gdk_draw_layout_with_colors (drawable, kontext_map,
                               posx + 15, posy - k2 / 2,
                               poi_label_layout, &colors.lightgrey, NULL);
  if (poi_label_layout != NULL)
    g_object_unref (G_OBJECT (poi_label_layout));

  pango_font_description_free (pfd);
}
