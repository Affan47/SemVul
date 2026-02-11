vev_sched_timeout(struct vev_base *evb, struct vev *e, double t)
{
	int i;


	i = e->callback(e, 0);
	if (i) {
		vev_del(evb, e);
		free(e);
	} else {
		e->__when = t + e->timeout;
		binheap_delete(evb->binheap, e->__binheap_idx);
		binheap_insert(evb->binheap, e);
	}
	return (1);
}
