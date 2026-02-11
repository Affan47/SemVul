scanNameSpaceForRefname(ParseState *pstate, const char *refname)
{
	RangeTblEntry *result = NULL;
	ListCell   *l;

	foreach(l, pstate->p_relnamespace)
	{
		RangeTblEntry *rte = (RangeTblEntry *) lfirst(l);

		if (strcmp(rte->eref->aliasname, refname) == 0)
		{
			if (result)
				ereport(ERROR,
						(errcode(ERRCODE_AMBIGUOUS_ALIAS),
						 errmsg("table reference \"%s\" is ambiguous",
								refname)));
			result = rte;
		}
	}
	return result;
}
