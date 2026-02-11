init_pipeline_editor (GtkBuilder * dialog, GSTPPipelineEditor * editor)
{
  gchar *gconf_init_pipe = NULL;


  editor->optionmenu = create_pipeline_menu (dialog, editor);
  editor->entry = GTK_ENTRY (WID (editor->entry_name));
  editor->test_button = GTK_BUTTON (WID (editor->test_button_name));


  if (!(editor->entry && editor->optionmenu && editor->test_button))
    return;

  g_object_set_data (G_OBJECT (editor->optionmenu), pipeline_editor_property,
      (gpointer) (editor));
  g_signal_connect (G_OBJECT (editor->optionmenu), "changed",
      (GCallback) pipeline_option_changed, (gpointer) (editor));
  g_object_set_data (G_OBJECT (editor->entry), pipeline_editor_property,
      (gpointer) (editor));
  g_signal_connect (G_OBJECT (editor->entry), "changed",
      (GCallback) entry_changed, (gpointer) (editor));
  g_object_set_data (G_OBJECT (editor->test_button), pipeline_editor_property,
      (gpointer) (editor));
  g_signal_connect (G_OBJECT (editor->test_button), "clicked",
      (GCallback) test_button_clicked, (gpointer) (editor));

  gconf_init_pipe = gst_properties_gconf_get_string (editor->gconf_key);

  if (gconf_init_pipe) {
    update_from_gconf (editor, gconf_init_pipe);
    g_free (gconf_init_pipe);
  }
}
