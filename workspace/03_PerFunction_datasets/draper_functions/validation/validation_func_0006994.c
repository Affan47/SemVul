__rec_close(dbp)
	DB *dbp;
{
	BTREE *t;
	int status;

	t = dbp->internal;


	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	if (__rec_sync(dbp, 0) == RET_ERROR)
		return (RET_ERROR);


	status = RET_SUCCESS;
	if (F_ISSET(t, R_MEMMAPPED) && munmap(t->bt_smap, t->bt_msize))
		status = RET_ERROR;

	if (!F_ISSET(t, R_INMEM)) {
		if (F_ISSET(t, R_CLOSEFP)) {
			if (fclose(t->bt_rfp))
				status = RET_ERROR;
		} else
			if (close(t->bt_rfd))
				status = RET_ERROR;
	}

	if (__bt_close(dbp) == RET_ERROR)
		status = RET_ERROR;

	return (status);
}
