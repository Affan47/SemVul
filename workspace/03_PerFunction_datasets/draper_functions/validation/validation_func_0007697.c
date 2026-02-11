gkd_gpg_agent_ops_options (GkdGpgAgentCall *call, gchar *args)
{
	gchar *option;
	gsize len;

	split_arguments (args, NULL, &option, NULL);
	if (!option) {
		g_message ("received invalid option argument");
		return gkd_gpg_agent_send_reply (call, FALSE, "105 parameter error");
	}


	len = strlen (GPG_AGENT_OPT_DISPLAY);
	if (g_ascii_strncasecmp (option, GPG_AGENT_OPT_DISPLAY, len) == 0) {
		option += len;

		if (x11_displays_eq (option, g_getenv ("DISPLAY"))) {
			call->terminal_ok = TRUE;
		} else {
			g_message ("received request different display: %s", option);
			return gkd_gpg_agent_send_reply (call, FALSE, "105 parameter conflict");
		}
	}


	return gkd_gpg_agent_send_reply (call, TRUE, NULL);
}
