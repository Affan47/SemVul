ExecIndexScan(IndexScanState *node)
{


	if (node->iss_NumRuntimeKeys != 0 && !node->iss_RuntimeKeysReady)
		ExecReScan((PlanState *) node, NULL);


	return ExecScan(&node->ss, (ExecScanAccessMtd) IndexNext);
}
