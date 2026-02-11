sync_fh_state (struct queue *q)
{
	struct fh_state s;

	if (q->fd == -1)
		return 0;

	s.queue_head = htonl(q->queue_head);
	s.queue_length = htonl(q->queue_length);
	if (full_pwrite(q->fd, &s, sizeof(s), offsetof(struct file_header, s))
	    != 0)
		return -1;
	return q_sync(q);
}
