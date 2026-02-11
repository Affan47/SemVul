AttrDefaultFetch(Relation relation)
{
	AttrDefault *attrdef = relation->rd_att->constr->defval;
	int			ndef = relation->rd_att->constr->num_defval;
	Relation	adrel;
	SysScanDesc adscan;
	ScanKeyData skey;
	HeapTuple	htup;
	Datum		val;
	bool		isnull;
	int			found;
	int			i;

	ScanKeyInit(&skey,
				Anum_pg_attrdef_adrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(relation)));

	adrel = heap_open(AttrDefaultRelationId, AccessShareLock);
	adscan = systable_beginscan(adrel, AttrDefaultIndexId, true,
								SnapshotNow, 1, &skey);
	found = 0;

	while (HeapTupleIsValid(htup = systable_getnext(adscan)))
	{
		Form_pg_attrdef adform = (Form_pg_attrdef) GETSTRUCT(htup);

		for (i = 0; i < ndef; i++)
		{
			if (adform->adnum != attrdef[i].adnum)
				continue;
			if (attrdef[i].adbin != NULL)
				elog(WARNING, "multiple attrdef records found for attr %s of rel %s",
				NameStr(relation->rd_att->attrs[adform->adnum - 1]->attname),
					 RelationGetRelationName(relation));
			else
				found++;

			val = fastgetattr(htup,
							  Anum_pg_attrdef_adbin,
							  adrel->rd_att, &isnull);
			if (isnull)
				elog(WARNING, "null adbin for attr %s of rel %s",
				NameStr(relation->rd_att->attrs[adform->adnum - 1]->attname),
					 RelationGetRelationName(relation));
			else
				attrdef[i].adbin = MemoryContextStrdup(CacheMemoryContext,
								 DatumGetCString(DirectFunctionCall1(textout,
																	 val)));
			break;
		}

		if (i >= ndef)
			elog(WARNING, "unexpected attrdef record found for attr %d of rel %s",
				 adform->adnum, RelationGetRelationName(relation));
	}

	systable_endscan(adscan);
	heap_close(adrel, AccessShareLock);

	if (found != ndef)
		elog(WARNING, "%d attrdef record(s) missing for rel %s",
			 ndef - found, RelationGetRelationName(relation));
}
