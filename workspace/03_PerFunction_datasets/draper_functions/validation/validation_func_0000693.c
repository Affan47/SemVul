set_func_args (const GDBMIValue *frame_hash, GList** node)
{
	const gchar *level;
	const GDBMIValue *literal, *args_list, *arg_hash;
	gint i;
	GString *args_str;
	IAnjutaDebuggerFrame* frame;

	literal = gdbmi_value_hash_lookup (frame_hash, "level");
	if (!literal)
		return;

	level = gdbmi_value_literal_get (literal);
	if (!level)
		return;

	frame = (IAnjutaDebuggerFrame *)(*node)->data;

	args_list = gdbmi_value_hash_lookup (frame_hash, "args");
	if (args_list)
	{
		args_str = g_string_new ("(");
		for (i = 0; i < gdbmi_value_get_size (args_list); i++)
		{
			const gchar *name, *value;

			arg_hash = gdbmi_value_list_get_nth (args_list, i);
			if (!arg_hash)
				continue;

			literal = gdbmi_value_hash_lookup (arg_hash, "name");
			if (!literal)
				continue;
			name = gdbmi_value_literal_get (literal);
			if (!name)
				continue;

			literal = gdbmi_value_hash_lookup (arg_hash, "value");
			if (!literal)
				continue;
			value = gdbmi_value_literal_get (literal);
			if (!value)
				continue;
			args_str = g_string_append (args_str, name);
			args_str = g_string_append (args_str, "=");
			args_str = g_string_append (args_str, value);
			if (i < (gdbmi_value_get_size (args_list) - 1))
				args_str = g_string_append (args_str, ", ");
		}
		args_str = g_string_append (args_str, ")");
		frame->args = args_str->str;
		g_string_free (args_str, FALSE);
	}
	*node = g_list_next (*node);
}
