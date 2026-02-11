make_sort_from_groupcols(PlannerInfo *root,
						 List *groupcls,
						 AttrNumber *grpColIdx,
						 Plan *lefttree)
{
	List	   *sub_tlist = lefttree->targetlist;
	int			grpno = 0;
	ListCell   *l;
	int			numsortkeys;
	AttrNumber *sortColIdx;
	Oid		   *sortOperators;


	numsortkeys = list_length(groupcls);
	sortColIdx = (AttrNumber *) palloc(numsortkeys * sizeof(AttrNumber));
	sortOperators = (Oid *) palloc(numsortkeys * sizeof(Oid));

	numsortkeys = 0;

	foreach(l, groupcls)
	{
		GroupClause *grpcl = (GroupClause *) lfirst(l);
		TargetEntry *tle = get_tle_by_resno(sub_tlist, grpColIdx[grpno]);


		numsortkeys = add_sort_column(tle->resno, grpcl->sortop,
									  numsortkeys, sortColIdx, sortOperators);
		grpno++;
	}

	Assert(numsortkeys > 0);

	return make_sort(root, lefttree, numsortkeys,
					 sortColIdx, sortOperators);
}
