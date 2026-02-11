anewarray_expr(struct vm_class *class, struct expression *size)
{
	struct expression *expr = alloc_expression(EXPR_ANEWARRAY, J_REFERENCE);

	if (expr) {
		expr->anewarray_ref_type = class;
		expr->anewarray_size = &size->node;
	}
	return expr;
}
