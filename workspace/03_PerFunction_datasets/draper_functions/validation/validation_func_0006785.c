is_common_timeout(const struct timeval *tv,
    const struct event_base *base)
{
	int idx;
	if ((tv->tv_usec & COMMON_TIMEOUT_MASK) != COMMON_TIMEOUT_MAGIC)
		return 0;
	idx = COMMON_TIMEOUT_IDX(tv);
	return idx < base->n_common_timeouts;
}
