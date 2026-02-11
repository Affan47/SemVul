allow_sticky_processes_only (ExecuteData *exec_data)
{
	FrProcess *process = exec_data->process;

	if (! process->priv->sticky_only) {


		exec_data->error_command = process->priv->current_command;
		exec_data->first_error = fr_error_copy (exec_data->error);
		exec_data->first_error_stdout = g_list_reverse (_g_string_list_dup (process->out.raw));
		exec_data->first_error_stderr = g_list_reverse (_g_string_list_dup (process->err.raw));
	}

	process->priv->sticky_only = TRUE;

	if (! process->priv->stopping)
		g_signal_emit (G_OBJECT (process),
			       fr_process_signals[STICKY_ONLY],
			       0);
}
