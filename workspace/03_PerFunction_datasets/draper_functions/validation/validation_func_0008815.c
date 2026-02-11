ExecTypeSetColNames(TupleDesc typeInfo, List *namesList)
{
	bool		modified = false;
	int			colno = 0;
	ListCell   *lc;

	foreach(lc, namesList)
	{
		char	   *cname = strVal(lfirst(lc));
		Form_pg_attribute attr;


		if (colno >= typeInfo->natts)
			break;
		attr = typeInfo->attrs[colno++];


		if (cname[0] == '\0')
			continue;


		if (strcmp(cname, NameStr(attr->attname)) != 0)
		{
			namestrcpy(&(attr->attname), cname);
			modified = true;
		}
	}


	if (modified)
	{
		typeInfo->tdtypeid = RECORDOID;
		typeInfo->tdtypmod = -1;
	}
}
