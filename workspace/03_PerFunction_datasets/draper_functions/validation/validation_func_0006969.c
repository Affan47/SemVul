pfs_channel_lookup( const char *name, pfs_size_t *start )
{
	struct entry *e = head;

	do {
		if(e->name && !strcmp(e->name,name)) {
			e->inuse++;
			*start = e->start;
			return 1;
		}
		e = e->next;
	} while(e!=head);

	return 0;
}
