ExecReScanFunctionScan(FunctionScanState *node)
{
	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	ExecScanReScan(&node->ss);


	if (!node->tuplestorestate)
		return;


	if (node->ss.ps.chgParam != NULL)
	{
		tuplestore_end(node->tuplestorestate);
		node->tuplestorestate = NULL;
	}
	else
		tuplestore_rescan(node->tuplestorestate);
}
