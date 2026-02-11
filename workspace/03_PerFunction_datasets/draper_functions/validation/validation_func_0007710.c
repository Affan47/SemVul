on_preferences(G_GNUC_UNUSED GtkMenuItem *menuitem, G_GNUC_UNUSED gpointer user_data)
{
	PropertyDialogElements *e;
	gint response;
	gchar *project_dir;

	e = build_properties_dialog(TRUE);

	project_dir = g_path_get_dirname(g_current_project->path);
	gtk_entry_set_text(GTK_ENTRY(e->file_name), project_dir);
	gtk_entry_set_text(GTK_ENTRY(e->name), g_current_project->name);
	gtk_entry_set_text(GTK_ENTRY(e->base_path), g_current_project->base_path);
	gtk_combo_box_set_active(GTK_COMBO_BOX(e->type), g_current_project->type);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(e->regenerate),
				     g_current_project->regenerate);

	gtk_widget_show_all(e->dialog);

	response = gtk_dialog_run(GTK_DIALOG(e->dialog));
	if (response == GTK_RESPONSE_OK)
	{
		geany_project_set_base_path(g_current_project,
					    gtk_entry_get_text(GTK_ENTRY(e->base_path)));
		geany_project_set_name(g_current_project, gtk_entry_get_text(GTK_ENTRY(e->name)));
		geany_project_set_description(g_current_project, "");
		geany_project_set_run_cmd(g_current_project, "");
		geany_project_set_type_int(g_current_project,
					   gtk_combo_box_get_active(GTK_COMBO_BOX(e->type)));
		geany_project_set_regenerate(g_current_project,
					     gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON
									  (e->regenerate)));
		geany_project_save(g_current_project);

		if (g_current_project->regenerate)
		{
			geany_project_regenerate_file_list(g_current_project);
		}
		sidebar_refresh();
	}

	gtk_widget_destroy(e->dialog);
	g_free(e);
	g_free(project_dir);
}
