dma_plugin_debugger_stopped (DebugManagerPlugin *self, GError *err)
{
	GtkAction *action;
	AnjutaStatus* state;

	DEBUG_PRINT ("%s", "DMA: dma_plugin_debugger_stopped");

	dma_plugin_program_unload (self);


	gtk_action_group_set_visible (self->start_group, TRUE);
	gtk_action_group_set_sensitive (self->start_group, TRUE);
	action = gtk_action_group_get_action (self->start_group, "ActionDebuggerStop");
	gtk_action_set_sensitive (action, FALSE);
	gtk_action_group_set_visible (self->loaded_group, TRUE);
	gtk_action_group_set_sensitive (self->loaded_group, FALSE);
	gtk_action_group_set_visible (self->stopped_group, TRUE);
	gtk_action_group_set_sensitive (self->stopped_group, FALSE);
	gtk_action_group_set_visible (self->running_group, TRUE);
	gtk_action_group_set_sensitive (self->running_group, FALSE);


	set_program_counter (self, NULL, 0, 0);

	state = anjuta_shell_get_status(ANJUTA_PLUGIN (self)->shell, NULL);
	anjuta_status_set_default (state, _("Debugger"), NULL);


	if (self->user_command_dialog) gtk_widget_destroy (GTK_WIDGET (self->user_command_dialog));


	if (err != NULL)
	{
		GtkWindow *parent = GTK_WINDOW (ANJUTA_PLUGIN(self)->shell);
		anjuta_util_dialog_error (parent, _("Debugger terminated with error %d: %s\n"), err->code, err->message);
	}

}
