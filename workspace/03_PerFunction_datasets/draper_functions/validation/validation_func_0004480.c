print_session_list(GPtrArray *session_list, const char *path)
{
	int i;
	struct lttng_live_relay_session *relay_session;

	for (i = 0; i < session_list->len; i++) {
		relay_session = g_ptr_array_index(session_list, i);
		fprintf(stdout, "%s/host/%s/%s (timer = %u, "
				"%u stream(s), %u client(s) connected)\n",
				path, relay_session->hostname,
				relay_session->name, relay_session->timer,
				relay_session->streams, relay_session->clients);
	}
}
