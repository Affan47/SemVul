ForwardFsyncRequest(RelFileNode rnode, BlockNumber segno)
{
	BgWriterRequest *request;

	if (!IsUnderPostmaster)
		return false;
	Assert(BgWriterShmem != NULL);

	LWLockAcquire(BgWriterCommLock, LW_EXCLUSIVE);
	if (BgWriterShmem->bgwriter_pid == 0 ||
		BgWriterShmem->num_requests >= BgWriterShmem->max_requests)
	{
		LWLockRelease(BgWriterCommLock);
		return false;
	}
	request = &BgWriterShmem->requests[BgWriterShmem->num_requests++];
	request->rnode = rnode;
	request->segno = segno;
	LWLockRelease(BgWriterCommLock);
	return true;
}
