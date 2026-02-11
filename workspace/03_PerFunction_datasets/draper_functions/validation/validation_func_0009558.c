transformAExprOf(ParseState *pstate, A_Expr *a)
{


	Node	   *lexpr = transformExpr(pstate, a->lexpr);
	Const	   *result;
	ListCell   *telem;
	Oid			ltype,
				rtype;
	bool		matched = false;

	ltype = exprType(lexpr);
	foreach(telem, (List *) a->rexpr)
	{
		rtype = typenameTypeId(pstate, lfirst(telem), NULL);
		matched = (rtype == ltype);
		if (matched)
			break;
	}


	if (strcmp(strVal(linitial(a->name)), "<>") == 0)
		matched = (!matched);

	result = (Const *) makeBoolConst(matched, false);


	result->location = exprLocation((Node *) a);

	return (Node *) result;
}
