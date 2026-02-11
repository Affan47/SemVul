regclassout(PG_FUNCTION_ARGS)
{
	Oid			classid = PG_GETARG_OID(0);
	char	   *result;
	HeapTuple	classtup;

	if (classid == InvalidOid)
	{
		result = pstrdup("-");
		PG_RETURN_CSTRING(result);
	}

	classtup = SearchSysCache(RELOID,
							  ObjectIdGetDatum(classid),
							  0, 0, 0);

	if (HeapTupleIsValid(classtup))
	{
		Form_pg_class classform = (Form_pg_class) GETSTRUCT(classtup);
		char	   *classname = NameStr(classform->relname);


		if (IsBootstrapProcessingMode())
			result = pstrdup(classname);
		else
		{
			char	   *nspname;


			if (RelationIsVisible(classid))
				nspname = NULL;
			else
				nspname = get_namespace_name(classform->relnamespace);

			result = quote_qualified_identifier(nspname, classname);
		}

		ReleaseSysCache(classtup);
	}
	else
	{

		result = (char *) palloc(NAMEDATALEN);
		snprintf(result, NAMEDATALEN, "%u", classid);
	}

	PG_RETURN_CSTRING(result);
}
