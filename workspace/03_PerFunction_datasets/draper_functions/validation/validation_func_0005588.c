debugger_queue_set_next_command (Debugger *debugger)
{
	DebuggerCommand *dc;

	DEBUG_PRINT ("%s", "In function: debugger_set_next_command()");

	dc = debugger_queue_get_next_command (debugger);
	if (!dc)
	{
		debugger->priv->current_cmd.cmd = NULL;
		debugger->priv->current_cmd.parser = NULL;
		debugger->priv->current_cmd.callback = NULL;
		debugger->priv->current_cmd.user_data = NULL;
		debugger->priv->current_cmd.flags = 0;

		return FALSE;
	}
	g_free (debugger->priv->current_cmd.cmd);
	debugger->priv->current_cmd.cmd = dc->cmd;
	debugger->priv->current_cmd.parser = dc->parser;
	debugger->priv->current_cmd.callback = dc->callback;
	debugger->priv->current_cmd.user_data = dc->user_data;
	debugger->priv->current_cmd.flags = dc->flags;
	g_free (dc);

	return TRUE;
}
