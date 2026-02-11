constant_is_considered_positive(__isl_keep isl_val *v,
	__isl_keep isl_ast_expr *pos, __isl_keep isl_ast_expr *neg)
{
	if (ast_expr_is_zero(pos))
		return 1;
	if (ast_expr_is_zero(neg))
		return 0;
	return isl_val_is_pos(v);
}
