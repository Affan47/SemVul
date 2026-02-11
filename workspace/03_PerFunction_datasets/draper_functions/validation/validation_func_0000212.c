op_hashjoinable(Oid opno)
{
	HeapTuple	tp;
	bool		result = false;

	tp = SearchSysCache(OPEROID,
						ObjectIdGetDatum(opno),
						0, 0, 0);
	if (HeapTupleIsValid(tp))
	{
		Form_pg_operator optup = (Form_pg_operator) GETSTRUCT(tp);

		result = optup->oprcanhash;
		ReleaseSysCache(tp);
	}
	return result;
}
