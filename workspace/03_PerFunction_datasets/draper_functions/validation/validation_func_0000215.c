GetDatabasePath(Oid dbNode, Oid spcNode)
{
	if (spcNode == GLOBALTABLESPACE_OID)
	{

		Assert(dbNode == 0);
		return pstrdup("global");
	}
	else if (spcNode == DEFAULTTABLESPACE_OID)
	{

		return psprintf("base/%u", dbNode);
	}
	else
	{

		return psprintf("pg_tblspc/%u/%s/%u",
						spcNode, TABLESPACE_VERSION_DIRECTORY, dbNode);
	}
}
