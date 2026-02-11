setTargetTable(ParseState *pstate, RangeVar *relation,
			   bool inh, bool alsoSource, AclMode requiredPerms)
{
	RangeTblEntry *rte;
	int			rtindex;


	if (pstate->p_target_relation != NULL)
		heap_close(pstate->p_target_relation, NoLock);


	pstate->p_target_relation = parserOpenTable(pstate, relation,
												RowExclusiveLock);


	rte = addRangeTableEntryForRelation(pstate, pstate->p_target_relation,
										relation->alias, inh, false);
	pstate->p_target_rangetblentry = rte;


	rtindex = list_length(pstate->p_rtable);
	Assert(rte == rt_fetch(rtindex, pstate->p_rtable));


	rte->requiredPerms = requiredPerms;


	if (alsoSource)
		addRTEtoQuery(pstate, rte, true, true, true);

	return rtindex;
}
