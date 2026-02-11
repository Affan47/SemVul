LookupNamespaceNoError(const char *nspname)
{

	if (strcmp(nspname, "pg_temp") == 0)
	{
		if (OidIsValid(myTempNamespace))
			return myTempNamespace;


		return InvalidOid;
	}

	return get_namespace_oid(nspname, true);
}
