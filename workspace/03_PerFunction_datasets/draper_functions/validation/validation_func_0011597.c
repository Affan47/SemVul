SimpleLruReadPage(SlruCtl ctl, int pageno, TransactionId xid)
{
	SlruShared	shared = ctl->shared;


	for (;;)
	{
		int			slotno;
		bool		ok;


		slotno = SlruSelectLRUPage(ctl, pageno);


		if (shared->page_number[slotno] == pageno &&
			shared->page_status[slotno] != SLRU_PAGE_EMPTY)
		{

			if (shared->page_status[slotno] == SLRU_PAGE_READ_IN_PROGRESS)
			{
				SimpleLruWaitIO(ctl, slotno);

				continue;
			}

			SlruRecentlyUsed(shared, slotno);
			return slotno;
		}


		Assert(shared->page_status[slotno] == SLRU_PAGE_EMPTY ||
			   (shared->page_status[slotno] == SLRU_PAGE_VALID &&
				!shared->page_dirty[slotno]));


		shared->page_number[slotno] = pageno;
		shared->page_status[slotno] = SLRU_PAGE_READ_IN_PROGRESS;
		shared->page_dirty[slotno] = false;


		LWLockAcquire(shared->buffer_locks[slotno], LW_EXCLUSIVE);


		SlruRecentlyUsed(shared, slotno);


		LWLockRelease(shared->ControlLock);


		ok = SlruPhysicalReadPage(ctl, pageno, slotno);


		LWLockAcquire(shared->ControlLock, LW_EXCLUSIVE);

		Assert(shared->page_number[slotno] == pageno &&
			   shared->page_status[slotno] == SLRU_PAGE_READ_IN_PROGRESS &&
			   !shared->page_dirty[slotno]);

		shared->page_status[slotno] = ok ? SLRU_PAGE_VALID : SLRU_PAGE_EMPTY;

		LWLockRelease(shared->buffer_locks[slotno]);


		if (!ok)
			SlruReportIOError(ctl, pageno, xid);

		SlruRecentlyUsed(shared, slotno);
		return slotno;
	}
}
