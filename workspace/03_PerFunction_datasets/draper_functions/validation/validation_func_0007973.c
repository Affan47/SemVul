selectByPairMethod(GtkComboBox *combo, VisuPairExtension *meth)
{
  GtkTreeModel *model;
  GtkTreeIter iter;
  gboolean valid;
  VisuPairExtension *meth_;

  model = gtk_combo_box_get_model(combo);
  valid = gtk_tree_model_get_iter_first(model, &iter);
  while (valid)
    {
      gtk_tree_model_get(model, &iter,
			 GTK_PAIRS_COLUMN_PAIRS_POINTER, &meth_, -1);
      if (meth_ == meth)
	{
	  gtk_combo_box_set_active_iter(combo, &iter);
	  valid = FALSE;
	}
      else
	valid = gtk_tree_model_iter_next(model, &iter);
    }
}
