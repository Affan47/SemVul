update_pango_context (ClutterBackend *backend,
                      PangoContext   *context)
{
  ClutterSettings *settings;
  PangoFontDescription *font_desc;
  const cairo_font_options_t *font_options;
  gchar *font_name;
  PangoDirection pango_dir;
  gdouble resolution;

  settings = clutter_settings_get_default ();


  if (clutter_text_direction == CLUTTER_TEXT_DIRECTION_RTL)
    pango_dir = PANGO_DIRECTION_RTL;
  else
    pango_dir = PANGO_DIRECTION_LTR;

  pango_context_set_base_dir (context, pango_dir);

  g_object_get (settings, "font-name", &font_name, NULL);


  font_options = clutter_backend_get_font_options (backend);
  resolution = clutter_backend_get_resolution (backend);

  font_desc = pango_font_description_from_string (font_name);

  if (resolution < 0)
    resolution = 96.0;

  pango_context_set_font_description (context, font_desc);
  pango_cairo_context_set_font_options (context, font_options);
  pango_cairo_context_set_resolution (context, resolution);

  pango_font_description_free (font_desc);
  g_free (font_name);
}
