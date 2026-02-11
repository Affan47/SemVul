populate_connection_ui (NMConnectionEditor *editor)
{
	NMSettingConnection *s_con;
	GtkWidget *name;

	name = GTK_WIDGET (gtk_builder_get_object (editor->builder, "connection_name"));

	s_con = nm_connection_get_setting_connection (editor->connection);
	gtk_entry_set_text (GTK_ENTRY (name), s_con ? nm_setting_connection_get_id (s_con) : NULL);
	gtk_widget_set_tooltip_text (name, nm_connection_get_uuid (editor->connection));

	g_signal_connect_swapped (name, "changed", G_CALLBACK (connection_editor_validate), editor);

	connection_editor_validate (editor);
}
