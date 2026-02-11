AlterEnum(AlterEnumStmt *stmt)
{
	Oid			enum_type_oid;
	TypeName   *typename;
	HeapTuple	tup;


	typename = makeTypeNameFromNameList(stmt->typeName);
	enum_type_oid = typenameTypeId(NULL, typename);

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(enum_type_oid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", enum_type_oid);


	checkEnumOwner(tup);


	AddEnumLabel(enum_type_oid, stmt->newVal,
				 stmt->newValNeighbor, stmt->newValIsAfter);

	ReleaseSysCache(tup);
}
