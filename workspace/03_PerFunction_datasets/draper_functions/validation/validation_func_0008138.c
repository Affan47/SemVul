MPL_Get(struct mempool *mpl, unsigned *size)
{
	struct memitem *mi;

	CHECK_OBJ_NOTNULL(mpl, MEMPOOL_MAGIC);

	Lck_Lock(mpl->mtx);

	mpl->vsc->allocs++;
	mpl->vsc->live++;

	do {
		mi = VTAILQ_FIRST(&mpl->list);
		if (mi == NULL)
			break;
		mpl->vsc->pool--;
		mpl->n_pool--;
		CHECK_OBJ_NOTNULL(mi, MEMITEM_MAGIC);
		VTAILQ_REMOVE(&mpl->list, mi, list);
		if (mi->size < *mpl->cur_size) {
			mpl->vsc->toosmall++;
			VTAILQ_INSERT_HEAD(&mpl->surplus, mi, list);
			mi = NULL;
		} else {
			mpl->vsc->recycle++;
		}
	} while (mi == NULL);

	Lck_Unlock(mpl->mtx);

	if (mi == NULL)
		mi = mpl_alloc(mpl);
	if (size != NULL)
		*size = mi->size;


	return ((void*)(uintptr_t)&mi->payload);
}
