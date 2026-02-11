t3_l2e_free(struct l2t_data *d, struct l2t_entry *e)
{
	spin_lock_bh(&e->lock);
	if (atomic_read(&e->refcnt) == 0) {
		if (e->neigh) {
			neigh_release(e->neigh);
			e->neigh = NULL;
		}
	}
	spin_unlock_bh(&e->lock);
	atomic_inc(&d->nfree);
}
