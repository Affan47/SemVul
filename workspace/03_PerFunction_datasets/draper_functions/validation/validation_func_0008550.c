aim_clearhandlers(aim_conn_t *conn)
{
	struct aim_rxcblist_s *cur;

	if (!conn)
		return -1;

	for (cur = (struct aim_rxcblist_s *)conn->handlerlist; cur;) {
		struct aim_rxcblist_s *tmp;

		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	conn->handlerlist = NULL;

	return 0;
}
