update_document_ui_save_items (AnjutaPlugin *plugin, IAnjutaDocument *doc)
{
	AnjutaUI *ui;
	GtkAction *action;

	ui = anjuta_shell_get_ui (plugin->shell, NULL);

	if (anjuta_docman_get_current_document (ANJUTA_DOCMAN(ANJUTA_PLUGIN_DOCMAN(plugin)->docman)) ==
		doc)
	{
		action = anjuta_ui_get_action (ui, "ActionGroupEditorFile",
		                               "ActionFileSave");
		g_object_set (G_OBJECT (action), "sensitive",
		              ianjuta_file_savable_is_dirty(IANJUTA_FILE_SAVABLE(doc), NULL),
		              NULL);
	}
}
