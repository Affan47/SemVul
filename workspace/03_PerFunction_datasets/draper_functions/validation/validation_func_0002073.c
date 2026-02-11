readtup_heap(Tuplesortstate *state, SortTuple *stup,
			 int tapenum, unsigned int len)
{
	unsigned int tupbodylen = len - sizeof(int);
	unsigned int tuplen = tupbodylen + MINIMAL_TUPLE_DATA_OFFSET;
	MinimalTuple tuple = (MinimalTuple) palloc(tuplen);
	char	   *tupbody = (char *) tuple + MINIMAL_TUPLE_DATA_OFFSET;
	HeapTupleData htup;

	USEMEM(state, GetMemoryChunkSpace(tuple));

	tuple->t_len = tuplen;
	if (LogicalTapeRead(state->tapeset, tapenum,
						(void *) tupbody,
						tupbodylen) != (size_t) tupbodylen)
		elog(ERROR, "unexpected end of data");
	if (state->randomAccess)
		if (LogicalTapeRead(state->tapeset, tapenum, (void *) &tuplen,
							sizeof(tuplen)) != sizeof(tuplen))
			elog(ERROR, "unexpected end of data");
	stup->tuple = (void *) tuple;

	htup.t_len = tuple->t_len + MINIMAL_TUPLE_OFFSET;
	htup.t_data = (HeapTupleHeader) ((char *) tuple - MINIMAL_TUPLE_OFFSET);
	stup->datum1 = heap_getattr(&htup,
								state->scanKeys[0].sk_attno,
								state->tupDesc,
								&stup->isnull1);
}
