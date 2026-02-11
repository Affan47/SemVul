build_joinrel_tlist(PlannerInfo *root, RelOptInfo *joinrel,
					RelOptInfo *input_rel)
{
	Relids		relids = joinrel->relids;
	ListCell   *vars;

	foreach(vars, input_rel->reltargetlist)
	{
		Node	   *origvar = (Node *) lfirst(vars);
		Var		   *var;
		RelOptInfo *baserel;
		int			ndx;


		if (IsA(origvar, PlaceHolderVar))
			continue;


		var = (Var *) origvar;
		while (!IsA(var, Var))
		{
			if (IsA(var, ConvertRowtypeExpr))
				var = (Var *) ((ConvertRowtypeExpr *) var)->arg;
			else
				elog(ERROR, "unexpected node type in reltargetlist: %d",
					 (int) nodeTag(var));
		}


		baserel = find_base_rel(root, var->varno);


		ndx = var->varattno - baserel->min_attr;
		if (bms_nonempty_difference(baserel->attr_needed[ndx], relids))
		{

			joinrel->reltargetlist = lappend(joinrel->reltargetlist, origvar);
			joinrel->width += baserel->attr_widths[ndx];
		}
	}
}
