examine_attribute(Relation onerel, int attnum)
{
	Form_pg_attribute attr = onerel->rd_att->attrs[attnum - 1];
	HeapTuple	typtuple;
	VacAttrStats *stats;
	bool		ok;


	if (attr->attisdropped)
		return NULL;


	if (attr->attstattarget == 0)
		return NULL;


	stats = (VacAttrStats *) palloc0(sizeof(VacAttrStats));
	stats->attr = (Form_pg_attribute) palloc(ATTRIBUTE_TUPLE_SIZE);
	memcpy(stats->attr, attr, ATTRIBUTE_TUPLE_SIZE);
	typtuple = SearchSysCache(TYPEOID,
							  ObjectIdGetDatum(attr->atttypid),
							  0, 0, 0);
	if (!HeapTupleIsValid(typtuple))
		elog(ERROR, "cache lookup failed for type %u", attr->atttypid);
	stats->attrtype = (Form_pg_type) palloc(sizeof(FormData_pg_type));
	memcpy(stats->attrtype, GETSTRUCT(typtuple), sizeof(FormData_pg_type));
	ReleaseSysCache(typtuple);
	stats->anl_context = anl_context;
	stats->tupattnum = attnum;


	if (OidIsValid(stats->attrtype->typanalyze))
		ok = DatumGetBool(OidFunctionCall1(stats->attrtype->typanalyze,
										   PointerGetDatum(stats)));
	else
		ok = std_typanalyze(stats);

	if (!ok || stats->compute_stats == NULL || stats->minrows <= 0)
	{
		pfree(stats->attrtype);
		pfree(stats->attr);
		pfree(stats);
		return NULL;
	}

	return stats;
}
