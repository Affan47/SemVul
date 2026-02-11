rm_conn(con c) {
	int n;

	if (!c)
		return;
	if (c->other) {
		c->other->other = NULL;
		if (!c->other->idx)
			rm_conn(c->other);
	}
	if ((n = c->idx)) {
		SSL_free(c->s);
		close(ev[n].fd);
		ev[n] = ev[--fd_count];
		(cons[n] = cons[fd_count])->idx = n;
	}
	free(c);
	cons[fd_count] = NULL;
}
