static void event_cap (IRC_SERVER_REC *server, char *args, char *nick, char *address)
{
	GSList *tmp;
	GString *cmd;
	char *params, *evt, *list, *star, **caps;
	int i, caps_length, disable, avail_caps, multiline;

	params = event_get_params(args, 4, NULL, &evt, &star, &list);
	if (params == NULL)
		return;


	if (!g_ascii_strcasecmp(evt, "LS") && !strcmp(star, "*")) {
		multiline = TRUE;
	}


	else if (list[0] == '\0') {
		multiline = FALSE;
		list = star;
	}

	else {
		irc_cap_finish_negotiation(server);
		g_warn_if_reached();
		return;
	}


	if (server->cap_supported == NULL) {
		server->cap_supported = g_hash_table_new_full(g_str_hash,
							      g_str_equal,
							      g_free, g_free);
	}


	caps = g_strsplit(g_strchomp(list), " ", -1);
	caps_length = g_strv_length(caps);

	if (!g_ascii_strcasecmp(evt, "LS")) {
		if (!server->cap_in_multiline) {

			g_hash_table_remove_all(server->cap_supported);
		}

		server->cap_in_multiline = multiline;


		for (i = 0; i < caps_length; i++) {
			char *key, *val;

			if (!parse_cap_name(caps[i], &key, &val)) {
				g_warning("Invalid CAP %s key/value pair", evt);
				continue;
			}

			if (g_hash_table_lookup_extended(server->cap_supported, key, NULL, NULL)) {


				g_warning("The server sent the %s capability twice", key);
			}
			g_hash_table_insert(server->cap_supported, key, val);
		}


		if (multiline == FALSE) {

			if (server->cap_queue == NULL) {
				irc_cap_finish_negotiation(server);
			}
			else {
				cmd = g_string_new("CAP REQ :");

				avail_caps = 0;


				server->cap_queue = g_slist_reverse(server->cap_queue);


				for (tmp = server->cap_queue; tmp != NULL; tmp = tmp->next) {
					if (g_hash_table_lookup_extended(server->cap_supported, tmp->data, NULL, NULL)) {
						if (avail_caps > 0)
							g_string_append_c(cmd, ' ');
						g_string_append(cmd, tmp->data);

						avail_caps++;
					}
				}


				gslist_free_full(server->cap_queue, (GDestroyNotify) g_free);
				server->cap_queue = NULL;


				if (avail_caps > 0) {
					signal_emit("server cap req", 2, server, cmd->str + sizeof("CAP REQ :") - 1);
					irc_send_cmd_now(server, cmd->str);
				} else {
					irc_cap_finish_negotiation(server);
				}

				g_string_free(cmd, TRUE);
			}
		}
	}
	else if (!g_ascii_strcasecmp(evt, "ACK")) {
		int got_sasl = FALSE;


		for (i = 0; i < caps_length; i++) {
			disable = (*caps[i] == '-');

			if (disable)
				server->cap_active = gslist_delete_string(server->cap_active, caps[i] + 1, g_free);
			else
				server->cap_active = g_slist_prepend(server->cap_active, g_strdup(caps[i]));

			if (!strcmp(caps[i], "sasl"))
				got_sasl = TRUE;

			cap_emit_signal(server, "ack", caps[i]);
		}


		if (got_sasl == FALSE)
			irc_cap_finish_negotiation(server);
	}
	else if (!g_ascii_strcasecmp(evt, "NAK")) {
		g_warning("The server answered with a NAK to our CAP request, this should not happen");


		for (i = 0; i < caps_length; i++)
			cap_emit_signal(server, "nak", caps[i]);
	}
	else if (!g_ascii_strcasecmp(evt, "NEW")) {
		for (i = 0; i < caps_length; i++) {
			char *key, *val;

			if (!parse_cap_name(caps[i], &key, &val)) {
				g_warning("Invalid CAP %s key/value pair", evt);
				continue;
			}

			g_hash_table_insert(server->cap_supported, key, val);
			cap_emit_signal(server, "new", key);
		}
	}
	else if (!g_ascii_strcasecmp(evt, "DEL")) {
		for (i = 0; i < caps_length; i++) {
			char *key, *val;

			if (!parse_cap_name(caps[i], &key, &val)) {
				g_warning("Invalid CAP %s key/value pair", evt);
				continue;
			}

			g_hash_table_remove(server->cap_supported, key);
			cap_emit_signal(server, "delete", key);


			server->cap_active = gslist_delete_string(server->cap_active, key, g_free);


			g_free(key);
			g_free(val);
		}
	}
	else if (!g_ascii_strcasecmp(evt, "LIST")) {

	}
	else {
		g_warning("Unhandled CAP subcommand %s", evt);
	}

	g_strfreev(caps);
	g_free(params);
}
