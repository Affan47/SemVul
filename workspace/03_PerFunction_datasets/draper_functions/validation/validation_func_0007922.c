LockTableCommand(LockStmt *lockstmt)
{
	ListCell   *p;


	foreach(p, lockstmt->relations)
	{
		RangeVar   *relation = (RangeVar *) lfirst(p);
		bool		recurse = interpretInhOption(relation->inhOpt);
		Oid			reloid;

		reloid = RangeVarGetRelid(relation, false);


		if (lockstmt->mode > RowExclusiveLock)
			PreventCommandDuringRecovery("LOCK TABLE");

		LockTableRecurse(reloid, relation,
						 lockstmt->mode, lockstmt->nowait, recurse);
	}
}
