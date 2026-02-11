debugger_read_memory_finish (Debugger *debugger, const GDBMIValue *mi_results, const GList *cli_results, GError *error)

{
	const GDBMIValue *literal;
	const GDBMIValue *mem;
	const gchar *value;
	gchar *data;
	gchar *ptr;
	gulong address;
	guint len;
	guint i;
	IAnjutaDebuggerCallback callback = debugger->priv->current_cmd.callback;
	gpointer user_data = debugger->priv->current_cmd.user_data;
	IAnjutaDebuggerMemoryBlock read = {0,};

	literal = gdbmi_value_hash_lookup (mi_results, "total-bytes");
	if (literal)
	{
		guint size;

		len = strtoul (gdbmi_value_literal_get (literal), NULL, 10);
		data = g_new (gchar, len * 2);
		memset (data + len, 0, len);

		literal = gdbmi_value_hash_lookup (mi_results, "addr");
		address = strtoul (gdbmi_value_literal_get (literal), NULL, 0);

		ptr = data;
		size = 0;
		mem = gdbmi_value_hash_lookup (mi_results, "memory");
		if (mem)
		{
			mem = gdbmi_value_list_get_nth (mem, 0);
			if (mem)
			{
				mem = gdbmi_value_hash_lookup (mem, "data");
				if (mem)
				{
					size = gdbmi_value_get_size (mem);
				}
			}
		}

		if (size < len) len = size;
		for (i = 0; i < len; i++)
		{
			literal = gdbmi_value_list_get_nth (mem, i);
			if (literal)
			{
				gchar *endptr;
				value = gdbmi_value_literal_get (literal);
				*ptr = strtoul (value, &endptr, 16);
				if ((*value != '\0') && (*endptr == '\0'))
				{

					ptr[len] = 1;
				}
				ptr++;
			}
		}
		read.address = address;
		read.length = len;
		read.data = data;
		callback (&read, user_data, NULL);

		g_free (data);
	}
	else
	{
		callback (NULL, user_data, NULL);
	}
}
