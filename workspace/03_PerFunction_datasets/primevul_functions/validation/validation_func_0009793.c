static __poll_t ep_read_events_proc(struct eventpoll *ep, struct list_head *head,
			       void *priv)
{
	struct epitem *epi, *tmp;
	poll_table pt;
	int depth = *(int *)priv;

	init_poll_funcptr(&pt, NULL);
	depth++;

	list_for_each_entry_safe(epi, tmp, head, rdllink) {
		if (ep_item_poll(epi, &pt, depth)) {
			return EPOLLIN | EPOLLRDNORM;
		} else {


			__pm_relax(ep_wakeup_source(epi));
			list_del_init(&epi->rdllink);
		}
	}

	return 0;
}
