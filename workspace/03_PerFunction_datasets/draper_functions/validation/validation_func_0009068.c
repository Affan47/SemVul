dtModify(tid_t tid, struct inode *ip,
	 struct component_name * key, ino_t * orig_ino, ino_t new_ino, int flag)
{
	int rc;
	s64 bn;
	struct metapage *mp;
	dtpage_t *p;
	int index;
	struct btstack btstack;
	struct tlock *tlck;
	struct dt_lock *dtlck;
	struct lv *lv;
	s8 *stbl;
	int entry_si;
	struct ldtentry *entry;


	if ((rc = dtSearch(ip, key, orig_ino, &btstack, flag)))
		return rc;


	DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	BT_MARK_DIRTY(mp, ip);


	tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
	dtlck = (struct dt_lock *) & tlck->lock;


	stbl = DT_GETSTBL(p);
	entry_si = stbl[index];


	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = entry_si;
	lv->length = 1;
	dtlck->index++;


	entry = (struct ldtentry *) & p->slot[entry_si];


	entry->inumber = cpu_to_le32(new_ino);


	DT_PUTPAGE(mp);

	return 0;
}
