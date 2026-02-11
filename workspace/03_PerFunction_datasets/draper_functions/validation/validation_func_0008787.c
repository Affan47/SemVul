gda_sql_operation_serialize (GdaSqlOperation *operation)
{
	if (!operation)
		return g_strdup ("null");
	else {
		GString *string;
		gchar *str;
		GSList *list;
		gint i = 0;

		string = g_string_new ("{");

		g_string_append (string, "\"operator\":");
		str = _json_quote_string (gda_sql_operation_operator_to_string (operation->operator_type));
		g_string_append (string, str);
		g_free (str);

		for (list = operation->operands; list; list = list->next) {
			g_string_append_printf (string, ",\"operand%d\":", i++);
			if (list->data) {
				str = gda_sql_expr_serialize ((GdaSqlExpr*) list->data);
				g_string_append (string, str);
				g_free (str);
			}
			else
				g_string_append (string, "null");
		}

		g_string_append_c (string, '}');
		str = string->str;
		g_string_free (string, FALSE);
		return str;
	}
}
