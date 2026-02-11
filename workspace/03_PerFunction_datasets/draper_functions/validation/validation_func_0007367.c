assignOperSubtype(Oid amoid, Oid typeoid, Oid operOid)
{
	Oid			subtype;
	Operator	optup;
	Form_pg_operator opform;


	if (amoid != BTREE_AM_OID)
		return InvalidOid;

	optup = SearchSysCache(OPEROID,
						   ObjectIdGetDatum(operOid),
						   0, 0, 0);
	if (optup == NULL)
		elog(ERROR, "cache lookup failed for operator %u", operOid);
	opform = (Form_pg_operator) GETSTRUCT(optup);


	if (opform->oprkind != 'b')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("btree operators must be binary")));
	if (opform->oprresult != BOOLOID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("btree operators must return boolean")));
	if (opform->oprleft != typeoid)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
			  errmsg("btree operators must have index type as left input")));


	if (opform->oprright == typeoid)
		subtype = InvalidOid;
	else
		subtype = opform->oprright;
	ReleaseSysCache(optup);
	return subtype;
}
