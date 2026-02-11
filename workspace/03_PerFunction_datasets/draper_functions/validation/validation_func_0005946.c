RememberFsyncRequest(RelFileNode rnode, ForkNumber forknum, BlockNumber segno)
{
	Assert(pendingOpsTable);

	if (segno == FORGET_RELATION_FSYNC)
	{

		HASH_SEQ_STATUS hstat;
		PendingOperationEntry *entry;

		hash_seq_init(&hstat, pendingOpsTable);
		while ((entry = (PendingOperationEntry *) hash_seq_search(&hstat)) != NULL)
		{
			if (RelFileNodeEquals(entry->tag.rnode, rnode) &&
				entry->tag.forknum == forknum)
			{

				entry->canceled = true;
			}
		}
	}
	else if (segno == FORGET_DATABASE_FSYNC)
	{

		HASH_SEQ_STATUS hstat;
		PendingOperationEntry *entry;
		ListCell   *cell,
				   *prev,
				   *next;


		hash_seq_init(&hstat, pendingOpsTable);
		while ((entry = (PendingOperationEntry *) hash_seq_search(&hstat)) != NULL)
		{
			if (entry->tag.rnode.dbNode == rnode.dbNode)
			{

				entry->canceled = true;
			}
		}


		prev = NULL;
		for (cell = list_head(pendingUnlinks); cell; cell = next)
		{
			PendingUnlinkEntry *entry = (PendingUnlinkEntry *) lfirst(cell);

			next = lnext(cell);
			if (entry->rnode.dbNode == rnode.dbNode)
			{
				pendingUnlinks = list_delete_cell(pendingUnlinks, cell, prev);
				pfree(entry);
			}
			else
				prev = cell;
		}
	}
	else if (segno == UNLINK_RELATION_REQUEST)
	{

		MemoryContext oldcxt = MemoryContextSwitchTo(MdCxt);
		PendingUnlinkEntry *entry;

		entry = palloc(sizeof(PendingUnlinkEntry));
		entry->rnode = rnode;
		entry->cycle_ctr = mdckpt_cycle_ctr;

		pendingUnlinks = lappend(pendingUnlinks, entry);

		MemoryContextSwitchTo(oldcxt);
	}
	else
	{

		PendingOperationTag key;
		PendingOperationEntry *entry;
		bool		found;


		MemSet(&key, 0, sizeof(key));
		key.rnode = rnode;
		key.forknum = forknum;
		key.segno = segno;

		entry = (PendingOperationEntry *) hash_search(pendingOpsTable,
													  &key,
													  HASH_ENTER,
													  &found);

		if (!found || entry->canceled)
		{
			entry->canceled = false;
			entry->cycle_ctr = mdsync_cycle_ctr;
		}


	}
}
