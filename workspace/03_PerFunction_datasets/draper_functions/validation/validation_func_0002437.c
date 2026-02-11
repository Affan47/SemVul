dump_append(struct dump *dump, const void *data, size_t size)
{
	g_return_if_fail(dump->slist);

	pmsg_slist_append(dump->slist, data, size);
	dump->fill += size;
}
