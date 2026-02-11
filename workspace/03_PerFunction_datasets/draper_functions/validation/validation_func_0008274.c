match_clause_to_ordering_op(IndexOptInfo *index,
							int indexcol,
							Expr *clause,
							Oid pk_opfamily)
{
	Oid			opfamily = index->opfamily[indexcol];
	Oid			idxcollation = index->indexcollations[indexcol];
	Node	   *leftop,
			   *rightop;
	Oid			expr_op;
	Oid			expr_coll;
	Oid			sortfamily;
	bool		commuted;


	if (!is_opclause(clause))
		return NULL;
	leftop = get_leftop(clause);
	rightop = get_rightop(clause);
	if (!leftop || !rightop)
		return NULL;
	expr_op = ((OpExpr *) clause)->opno;
	expr_coll = ((OpExpr *) clause)->inputcollid;


	if (!IndexCollMatchesExprColl(idxcollation, expr_coll))
		return NULL;


	if (match_index_to_operand(leftop, indexcol, index) &&
		!contain_var_clause(rightop) &&
		!contain_volatile_functions(rightop))
	{
		commuted = false;
	}
	else if (match_index_to_operand(rightop, indexcol, index) &&
			 !contain_var_clause(leftop) &&
			 !contain_volatile_functions(leftop))
	{

		expr_op = get_commutator(expr_op);
		if (expr_op == InvalidOid)
			return NULL;
		commuted = true;
	}
	else
		return NULL;


	sortfamily = get_op_opfamily_sortfamily(expr_op, opfamily);
	if (sortfamily != pk_opfamily)
		return NULL;


	if (commuted)
	{
		OpExpr	   *newclause = makeNode(OpExpr);


		memcpy(newclause, clause, sizeof(OpExpr));


		newclause->opno = expr_op;
		newclause->opfuncid = InvalidOid;
		newclause->args = list_make2(rightop, leftop);

		clause = (Expr *) newclause;
	}

	return clause;
}
