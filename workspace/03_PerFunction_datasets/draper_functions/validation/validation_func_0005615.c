irc_server_purge_output(IRC_SERVER_REC *server, const char *target)
{
	GSList *tmp, *next, *link;
        REDIRECT_REC *redirect;
	char *cmd;

	if (target != NULL && *target == '\0')
                target = NULL;

	for (tmp = server->cmdqueue; tmp != NULL; tmp = next) {
		next = tmp->next->next;
		cmd = tmp->data;
                redirect = tmp->next->data;

		if ((target == NULL || command_has_target(cmd, target)) &&
		    g_ascii_strncasecmp(cmd, "PONG ", 5) != 0) {

                        link = tmp->next;
			server->cmdqueue =
				g_slist_remove_link(server->cmdqueue, link);
                        g_slist_free_1(link);

			if (redirect != NULL)
                                server_redirect_destroy(redirect);


			server->cmdqueue =
				g_slist_remove(server->cmdqueue, cmd);
                        g_free(cmd);
                        server->cmdcount--;
		}
	}
}
