select_matching_profile (GstLocationsCombo *combo)
{
  GstLocationsComboPrivate *priv;
  GtkTreeIter iter;
  gchar *current;
  gchar *profile;
  gboolean valid;

  priv = combo->_priv;
  valid = gtk_tree_model_get_iter_first (priv->model, &iter);
  current = gst_network_locations_get_current (GST_NETWORK_LOCATIONS (combo));

  while (valid)
    {
      gtk_tree_model_get (priv->model, &iter, 0, &profile, -1);

      if (profile && current && strcmp (profile, current) == 0)
	{
	  gtk_combo_box_set_active_iter (GTK_COMBO_BOX (priv->combo), &iter);
	  valid = FALSE;
	}
      else
	valid = gtk_tree_model_iter_next (priv->model, &iter);

      g_free (profile);
    }

  g_free (current);
}
