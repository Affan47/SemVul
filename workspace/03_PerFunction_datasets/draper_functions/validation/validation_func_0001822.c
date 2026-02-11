get_fn_expr_variadic(FmgrInfo *flinfo)
{
	Node	   *expr;


	if (!flinfo || !flinfo->fn_expr)
		return false;

	expr = flinfo->fn_expr;

	if (IsA(expr, FuncExpr))
		return ((FuncExpr *) expr)->funcvariadic;
	else
		return false;
}
