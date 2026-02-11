compose_update_privacy_system_menu_item(Compose * compose, gboolean warn)
{
	static gchar *branch_path = "/Menu/Options/PrivacySystem";
	GtkWidget *menuitem = NULL;
	GList *children, *amenu;
	gboolean can_sign = FALSE, can_encrypt = FALSE;
	gboolean found = FALSE;

	if (compose->privacy_system != NULL) {
		gchar *systemid;
		menuitem = gtk_menu_item_get_submenu(GTK_MENU_ITEM(
				gtk_ui_manager_get_widget(compose->ui_manager, branch_path)));
		cm_return_if_fail(menuitem != NULL);

		children = gtk_container_get_children(GTK_CONTAINER(GTK_MENU_SHELL(menuitem)));
		amenu = children;
		menuitem = NULL;
		while (amenu != NULL) {
			systemid = g_object_get_data(G_OBJECT(amenu->data), "privacy_system");
			if (systemid != NULL) {
				if (strcmp(systemid, compose->privacy_system) == 0 &&
				    GTK_IS_CHECK_MENU_ITEM(amenu->data)) {
					menuitem = GTK_WIDGET(amenu->data);

					can_sign = privacy_system_can_sign(systemid);
					can_encrypt = privacy_system_can_encrypt(systemid);
					found = TRUE;
					break;
				}
			} else if (strlen(compose->privacy_system) == 0 &&
				   GTK_IS_CHECK_MENU_ITEM(amenu->data)) {
					menuitem = GTK_WIDGET(amenu->data);

					can_sign = FALSE;
					can_encrypt = FALSE;
					found = TRUE;
					break;
			}

			amenu = amenu->next;
		}
		g_list_free(children);
		if (menuitem != NULL)
			gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), TRUE);

		if (warn && !found && strlen(compose->privacy_system)) {
			alertpanel_warning(_("The privacy system '%s' cannot be loaded. You "
				  "will not be able to sign or encrypt this message."),
				  compose->privacy_system);
		}
	}

	cm_menu_set_sensitive_full(compose->ui_manager, "Menu/Options/Sign", can_sign);
	cm_menu_set_sensitive_full(compose->ui_manager, "Menu/Options/Encrypt", can_encrypt);
}
