get_event_entry(void)
{
	struct evt_entry *e;

	if (list_empty(&wm_event.freeq)) {
		e = alloc_event_entry();
	} else {
		e = list_entry(wm_event.freeq.next, struct evt_entry, list);
		list_del(&e->list);
	}

	return e;
}
