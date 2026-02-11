gda_sql_builder_select_set_having (GdaSqlBuilder *builder, GdaSqlBuilderId cond_id)
{
	GdaSqlStatementSelect *sel;

	g_return_if_fail (GDA_IS_SQL_BUILDER (builder));

	if (builder->priv->main_stmt->stmt_type != GDA_SQL_STATEMENT_SELECT) {
		g_warning (_("Wrong statement type"));
		return;
	}

	SqlPart *p = NULL;
	if (cond_id > 0) {
		p = get_part (builder, cond_id, GDA_SQL_ANY_EXPR);
		if (!p)
			return;
	}

	sel = (GdaSqlStatementSelect*) builder->priv->main_stmt->contents;
	if (sel->having_cond)
		gda_sql_expr_free (sel->having_cond);
	sel->having_cond = (GdaSqlExpr*) use_part (p, GDA_SQL_ANY_PART (sel));
}
