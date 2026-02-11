gm_audio_profile_choose_init (GMAudioProfileChoose *choose)
{
  GMAudioProfileChoosePrivate *priv;
  GtkListStore                *store;
  GList                       *orig,
			      *profiles;
  GtkCellRenderer             *cell;

  priv = G_TYPE_INSTANCE_GET_PRIVATE (choose,
				      GM_AUDIO_TYPE_PROFILE_CHOOSE,
				      GMAudioProfileChoosePrivate);


  store = gtk_list_store_new (N_COLUMNS, G_TYPE_STRING,
					 G_TYPE_STRING,
					 GM_AUDIO_TYPE_PROFILE);
  for (orig = profiles = gm_audio_profile_get_active_list ();
       profiles;
       profiles = g_list_next (profiles))
    {
      GMAudioProfile *profile = profiles->data;
      gchar          *profile_name,
		     *temp_file_name,
		     *mime_type_description;
      GtkTreeIter     iter;

      temp_file_name = g_strdup_printf (".%s", gm_audio_profile_get_extension (profile));
      mime_type_description = g_content_type_get_description (temp_file_name);
      g_free (temp_file_name);

      profile_name = g_strdup_printf (gettext ("%s (%s)"),
				      gm_audio_profile_get_name (profile),
				      mime_type_description);
      g_free (mime_type_description);
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
			  NAME_COLUMN, profile_name,
			  ID_COLUMN, gm_audio_profile_get_id (profile),
			  PROFILE_COLUMN, profile,
			  -1);

      g_signal_connect (profile, "forgotten",
			G_CALLBACK (audio_profile_forgotten), choose);

      g_free (profile_name);
    }
  g_list_free (orig);


  cell = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (choose), cell, TRUE );
  gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (choose), cell, "text", NAME_COLUMN);
  gtk_combo_box_set_model (GTK_COMBO_BOX (choose), GTK_TREE_MODEL (store));
  g_object_unref (store);


  priv->model   = GTK_TREE_MODEL (store);
  priv->profile = NULL;


  choose->priv = priv;
}
