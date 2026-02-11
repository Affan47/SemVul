glade_placeholder_class_init (GladePlaceholderClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  gchar *path;
  cairo_surface_t *surface;

  object_class->finalize = glade_placeholder_finalize;
  object_class->set_property = glade_placeholder_set_property;
  object_class->get_property = glade_placeholder_get_property;

  widget_class->realize = glade_placeholder_realize;
  widget_class->unrealize = glade_placeholder_unrealize;
  widget_class->map = glade_placeholder_map;
  widget_class->unmap = glade_placeholder_unmap;
  widget_class->size_allocate = glade_placeholder_size_allocate;
  widget_class->draw = glade_placeholder_draw;
  widget_class->motion_notify_event = glade_placeholder_motion_notify_event;
  widget_class->button_press_event = glade_placeholder_button_press;
  widget_class->popup_menu = glade_placeholder_popup_menu;


  g_object_class_override_property (object_class, PROP_HADJUSTMENT,
                                    "hadjustment");
  g_object_class_override_property (object_class, PROP_VADJUSTMENT,
                                    "vadjustment");
  g_object_class_override_property (object_class, PROP_HSCROLL_POLICY,
                                    "hscroll-policy");
  g_object_class_override_property (object_class, PROP_VSCROLL_POLICY,
                                    "vscroll-policy");


  path = g_build_filename (glade_app_get_pixmaps_dir (), "placeholder.png", NULL);
  surface = cairo_image_surface_create_from_png (path);

  if (!surface)
    g_warning ("Failed to create surface for %s\n", path);
  else
    {
      placeholder_pattern = cairo_pattern_create_for_surface (surface);
      cairo_pattern_set_extend (placeholder_pattern, CAIRO_EXTEND_REPEAT);
    }
  g_free (path);

  g_type_class_add_private (klass, sizeof (GladePlaceholderPrivate));
}
