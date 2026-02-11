qpol_cond_expr_node_get_expr_type(const qpol_policy_t * policy, const qpol_cond_expr_node_t * node, uint32_t * expr_type)
{
	cond_expr_t *internal_cond = NULL;

	if (expr_type)
		*expr_type = 0;

	if (!policy || !node || !expr_type) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_cond = (cond_expr_t *) node;

	*expr_type = internal_cond->expr_type;

	return STATUS_SUCCESS;
}
