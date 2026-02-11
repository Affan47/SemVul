handle_gsettings_settings (GSearchWindow * gsearch)
{
	if (g_settings_get_boolean (gsearch->gnome_search_tool_settings, "show-additional-options")) {
		if (gtk_widget_get_visible (gsearch->available_options_vbox) == FALSE) {
			gtk_expander_set_expanded (GTK_EXPANDER (gsearch->show_more_options_expander), TRUE);
			gtk_widget_show (gsearch->available_options_vbox);
		}
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "contains-the-text")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_CONTAINS_THE_TEXT, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "date-modified-less-than")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_DATE_MODIFIED_BEFORE, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "date-modified-more-than")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_DATE_MODIFIED_AFTER, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "size-at-least")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_SIZE_IS_MORE_THAN, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "size-at-most")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_SIZE_IS_LESS_THAN, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "file-is-empty")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_FILE_IS_EMPTY, NULL, FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "owned-by-user")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_OWNED_BY_USER, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "owned-by-group")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_OWNED_BY_GROUP, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "owner-is-unrecognized")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_OWNER_IS_UNRECOGNIZED, NULL, FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "name-does-not-contain")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_FILE_IS_NOT_NAMED, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "name-matches-regular-expression")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_FILE_MATCHES_REGULAR_EXPRESSION, "", FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "show-hidden-files-and-folders")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_SHOW_HIDDEN_FILES_AND_FOLDERS, NULL, FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "follow-symbolic-links")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_FOLLOW_SYMBOLIC_LINKS, NULL, FALSE);
	}

	if (g_settings_get_boolean (gsearch->gnome_search_tool_select_settings, "exclude-other-filesystems")) {
		add_constraint (gsearch, SEARCH_CONSTRAINT_SEARCH_OTHER_FILESYSTEMS, NULL, FALSE);
	}
}
