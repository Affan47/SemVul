SampleNext(SampleScanState *node)
{
	HeapTuple	tuple;
	TupleTableSlot *slot;


	if (!node->begun)
		tablesample_init(node);


	tuple = tablesample_getnext(node);

	slot = node->ss.ss_ScanTupleSlot;

	if (tuple)
		ExecStoreTuple(tuple,
					   slot,
					   node->ss.ss_currentScanDesc->rs_cbuf,
					   false);
	else
		ExecClearTuple(slot);

	return slot;
}
