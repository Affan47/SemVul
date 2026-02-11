gpk_distro_upgrade_get_distro_upgrades_cb (PkClient *client, GAsyncResult *res, GpkDistroUpgradePrivate *priv)
{
	PkResults *results;
	GError *error = NULL;
	GPtrArray *array = NULL;
	PkError *error_code = NULL;
	guint i;
	PkDistroUpgrade *distro_upgrade;
	gboolean show_unstable;


	results = pk_client_generic_finish (client, res, &error);
	if (results == NULL) {

		gpk_error_dialog_modal (GTK_WINDOW (priv->assistant), _("Could not get distribution upgrades"), "", error->message);
		g_error_free (error);
		goto out;
	}


	error_code = pk_results_get_error_code (results);
	if (error_code != NULL) {
		g_warning ("failed to get upgrades: %s, %s", pk_error_enum_to_string (pk_error_get_code (error_code)), pk_error_get_details (error_code));
		gpk_error_dialog_modal (GTK_WINDOW (priv->assistant), gpk_error_enum_to_localised_text (pk_error_get_code (error_code)),
					gpk_error_enum_to_localised_message (pk_error_get_code (error_code)), pk_error_get_details (error_code));
		goto out;
	}


	gtk_list_store_clear (priv->distro_upgrade_store);


	array = pk_results_get_distro_upgrade_array (results);
	if (array->len == 0) {

		gpk_distro_upgrade_set_combobox_text (priv, _("No releases available for upgrade"));
		gtk_assistant_set_page_complete (GTK_ASSISTANT (priv->assistant), priv->page_choose_vbox, FALSE);
		goto out;
	}


	show_unstable = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->checkbutton));
	for (i=0; i<array->len; i++) {
		distro_upgrade = g_ptr_array_index (array, i);
		if (show_unstable ||
		    pk_distro_upgrade_get_state (distro_upgrade) == PK_DISTRO_UPGRADE_ENUM_STABLE) {
			gpk_distro_upgrade_add_item_to_list (priv, distro_upgrade);
		}
	}
	gtk_widget_set_sensitive (GTK_WIDGET (priv->combobox), TRUE);
	gtk_assistant_set_page_complete (GTK_ASSISTANT (priv->assistant), priv->page_choose_vbox, TRUE);
out:

	gtk_combo_box_set_active (GTK_COMBO_BOX (priv->combobox), 0);
	if (error_code != NULL)
		g_object_unref (error_code);
	if (array != NULL)
		g_ptr_array_unref (array);
	if (results != NULL)
		g_object_unref (results);
}
