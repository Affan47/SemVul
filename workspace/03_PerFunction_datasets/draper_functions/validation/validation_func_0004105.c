recheck_initialization (NMConnectionEditor *editor)
{
	GtkNotebook *notebook;

	if (!editor_is_initialized (editor) || editor->init_run)
		return;

	editor->init_run = TRUE;

	populate_connection_ui (editor);


	notebook = GTK_NOTEBOOK (gtk_builder_get_object (editor->builder, "notebook"));
	gtk_notebook_set_current_page (notebook, 1);


	nm_connection_editor_present (editor);


	if (editor->validate_id)
		g_source_remove (editor->validate_id);
	editor->validate_id = g_idle_add (idle_validate, editor);
}
