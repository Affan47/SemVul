_scir_add_to_lru(resource_mgr_t *mgr, resource_t *res)
{
	if (res->status != SCI_STATUS_ALLOCATED) {
		sciprintf("Resmgr: Oops: trying to enqueue resource with state"
			  " %d\n", res->status);
		return;
	}

	res->prev = NULL;
	res->next = mgr->lru_first;
	mgr->lru_first = res;
	if (!mgr->lru_last)
		mgr->lru_last = res;
	if (res->next)
		res->next->prev = res;

	mgr->memory_lru += res->size;
#if (SCI_VERBOSE_RESMGR > 1)
	fprintf(stderr, "Adding %s.%03d (%d bytes) to lru control: %d bytes total\n",
		sci_resource_types[res->type], res->number, res->size,
		mgr->memory_lru);

#endif

	res->status = SCI_STATUS_ENQUEUED;
}
