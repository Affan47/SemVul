TBUF_INIT_READ(size_t size)
{
	tbuf_check();

	if (NULL == tbuf.arena || (size_t) (tbuf.end - tbuf.arena) < size) {
		tbuf_extend(size, FALSE);
	}
	tbuf.rptr = tbuf.arena;
	tbuf.wptr = NULL;
}
