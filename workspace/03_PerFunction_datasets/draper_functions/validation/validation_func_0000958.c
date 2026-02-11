update_from_gconf (GSTPPipelineEditor * editor, const gchar * pipeline_str)
{


  int i = 0;
  gint custom_desc = -1;


  gchar **pipeline_nodes = g_strsplit (pipeline_str, " ", -1);
  gchar *pipeline_device = NULL;
  if (pipeline_nodes == NULL) {
    pipeline_nodes[0] = (gchar*)pipeline_str;
    pipeline_device = pipeline_nodes[1];
  }

  editor->cur_pipeline_index = -1;
  for (i = 0; i < editor->n_pipeline_desc; i++) {
    GSTPPipelineDescription *pipeline_desc = editor->pipeline_desc + i;

    if (pipeline_desc->is_custom == TRUE) {
      custom_desc = i;
    } else if (!strcmp (gst_pipeline_string_from_desc (pipeline_desc), pipeline_str)) {
      editor->cur_pipeline_index = i;
      break;
    } else if (!strcmp (gst_pipeline_string_from_desc (pipeline_desc), pipeline_nodes[0])) {
      editor->cur_pipeline_index = i;
      pipeline_desc->device = gst_pipeline_string_get_property_value(pipeline_str, "device");
      break;
    }
  }

  if (editor->cur_pipeline_index < 0) {
    editor->cur_pipeline_index = custom_desc;
    if (custom_desc >= 0) {
      gtk_entry_set_text (editor->entry, pipeline_str);
      if (pipeline_str == NULL || *pipeline_str == '\0')
        gtk_widget_set_sensitive (GTK_WIDGET (editor->test_button), FALSE);
    }
  }

  if (editor->cur_pipeline_index >= 0) {
    GtkTreeModel *model = gtk_combo_box_get_model (editor->optionmenu);

    gtk_tree_model_foreach (model, set_menuitem_by_pipeline, editor);
    update_from_option (editor,
        editor->pipeline_desc + editor->cur_pipeline_index);
  }

  g_strfreev(pipeline_nodes);
}
