make_agg_subplan(PlannerInfo *root, MinMaxAggInfo *info)
{
	PlannerInfo subroot;
	Query	   *subparse;
	Plan	   *plan;
	Plan	   *iplan;
	TargetEntry *tle;
	SortClause *sortcl;
	NullTest   *ntest;


	memcpy(&subroot, root, sizeof(PlannerInfo));
	subroot.parse = subparse = (Query *) copyObject(root->parse);
	subparse->commandType = CMD_SELECT;
	subparse->resultRelation = 0;
	subparse->resultRelations = NIL;
	subparse->returningLists = NIL;
	subparse->into = NULL;
	subparse->hasAggs = false;
	subparse->groupClause = NIL;
	subparse->havingQual = NULL;
	subparse->distinctClause = NIL;
	subroot.hasHavingQual = false;


	tle = makeTargetEntry(copyObject(info->target),
						  1,
						  pstrdup("agg_target"),
						  false);
	subparse->targetList = list_make1(tle);


	sortcl = makeNode(SortClause);
	sortcl->tleSortGroupRef = assignSortGroupRef(tle, subparse->targetList);
	sortcl->sortop = info->aggsortop;
	subparse->sortClause = list_make1(sortcl);


	subparse->limitOffset = NULL;
	subparse->limitCount = (Node *) makeConst(INT8OID, sizeof(int64),
											  Int64GetDatum(1),
											  false, false  );


	plan = create_plan(&subroot, (Path *) info->path);

	plan->targetlist = copyObject(subparse->targetList);

	if (IsA(plan, Result))
		iplan = plan->lefttree;
	else
		iplan = plan;
	Assert(IsA(iplan, IndexScan));

	ntest = makeNode(NullTest);
	ntest->nulltesttype = IS_NOT_NULL;
	ntest->arg = copyObject(info->target);

	iplan->qual = lcons(ntest, iplan->qual);

	plan = (Plan *) make_limit(plan,
							   subparse->limitOffset,
							   subparse->limitCount,
							   0, 1);


	info->param = SS_make_initplan_from_plan(&subroot, plan,
											 exprType((Node *) tle->expr),
											 -1);
}
