generate_join_implied_equalities_broken(PlannerInfo *root,
										EquivalenceClass *ec,
										RelOptInfo *joinrel,
										RelOptInfo *outer_rel,
										RelOptInfo *inner_rel)
{
	List	   *result = NIL;
	ListCell   *lc;

	foreach(lc, ec->ec_sources)
	{
		RestrictInfo *restrictinfo = (RestrictInfo *) lfirst(lc);

		if (bms_is_subset(restrictinfo->required_relids, joinrel->relids) &&
		  !bms_is_subset(restrictinfo->required_relids, outer_rel->relids) &&
			!bms_is_subset(restrictinfo->required_relids, inner_rel->relids))
			result = lappend(result, restrictinfo);
	}

	return result;
}
