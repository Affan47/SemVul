panel_menu_button_load (PanelWidget *panel,
			const char  *id,
			GSettings   *settings)
{
	GSettings    *settings_instance;
	char         *scheme;
	MenuPathRoot  root;
	char         *menu_path;
	char         *custom_icon;
	char         *tooltip;

	settings_instance = panel_layout_get_instance_settings (settings,
								PANEL_MENU_BUTTON_SCHEMA);

	menu_path = g_settings_get_string (settings_instance,
					   PANEL_MENU_BUTTON_MENU_PATH_KEY);
	custom_icon = g_settings_get_string (settings_instance,
					     PANEL_MENU_BUTTON_CUSTOM_ICON_KEY);
	tooltip = g_settings_get_string (settings_instance,
					 PANEL_MENU_BUTTON_TOOLTIP_KEY);

	if (!PANEL_GLIB_STR_EMPTY (menu_path)) {
		scheme = g_strndup (menu_path, strcspn (menu_path, ":"));
		root = panel_menu_scheme_to_path_root (scheme);
		g_free (scheme);
	} else
		root = APPLICATIONS_MENU;

	if (root == LAST_MENU) {
		g_printerr ("Unknown menu scheme, cannot load menu button\n");

		g_free (menu_path);
		g_free (custom_icon);
		g_free (tooltip);
		g_object_unref (settings_instance);

		return;
	}

	panel_menu_button_load_helper (menu_path,
				       custom_icon,
				       tooltip,
				       panel,
				       id,
				       settings);

	g_free (menu_path);
	g_free (custom_icon);
	g_free (tooltip);

	g_object_unref (settings_instance);
}
