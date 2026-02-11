command_radio_toggle(void)
{
	GtkWidget *run_command_radio = GTK_WIDGET (gtk_builder_get_object (gxml, "radiobutton5"));
	GtkWidget *run_command_entry = GTK_WIDGET (gtk_builder_get_object (gxml, "command_entry"));
	GtkWidget *run_script_entry = GTK_WIDGET (gtk_builder_get_object (gxml, "script_entry"));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(run_command_radio)))
	{
		gtk_widget_set_sensitive(GTK_WIDGET(run_command_entry), TRUE);
		gtk_widget_set_sensitive(GTK_WIDGET(run_script_entry), FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(GTK_WIDGET(run_command_entry), FALSE);
		gtk_widget_set_sensitive(GTK_WIDGET(run_script_entry), TRUE);
	}
}
