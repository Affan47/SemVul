get_label_wrap_width (EelEditableLabel *label)
{
  PangoLayout *layout;
  GtkStyleContext *style = gtk_widget_get_style_context (GTK_WIDGET (label));
  PangoFontDescription *desc;

  LabelWrapWidth *wrap_width = g_object_get_data (G_OBJECT (style), "gtk-label-wrap-width");
  if (!wrap_width)
    {
      wrap_width = g_new0 (LabelWrapWidth, 1);
      g_object_set_data_full (G_OBJECT (style), "gtk-label-wrap-width",
			      wrap_width, label_wrap_width_free);
    }

  gtk_style_context_get (style, gtk_widget_get_state_flags (GTK_WIDGET (label)),
                         GTK_STYLE_PROPERTY_FONT, &desc,
                         NULL);

  if (wrap_width->font_desc && pango_font_description_equal (wrap_width->font_desc, desc))
    goto out;

  if (wrap_width->font_desc)
    pango_font_description_free (wrap_width->font_desc);

  wrap_width->font_desc = pango_font_description_copy (desc);

  layout = gtk_widget_create_pango_layout (GTK_WIDGET (label),
					   "This long string gives a good enough length for any line to have.");
  pango_layout_get_size (layout, &wrap_width->width, NULL);
  g_object_unref (layout);

 out:
  pango_font_description_free (desc);

  return wrap_width->width;
}
