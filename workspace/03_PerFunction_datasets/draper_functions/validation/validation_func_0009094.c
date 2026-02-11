GetRelationPath(Oid dbNode, Oid spcNode, Oid relNode,
				int backendId, ForkNumber forkNumber)
{
	char	   *path;

	if (spcNode == GLOBALTABLESPACE_OID)
	{

		Assert(dbNode == 0);
		Assert(backendId == InvalidBackendId);
		if (forkNumber != MAIN_FORKNUM)
			path = psprintf("global/%u_%s",
							relNode, forkNames[forkNumber]);
		else
			path = psprintf("global/%u", relNode);
	}
	else if (spcNode == DEFAULTTABLESPACE_OID)
	{

		if (backendId == InvalidBackendId)
		{
			if (forkNumber != MAIN_FORKNUM)
				path = psprintf("base/%u/%u_%s",
								dbNode, relNode,
								forkNames[forkNumber]);
			else
				path = psprintf("base/%u/%u",
								dbNode, relNode);
		}
		else
		{
			if (forkNumber != MAIN_FORKNUM)
				path = psprintf("base/%u/t%d_%u_%s",
								dbNode, backendId, relNode,
								forkNames[forkNumber]);
			else
				path = psprintf("base/%u/t%d_%u",
								dbNode, backendId, relNode);
		}
	}
	else
	{

		if (backendId == InvalidBackendId)
		{
			if (forkNumber != MAIN_FORKNUM)
				path = psprintf("pg_tblspc/%u/%s/%u/%u_%s",
								spcNode, TABLESPACE_VERSION_DIRECTORY,
								dbNode, relNode,
								forkNames[forkNumber]);
			else
				path = psprintf("pg_tblspc/%u/%s/%u/%u",
								spcNode, TABLESPACE_VERSION_DIRECTORY,
								dbNode, relNode);
		}
		else
		{
			if (forkNumber != MAIN_FORKNUM)
				path = psprintf("pg_tblspc/%u/%s/%u/t%d_%u_%s",
								spcNode, TABLESPACE_VERSION_DIRECTORY,
								dbNode, backendId, relNode,
								forkNames[forkNumber]);
			else
				path = psprintf("pg_tblspc/%u/%s/%u/t%d_%u",
								spcNode, TABLESPACE_VERSION_DIRECTORY,
								dbNode, backendId, relNode);
		}
	}
	return path;
}
