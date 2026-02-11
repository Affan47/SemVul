vacuum(VacuumStmt *vacstmt, Oid relid, bool do_toast,
	   BufferAccessStrategy bstrategy, bool for_wraparound, bool isTopLevel)
{
	const char *stmttype = vacstmt->vacuum ? "VACUUM" : "ANALYZE";
	volatile MemoryContext anl_context = NULL;
	volatile bool all_rels,
				in_outer_xact,
				use_own_xacts;
	List	   *relations;

	if (vacstmt->verbose)
		elevel = INFO;
	else
		elevel = DEBUG2;


	if (vacstmt->vacuum)
	{
		PreventTransactionChain(isTopLevel, stmttype);
		in_outer_xact = false;
	}
	else
		in_outer_xact = IsInTransactionChain(isTopLevel);


	if (vacstmt->vacuum && !IsAutoVacuumWorkerProcess())
		pgstat_vacuum_stat();


	vac_context = AllocSetContextCreate(PortalContext,
										"Vacuum",
										ALLOCSET_DEFAULT_MINSIZE,
										ALLOCSET_DEFAULT_INITSIZE,
										ALLOCSET_DEFAULT_MAXSIZE);


	if (bstrategy == NULL)
	{
		MemoryContext old_context = MemoryContextSwitchTo(vac_context);

		bstrategy = GetAccessStrategy(BAS_VACUUM);
		MemoryContextSwitchTo(old_context);
	}
	vac_strategy = bstrategy;


	all_rels = (!OidIsValid(relid) && vacstmt->relation == NULL);


	relations = get_rel_oids(relid, vacstmt->relation, stmttype);


	if (vacstmt->vacuum)
		use_own_xacts = true;
	else
	{
		Assert(vacstmt->analyze);
		if (IsAutoVacuumWorkerProcess())
			use_own_xacts = true;
		else if (in_outer_xact)
			use_own_xacts = false;
		else if (list_length(relations) > 1)
			use_own_xacts = true;
		else
			use_own_xacts = false;
	}


	if (!use_own_xacts)
		anl_context = AllocSetContextCreate(PortalContext,
											"Analyze",
											ALLOCSET_DEFAULT_MINSIZE,
											ALLOCSET_DEFAULT_INITSIZE,
											ALLOCSET_DEFAULT_MAXSIZE);


	if (use_own_xacts)
	{

		if (ActiveSnapshotSet())
			PopActiveSnapshot();


		CommitTransactionCommand();
	}


	PG_TRY();
	{
		ListCell   *cur;

		VacuumCostActive = (VacuumCostDelay > 0);
		VacuumCostBalance = 0;


		foreach(cur, relations)
		{
			Oid			relid = lfirst_oid(cur);
			bool		scanned_all = false;

			if (vacstmt->vacuum)
				vacuum_rel(relid, vacstmt, do_toast, for_wraparound,
						   &scanned_all);

			if (vacstmt->analyze)
			{
				MemoryContext old_context = NULL;


				if (use_own_xacts)
				{
					StartTransactionCommand();

					PushActiveSnapshot(GetTransactionSnapshot());
				}
				else
					old_context = MemoryContextSwitchTo(anl_context);

				analyze_rel(relid, vacstmt, vac_strategy, !scanned_all);

				if (use_own_xacts)
				{
					PopActiveSnapshot();
					CommitTransactionCommand();
				}
				else
				{
					MemoryContextSwitchTo(old_context);
					MemoryContextResetAndDeleteChildren(anl_context);
				}
			}
		}
	}
	PG_CATCH();
	{

		VacuumCostActive = false;
		PG_RE_THROW();
	}
	PG_END_TRY();


	VacuumCostActive = false;


	if (use_own_xacts)
	{


		StartTransactionCommand();
	}

	if (vacstmt->vacuum && !IsAutoVacuumWorkerProcess())
	{


		vac_update_datfrozenxid();
	}


	MemoryContextDelete(vac_context);
	vac_context = NULL;

	if (anl_context)
		MemoryContextDelete(anl_context);
}
