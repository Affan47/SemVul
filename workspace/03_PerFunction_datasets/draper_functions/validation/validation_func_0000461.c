find_typmod_coercion_function(Oid typeId,
							  Oid *funcid)
{
	CoercionPathType result;
	Type		targetType;
	Form_pg_type typeForm;
	HeapTuple	tuple;

	*funcid = InvalidOid;
	result = COERCION_PATH_FUNC;

	targetType = typeidType(typeId);
	typeForm = (Form_pg_type) GETSTRUCT(targetType);


	if (typeForm->typelem != InvalidOid && typeForm->typlen == -1)
	{

		typeId = typeForm->typelem;
		result = COERCION_PATH_ARRAYCOERCE;
	}
	ReleaseSysCache(targetType);


	tuple = SearchSysCache2(CASTSOURCETARGET,
							ObjectIdGetDatum(typeId),
							ObjectIdGetDatum(typeId));

	if (HeapTupleIsValid(tuple))
	{
		Form_pg_cast castForm = (Form_pg_cast) GETSTRUCT(tuple);

		*funcid = castForm->castfunc;
		ReleaseSysCache(tuple);
	}

	if (!OidIsValid(*funcid))
		result = COERCION_PATH_NONE;

	return result;
}
