login_get_dialog (EogPostasaPlugin *plugin)
{
	GtkBuilder *builder;
	GError *error = NULL;

	if (plugin->priv->login_dialog == NULL) {
		builder = gtk_builder_new ();
		gtk_builder_set_translation_domain (builder, GETTEXT_PACKAGE);
		gtk_builder_add_from_resource (builder, GTKBUILDER_CONFIG_FILE,
		                               &error);
		if (error != NULL) {
			g_warning ("Couldn't load Postasa configuration UI file:%d:%s", error->code, error->message);
			g_error_free (error);
		}


		plugin->priv->username_entry = GTK_ENTRY  (gtk_builder_get_object (builder, "username_entry"));
		plugin->priv->password_entry = GTK_ENTRY  (gtk_builder_get_object (builder, "password_entry"));
		plugin->priv->login_dialog   = GTK_DIALOG (gtk_builder_get_object (builder, "postasa_login_dialog"));
		plugin->priv->cancel_button  = GTK_BUTTON (gtk_builder_get_object (builder, "cancel_button"));
		plugin->priv->login_button   = GTK_BUTTON (gtk_builder_get_object (builder, "login_button"));
		plugin->priv->login_message  = GTK_LABEL  (gtk_builder_get_object (builder, "login_message"));

		g_object_unref (builder);

		g_signal_connect (G_OBJECT (plugin->priv->login_button),  "clicked", G_CALLBACK (picasaweb_login_cb),     plugin);
		g_signal_connect (G_OBJECT (plugin->priv->cancel_button), "clicked", G_CALLBACK (login_dialog_cancel_button_cb), plugin);
		g_signal_connect (G_OBJECT (plugin->priv->login_dialog), "delete-event", G_CALLBACK (login_dialog_delete_event_cb), plugin);

#ifdef HAVE_LIBGDATA_0_9
		if (gdata_service_is_authorized (GDATA_SERVICE (plugin->priv->service))) {
			gtk_entry_set_text (plugin->priv->username_entry, gdata_client_login_authorizer_get_username (plugin->priv->authorizer));
			gtk_entry_set_text (plugin->priv->password_entry, gdata_client_login_authorizer_get_password (plugin->priv->authorizer));
#else
		if (gdata_service_is_authenticated (GDATA_SERVICE (plugin->priv->service))) {
			gtk_entry_set_text (plugin->priv->username_entry, gdata_service_get_username (GDATA_SERVICE (plugin->priv->service)));
			gtk_entry_set_text (plugin->priv->password_entry, gdata_service_get_password (GDATA_SERVICE (plugin->priv->service)));
#endif
		}
	}

	return GTK_WIDGET (plugin->priv->login_dialog);
}
