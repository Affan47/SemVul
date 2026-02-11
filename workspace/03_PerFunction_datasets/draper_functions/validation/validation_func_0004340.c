create_scan_plan(PlannerInfo *root, Path *best_path)
{
	RelOptInfo *rel = best_path->parent;
	List	   *tlist;
	List	   *scan_clauses;
	Plan	   *plan;


	if (use_physical_tlist(rel))
	{
		tlist = build_physical_tlist(root, rel);

		if (tlist == NIL)
			tlist = build_relation_tlist(rel);
	}
	else
		tlist = build_relation_tlist(rel);


	scan_clauses = rel->baserestrictinfo;

	switch (best_path->pathtype)
	{
		case T_SeqScan:
			plan = (Plan *) create_seqscan_plan(root,
												best_path,
												tlist,
												scan_clauses);
			break;

		case T_IndexScan:
			plan = (Plan *) create_indexscan_plan(root,
												  (IndexPath *) best_path,
												  tlist,
												  scan_clauses,
												  NULL);
			break;

		case T_BitmapHeapScan:
			plan = (Plan *) create_bitmap_scan_plan(root,
												(BitmapHeapPath *) best_path,
													tlist,
													scan_clauses);
			break;

		case T_TidScan:
			plan = (Plan *) create_tidscan_plan(root,
												(TidPath *) best_path,
												tlist,
												scan_clauses);
			break;

		case T_SubqueryScan:
			plan = (Plan *) create_subqueryscan_plan(root,
													 best_path,
													 tlist,
													 scan_clauses);
			break;

		case T_FunctionScan:
			plan = (Plan *) create_functionscan_plan(root,
													 best_path,
													 tlist,
													 scan_clauses);
			break;

		case T_ValuesScan:
			plan = (Plan *) create_valuesscan_plan(root,
												   best_path,
												   tlist,
												   scan_clauses);
			break;

		default:
			elog(ERROR, "unrecognized node type: %d",
				 (int) best_path->pathtype);
			plan = NULL;
			break;
	}


	if (root->hasPseudoConstantQuals)
		plan = create_gating_plan(root, plan, scan_clauses);

	return plan;
}
