found_reset(size_t max_size, const struct guid *muid, unsigned flags,
	qhit_process_t process, void *udata, const struct array *token)
{
	g_assert(process != NULL);
	g_assert(max_size <= INT_MAX);
	found_init(max_size, muid, flags, process, udata, token);
	found_clear();
}
