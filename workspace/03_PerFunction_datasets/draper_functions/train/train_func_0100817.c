InitBufferPool(void)
{
	bool		foundBufs,
				foundDescs;

	BufferDescriptors = (BufferDesc *)
		ShmemInitStruct("Buffer Descriptors",
						NBuffers * sizeof(BufferDesc), &foundDescs);

	BufferBlocks = (char *)
		ShmemInitStruct("Buffer Blocks",
						NBuffers * (Size) BLCKSZ, &foundBufs);

	if (foundDescs || foundBufs)
	{

		Assert(foundDescs && foundBufs);

	}
	else
	{
		BufferDesc *buf;
		int			i;

		buf = BufferDescriptors;


		for (i = 0; i < NBuffers; buf++, i++)
		{
			CLEAR_BUFFERTAG(buf->tag);
			buf->flags = 0;
			buf->usage_count = 0;
			buf->refcount = 0;
			buf->wait_backend_pid = 0;

			SpinLockInit(&buf->buf_hdr_lock);

			buf->buf_id = i;


			buf->freeNext = i + 1;

			buf->io_in_progress_lock = LWLockAssign();
			buf->content_lock = LWLockAssign();
		}


		BufferDescriptors[NBuffers - 1].freeNext = FREENEXT_END_OF_LIST;
	}


	StrategyInitialize(!foundDescs);
}
