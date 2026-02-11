prop_path_changed(GtkWidget *entry, property_t *prop)
{
  app_t      *app;
  const char *value;
  g_assert((entry != NULL) && (prop != NULL));
  g_assert(prop->apwal != NULL);
  g_assert(prop->apwal->selected_app != NULL);
  app = prop->apwal->selected_app;
  TRACE("app:%p", app);
  value = gtk_entry_get_text(GTK_ENTRY(entry));
  app_set_path(app, value);

  if (app_path_is_valid(app))
    gtk_widget_set_text_color_default(GTK_WIDGET(prop->entry_path));
  else
    gtk_widget_set_text_color_invalid(GTK_WIDGET(prop->entry_path));

  apwalapp_selected_app_modified(prop->apwal);
}
