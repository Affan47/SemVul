thread_clear(struct replay_thread *thr)
{

	thr->method = thr->proto = thr->url = NULL;
	thr->conn = NULL;
	memset(&thr->hdr, 0, sizeof thr->hdr);
	thr->nhdr = 0;
	thr->bogus = 0;
	memset(&thr->arena, 0, sizeof thr->arena);
	thr->top = 0;
	memset(&thr->line, 0, sizeof thr->line);
	memset(&thr->temp, 0, sizeof thr->temp);
	if (thr->sock != -1)
		close(thr->sock);
	thr->sock = -1;
}
