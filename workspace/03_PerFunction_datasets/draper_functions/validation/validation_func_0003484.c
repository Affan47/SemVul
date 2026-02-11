rangesel(PG_FUNCTION_ARGS)
{
	PlannerInfo *root = (PlannerInfo *) PG_GETARG_POINTER(0);
	Oid			operator = PG_GETARG_OID(1);
	List	   *args = (List *) PG_GETARG_POINTER(2);
	int			varRelid = PG_GETARG_INT32(3);
	VariableStatData vardata;
	Node	   *other;
	bool		varonleft;
	Selectivity selec;
	TypeCacheEntry *typcache = NULL;
	RangeType  *constrange = NULL;


	if (!get_restriction_variable(root, args, varRelid,
								  &vardata, &other, &varonleft))
		PG_RETURN_FLOAT8(default_range_selectivity(operator));


	if (!IsA(other, Const))
	{
		ReleaseVariableStats(vardata);
		PG_RETURN_FLOAT8(default_range_selectivity(operator));
	}


	if (((Const *) other)->constisnull)
	{
		ReleaseVariableStats(vardata);
		PG_RETURN_FLOAT8(0.0);
	}


	if (!varonleft)
	{

		operator = get_commutator(operator);
		if (!operator)
		{

			ReleaseVariableStats(vardata);
			PG_RETURN_FLOAT8(default_range_selectivity(operator));
		}
	}


	if (operator == OID_RANGE_CONTAINS_ELEM_OP)
	{
		typcache = range_get_typcache(fcinfo, vardata.vartype);

		if (((Const *) other)->consttype == typcache->rngelemtype->type_id)
		{
			RangeBound	lower,
						upper;

			lower.inclusive = true;
			lower.val = ((Const *) other)->constvalue;
			lower.infinite = false;
			lower.lower = true;
			upper.inclusive = true;
			upper.val = ((Const *) other)->constvalue;
			upper.infinite = false;
			upper.lower = false;
			constrange = range_serialize(typcache, &lower, &upper, false);
		}
	}
	else if (operator == OID_RANGE_ELEM_CONTAINED_OP)
	{


	}
	else if (((Const *) other)->consttype == vardata.vartype)
	{

		typcache = range_get_typcache(fcinfo, vardata.vartype);

		constrange = DatumGetRangeType(((Const *) other)->constvalue);
	}


	if (constrange)
		selec = calc_rangesel(typcache, &vardata, constrange, operator);
	else
		selec = default_range_selectivity(operator);

	ReleaseVariableStats(vardata);

	CLAMP_PROBABILITY(selec);

	PG_RETURN_FLOAT8((float8) selec);
}
