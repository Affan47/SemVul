profile_combo_box_get_selected (GtkWidget *widget)
{
  GtkComboBox *combo = GTK_COMBO_BOX (widget);
  TerminalProfile *profile = NULL;
  GtkTreeIter iter;

  if (gtk_combo_box_get_active_iter (combo, &iter))
    gtk_tree_model_get (gtk_combo_box_get_model (combo), &iter,
                        (int) COL_PROFILE, &profile, (int) -1);

  return profile;
}
