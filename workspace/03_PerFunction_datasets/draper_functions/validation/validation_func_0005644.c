branch_if_lesser_stmt(struct basic_block *target,
					       struct expression *left,
					       int32_t right)
{
	struct expression *right_expr;

	right_expr = value_expr(J_INT, right);
	if (!right_expr)
		return NULL;

	return if_stmt(target, J_INT, OP_LT, left, right_expr);
}
