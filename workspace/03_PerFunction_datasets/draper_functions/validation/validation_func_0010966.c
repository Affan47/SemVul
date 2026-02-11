gnm_cell_set_expr (GnmCell *cell, GnmExprTop const *texpr)
{
	g_return_if_fail (!gnm_cell_is_nonsingleton_array (cell));
	g_return_if_fail (cell != NULL);
	g_return_if_fail (texpr != NULL);

	cell_set_expr_internal (cell, texpr);
	dependent_link (GNM_CELL_TO_DEP (cell));
}
