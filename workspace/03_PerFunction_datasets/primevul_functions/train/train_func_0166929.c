vte_sequence_handler_erase_in_display (VteTerminal *terminal, GValueArray *params)
{
	GValue *value;
	long param;
	guint i;

	param = 0;

	for (i = 0; (params != NULL) && (i < params->n_values); i++) {
		value = g_value_array_get_nth(params, i);
		if (!G_VALUE_HOLDS_LONG(value)) {
			continue;
		}
		param = g_value_get_long(value);
	}

	switch (param) {
	case 0:

		vte_sequence_handler_cd (terminal, NULL);
		break;
	case 1:

		_vte_terminal_clear_above_current (terminal);


		vte_sequence_handler_cb (terminal, NULL);
		break;
	case 2:

		_vte_terminal_clear_screen (terminal);
		break;
	default:
		break;
	}

	terminal->pvt->text_deleted_flag = TRUE;
}
