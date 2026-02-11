TransactionIdIsPrepared(TransactionId xid)
{
	bool		result = false;
	int			i;

	LWLockAcquire(TwoPhaseStateLock, LW_SHARED);

	for (i = 0; i < TwoPhaseState->numPrepXacts; i++)
	{
		GlobalTransaction gxact = TwoPhaseState->prepXacts[i];
		PGXACT	   *pgxact = &ProcGlobal->allPgXact[gxact->pgprocno];

		if (gxact->valid && pgxact->xid == xid)
		{
			result = true;
			break;
		}
	}

	LWLockRelease(TwoPhaseStateLock);

	return result;
}
