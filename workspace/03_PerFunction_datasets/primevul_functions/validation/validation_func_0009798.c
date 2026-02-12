static inline bool chain_epi_lockless(struct epitem *epi)
{
	struct eventpoll *ep = epi->ep;


	if (epi->next != EP_UNACTIVE_PTR)
		return false;


	if (cmpxchg(&epi->next, EP_UNACTIVE_PTR, NULL) != EP_UNACTIVE_PTR)
		return false;


	epi->next = xchg(&ep->ovflist, epi);

	return true;
}
