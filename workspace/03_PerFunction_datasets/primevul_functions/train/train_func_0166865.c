vte_sequence_handler_set_mode_internal(VteTerminal *terminal,
				       long setting, gboolean value)
{
	switch (setting) {
	case 2:
		break;
	case 4:
		terminal->pvt->screen->insert_mode = value;
		break;
	case 12:
		terminal->pvt->screen->sendrecv_mode = value;
		break;
	case 20:
		terminal->pvt->screen->linefeed_mode = value;
		break;
	default:
		break;
	}
}
