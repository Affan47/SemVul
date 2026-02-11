show_plan_tlist(PlanState *planstate, List *ancestors, ExplainState *es)
{
	Plan	   *plan = planstate->plan;
	List	   *context;
	List	   *result = NIL;
	bool		useprefix;
	ListCell   *lc;


	if (plan->targetlist == NIL)
		return;

	if (IsA(plan, Append))
		return;

	if (IsA(plan, MergeAppend))
		return;
	if (IsA(plan, RecursiveUnion))
		return;


	context = set_deparse_context_planstate(es->deparse_cxt,
											(Node *) planstate,
											ancestors);
	useprefix = list_length(es->rtable) > 1;


	foreach(lc, plan->targetlist)
	{
		TargetEntry *tle = (TargetEntry *) lfirst(lc);

		result = lappend(result,
						 deparse_expression((Node *) tle->expr, context,
											useprefix, false));
	}


	ExplainPropertyList("Output", result, es);
}
