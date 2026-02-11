visu_ui_color_combobox_setSelection(VisuUiColorCombobox* colorComboBox, ToolColor *color)
{
  GtkTreeIter iter;
  gboolean validIter;
  GObjectClass *klass;
  GtkListStore *model;
  ToolColor *tmpColor;

  g_return_val_if_fail(color && VISU_UI_IS_COLOR_COMBOBOX(colorComboBox), FALSE);

  DBG_fprintf(stderr, "Gtk VisuUiColorCombobox: select a new color %p.\n", (gpointer)color);
  klass = G_OBJECT_GET_CLASS(colorComboBox);
  model = GTK_LIST_STORE(VISU_UI_COLOR_COMBOBOX_CLASS(klass)->listStoredColors);
  validIter = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter);
  while (validIter)
    {
      gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,
			 COLUMN_COLOR_POINTER_TO, &tmpColor,
			 -1);
      if (tmpColor && tool_color_equal(tmpColor, color))
	{
	  gtk_combo_box_set_active_iter(GTK_COMBO_BOX(colorComboBox), &iter);
	  return TRUE;
	}
      validIter = gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter);
    }
  return FALSE;
}
