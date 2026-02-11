cmd_statusbar_print_info(const char *name)
{
	GSList *tmp;

        tmp = active_statusbar_group->config_bars;
	for (; tmp != NULL; tmp = tmp->next) {
		STATUSBAR_CONFIG_REC *rec = tmp->data;

		if (g_strcasecmp(rec->name, name) == 0) {
                        statusbar_print(rec);
			return;
		}
	}

	printformat(NULL, NULL, MSGLEVEL_CLIENTERROR,
		    TXT_STATUSBAR_NOT_FOUND, name);
}
