plpgsql_pre_column_ref(ParseState *pstate, ColumnRef *cref)
{
	PLpgSQL_expr *expr = (PLpgSQL_expr *) pstate->p_ref_hook_state;

	if (expr->func->resolve_option == PLPGSQL_RESOLVE_VARIABLE)
		return resolve_column_ref(pstate, expr, cref, false);
	else
		return NULL;
}
