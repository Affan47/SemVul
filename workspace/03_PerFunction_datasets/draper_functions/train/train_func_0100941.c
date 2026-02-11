hashgettuple(PG_FUNCTION_ARGS)
{
	IndexScanDesc scan = (IndexScanDesc) PG_GETARG_POINTER(0);
	ScanDirection dir = (ScanDirection) PG_GETARG_INT32(1);
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	Relation	rel = scan->indexRelation;
	Page		page;
	OffsetNumber offnum;
	bool		res;


	if (BufferIsValid(so->hashso_curbuf))
		_hash_chgbufaccess(rel, so->hashso_curbuf, HASH_NOLOCK, HASH_READ);


	if (ItemPointerIsValid(&(so->hashso_curpos)))
	{


		if (scan->kill_prior_tuple)
		{


			offnum = ItemPointerGetOffsetNumber(&(so->hashso_curpos));
			page = BufferGetPage(so->hashso_curbuf);
			ItemIdMarkDead(PageGetItemId(page, offnum));


			SetBufferCommitInfoNeedsSave(so->hashso_curbuf);
		}


		res = _hash_next(scan, dir);
	}
	else
		res = _hash_first(scan, dir);


	if (scan->ignore_killed_tuples)
	{
		while (res)
		{
			offnum = ItemPointerGetOffsetNumber(&(so->hashso_curpos));
			page = BufferGetPage(so->hashso_curbuf);
			if (!ItemIdIsDead(PageGetItemId(page, offnum)))
				break;
			res = _hash_next(scan, dir);
		}
	}


	if (BufferIsValid(so->hashso_curbuf))
		_hash_chgbufaccess(rel, so->hashso_curbuf, HASH_READ, HASH_NOLOCK);

	PG_RETURN_BOOL(res);
}
