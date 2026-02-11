gnm_expr_get_func_def (GnmExpr const *expr)
{
	g_return_val_if_fail (expr != NULL, NULL);
	g_return_val_if_fail (GNM_EXPR_GET_OPER (expr) == GNM_EXPR_OP_FUNCALL, NULL);

	return expr->func.func;
}
