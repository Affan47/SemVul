gnac_profiles_utils_set_values_checked(BasicFormatInfo *bfi, ...)
{
  va_list ap;
  va_start(ap, bfi);

  const gchar *widget_name = va_arg(ap, const gchar *);

  while (widget_name) {
    gboolean active = FALSE;
    const gchar *checkbox_name = va_arg(ap, const gchar *);
    GtkWidget *widget = gnac_profiles_utils_get_widget(bfi, widget_name);

    if (GTK_IS_COMBO_BOX(widget)) {
      const gchar *value = va_arg(ap, const gchar *);
      if (value) {
        active = TRUE;
        gnac_profiles_utils_set_value_combo(widget, value);
      }
    } else if (GTK_IS_RANGE(widget)) {
      gdouble value = va_arg(ap, gdouble);
      if (value != -1) {
        active = TRUE;
        gtk_range_set_value(GTK_RANGE(widget), value);
      }
    } else {
      libgnac_debug("Unhandled widget type: %s",
          g_type_name(G_OBJECT_TYPE(widget)));
    }

    widget = gnac_profiles_utils_get_widget(bfi, checkbox_name);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), active);

    widget_name = va_arg(ap, const gchar *);
  }

  va_end(ap);
}
