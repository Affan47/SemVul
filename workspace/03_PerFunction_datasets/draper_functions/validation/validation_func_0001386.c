on_not_updated_command_finished (AnjutaCommand *command, guint return_code,
                                 GitStatusPane *self)
{
	if (g_hash_table_size (self->priv->diff_commands) > 0)
	{
		g_hash_table_foreach (self->priv->diff_commands,
		                      (GHFunc) anjuta_command_start, NULL);
	}
	else
		git_status_pane_set_model (self);
}
