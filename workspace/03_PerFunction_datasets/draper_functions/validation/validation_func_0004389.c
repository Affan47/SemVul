gnm_expr_new_funcallv (GnmFunc *func, int argc, GnmExprConstPtr *argv)
{
	GnmExprFunction *ans;
	g_return_val_if_fail (func, NULL);

	ans = CHUNK_ALLOC (GnmExprFunction, expression_pool_small);

	ans->oper = GNM_EXPR_OP_FUNCALL;
	gnm_func_ref (func);
	ans->func = func;
	ans->argc = argc;
	ans->argv = argv;

	return (GnmExpr *)ans;
}
