create_hashjoin_plan(PlannerInfo *root,
					 HashPath *best_path,
					 Plan *outer_plan,
					 Plan *inner_plan)
{
	List	   *tlist = build_path_tlist(root, &best_path->jpath.path);
	List	   *joinclauses;
	List	   *otherclauses;
	List	   *hashclauses;
	Oid			skewTable = InvalidOid;
	AttrNumber	skewColumn = InvalidAttrNumber;
	bool		skewInherit = false;
	Oid			skewColType = InvalidOid;
	int32		skewColTypmod = -1;
	HashJoin   *join_plan;
	Hash	   *hash_plan;


	joinclauses = order_qual_clauses(root, best_path->jpath.joinrestrictinfo);


	if (IS_OUTER_JOIN(best_path->jpath.jointype))
	{
		extract_actual_join_clauses(joinclauses,
									&joinclauses, &otherclauses);
	}
	else
	{

		joinclauses = extract_actual_clauses(joinclauses, false);
		otherclauses = NIL;
	}


	hashclauses = get_actual_clauses(best_path->path_hashclauses);
	joinclauses = list_difference(joinclauses, hashclauses);


	if (best_path->jpath.path.param_info)
	{
		joinclauses = (List *)
			replace_nestloop_params(root, (Node *) joinclauses);
		otherclauses = (List *)
			replace_nestloop_params(root, (Node *) otherclauses);
	}


	hashclauses = get_switched_clauses(best_path->path_hashclauses,
							 best_path->jpath.outerjoinpath->parent->relids);


	disuse_physical_tlist(root, inner_plan, best_path->jpath.innerjoinpath);


	if (best_path->num_batches > 1)
		disuse_physical_tlist(root, outer_plan, best_path->jpath.outerjoinpath);


	if (list_length(hashclauses) == 1)
	{
		OpExpr	   *clause = (OpExpr *) linitial(hashclauses);
		Node	   *node;

		Assert(is_opclause(clause));
		node = (Node *) linitial(clause->args);
		if (IsA(node, RelabelType))
			node = (Node *) ((RelabelType *) node)->arg;
		if (IsA(node, Var))
		{
			Var		   *var = (Var *) node;
			RangeTblEntry *rte;

			rte = root->simple_rte_array[var->varno];
			if (rte->rtekind == RTE_RELATION)
			{
				skewTable = rte->relid;
				skewColumn = var->varattno;
				skewInherit = rte->inh;
				skewColType = var->vartype;
				skewColTypmod = var->vartypmod;
			}
		}
	}


	hash_plan = make_hash(inner_plan,
						  skewTable,
						  skewColumn,
						  skewInherit,
						  skewColType,
						  skewColTypmod);
	join_plan = make_hashjoin(tlist,
							  joinclauses,
							  otherclauses,
							  hashclauses,
							  outer_plan,
							  (Plan *) hash_plan,
							  best_path->jpath.jointype);

	copy_path_costsize(&join_plan->join.plan, &best_path->jpath.path);

	return join_plan;
}
