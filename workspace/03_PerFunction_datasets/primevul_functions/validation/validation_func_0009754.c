static __poll_t ep_scan_ready_list(struct eventpoll *ep,
			      __poll_t (*sproc)(struct eventpoll *,
					   struct list_head *, void *),
			      void *priv, int depth, bool ep_locked)
{
	__poll_t res;
	struct epitem *epi, *nepi;
	LIST_HEAD(txlist);

	lockdep_assert_irqs_enabled();


	if (!ep_locked)
		mutex_lock_nested(&ep->mtx, depth);


	write_lock_irq(&ep->lock);
	list_splice_init(&ep->rdllist, &txlist);
	WRITE_ONCE(ep->ovflist, NULL);
	write_unlock_irq(&ep->lock);


	res = (*sproc)(ep, &txlist, priv);

	write_lock_irq(&ep->lock);


	for (nepi = READ_ONCE(ep->ovflist); (epi = nepi) != NULL;
	     nepi = epi->next, epi->next = EP_UNACTIVE_PTR) {


		if (!ep_is_linked(epi)) {


			list_add(&epi->rdllink, &ep->rdllist);
			ep_pm_stay_awake(epi);
		}
	}


	WRITE_ONCE(ep->ovflist, EP_UNACTIVE_PTR);


	list_splice(&txlist, &ep->rdllist);
	__pm_relax(ep->ws);
	write_unlock_irq(&ep->lock);

	if (!ep_locked)
		mutex_unlock(&ep->mtx);

	return res;
}
