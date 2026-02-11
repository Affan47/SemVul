debugger_add_breakpoint_at_line (Debugger *debugger, const gchar *file, guint line, IAnjutaDebuggerBreakpointCallback callback, gpointer user_data)
{
	gchar *buff;
	gchar *quoted_file;

	DEBUG_PRINT ("%s", "In function: debugger_add_breakpoint()");

	g_return_if_fail (IS_DEBUGGER (debugger));

	quoted_file = gdb_quote (file);
	buff = g_strdup_printf ("-break-insert %s \"\\\"%s\\\":%u\"",
							debugger->priv->has_pending_breakpoints ? "-f" : "",
							quoted_file, line);
	g_free (quoted_file);
	debugger_queue_command (debugger, buff, 0, debugger_add_breakpoint_finish, (IAnjutaDebuggerCallback)callback, user_data);
	g_free (buff);
}
