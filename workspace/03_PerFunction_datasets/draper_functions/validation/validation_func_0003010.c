RecordRelationFreeSpace(RelFileNode *rel,
						BlockNumber interestingPages,
						int nPages,
						PageFreeSpaceInfo *pageSpaces)
{
	FSMRelation *fsmrel;


	if (nPages < 0)
		nPages = 0;
	else if (nPages > MaxFSMPages)
		nPages = MaxFSMPages;

	LWLockAcquire(FreeSpaceLock, LW_EXCLUSIVE);


	fsmrel = lookup_fsm_rel(rel);
	if (fsmrel)
	{
		int			curAlloc;
		int			curAllocPages;
		FSMPageData *newLocation;

		curAlloc = realloc_fsm_rel(fsmrel, interestingPages, false);
		curAllocPages = curAlloc * CHUNKPAGES;


		newLocation = (FSMPageData *)
			(FreeSpaceMap->arena + fsmrel->firstChunk * CHUNKBYTES);
		if (nPages <= curAllocPages)
		{
			int			i;

			for (i = 0; i < nPages; i++)
			{
				BlockNumber page = pageSpaces[i].blkno;
				Size		avail = pageSpaces[i].avail;


				if (i > 0 && page <= pageSpaces[i - 1].blkno)
					elog(ERROR, "free-space data is not in page order");
				FSMPageSetPageNum(newLocation, page);
				FSMPageSetSpace(newLocation, avail);
				newLocation++;
			}
			fsmrel->storedPages = nPages;
		}
		else
		{
			pack_incoming_pages(newLocation, curAllocPages,
								pageSpaces, nPages);
			fsmrel->storedPages = curAllocPages;
		}
	}
	LWLockRelease(FreeSpaceLock);
}
