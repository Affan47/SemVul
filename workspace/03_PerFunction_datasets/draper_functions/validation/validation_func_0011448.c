ExecReScanLockRows(LockRowsState *node)
{


	if (node->ps.lefttree->chgParam == NULL)
		ExecReScan(node->ps.lefttree);
}
