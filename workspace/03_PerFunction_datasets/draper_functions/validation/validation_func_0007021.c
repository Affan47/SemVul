cq_free_periodic(const void *key, void *data)
{
	cperiodic_t *cp = deconstify_pointer(key);

	(void) data;

	cperiodic_check(cp);
	cp->magic = 0;
	WFREE(cp);
	return TRUE;
}
