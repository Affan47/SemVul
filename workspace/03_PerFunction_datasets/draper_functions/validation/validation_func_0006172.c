heap_page_prune_execute(Relation reln, Buffer buffer,
						OffsetNumber *redirected, int nredirected,
						OffsetNumber *nowdead, int ndead,
						OffsetNumber *nowunused, int nunused,
						bool redirect_move)
{
	Page		page = (Page) BufferGetPage(buffer);
	OffsetNumber *offnum;
	int			i;


	offnum = redirected;
	for (i = 0; i < nredirected; i++)
	{
		OffsetNumber fromoff = *offnum++;
		OffsetNumber tooff = *offnum++;
		ItemId		fromlp = PageGetItemId(page, fromoff);

		if (redirect_move)
		{

			ItemId		tolp = PageGetItemId(page, tooff);
			HeapTupleHeader htup;

			*fromlp = *tolp;
			ItemIdSetUnused(tolp);


			Assert(ItemIdIsNormal(fromlp));
			htup = (HeapTupleHeader) PageGetItem(page, fromlp);
			Assert(HeapTupleHeaderIsHeapOnly(htup));
			HeapTupleHeaderClearHeapOnly(htup);
		}
		else
		{

			ItemIdSetRedirect(fromlp, tooff);
		}
	}


	offnum = nowdead;
	for (i = 0; i < ndead; i++)
	{
		OffsetNumber off = *offnum++;
		ItemId		lp = PageGetItemId(page, off);

		ItemIdSetDead(lp);
	}


	offnum = nowunused;
	for (i = 0; i < nunused; i++)
	{
		OffsetNumber off = *offnum++;
		ItemId		lp = PageGetItemId(page, off);

		ItemIdSetUnused(lp);
	}


	PageRepairFragmentation(page);
}
