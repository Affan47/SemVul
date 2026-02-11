autosave_project (gpointer data)
{
  GladeProject *project = (GladeProject *)data;
  GladeWindow *window = GLADE_WINDOW (glade_app_get_window ());
  gchar *display_name;

  display_name = glade_project_get_name (project);

  if (glade_project_autosave (project, NULL))
    glade_util_flash_message (window->priv->statusbar,
			      window->priv->statusbar_actions_context_id,
			      _("Autosaving '%s'"), display_name);
  else

    glade_util_flash_message (window->priv->statusbar,
			      window->priv->statusbar_actions_context_id,
			      _("Error autosaving '%s'"), display_name);

  g_free (display_name);


  g_object_set_data (G_OBJECT (project), "glade-autosave-id", NULL);
  return FALSE;
}
