dataPlaceToPageLeafRecompress(Buffer buf, disassembledLeaf *leaf)
{
	Page		page = BufferGetPage(buf);
	char	   *ptr;
	int			newsize;
	bool		modified = false;
	dlist_iter	iter;
	int			segsize;


	if (!GinPageIsCompressed(page))
	{
		Assert(leaf->oldformat);
		GinPageSetCompressed(page);
		GinPageGetOpaque(page)->maxoff = InvalidOffsetNumber;
		modified = true;
	}

	ptr = (char *) GinDataLeafPageGetPostingList(page);
	newsize = 0;
	dlist_foreach(iter, &leaf->segments)
	{
		leafSegmentInfo *seginfo = dlist_container(leafSegmentInfo, node, iter.cur);

		if (seginfo->action != GIN_SEGMENT_UNMODIFIED)
			modified = true;

		if (seginfo->action != GIN_SEGMENT_DELETE)
		{
			segsize = SizeOfGinPostingList(seginfo->seg);

			if (modified)
				memcpy(ptr, seginfo->seg, segsize);

			ptr += segsize;
			newsize += segsize;
		}
	}

	Assert(newsize <= GinDataPageMaxDataSize);
	GinDataPageSetDataSize(page, newsize);
}
