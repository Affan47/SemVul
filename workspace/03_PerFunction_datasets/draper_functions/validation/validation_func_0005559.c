gda_sql_statement_copy (GdaSqlStatement *stmt)
{
	GdaSqlStatement *copy;
	GdaSqlStatementContentsInfo *infos;

	if (!stmt)
		return NULL;

	infos = gda_sql_statement_get_contents_infos (stmt->stmt_type);
	copy = g_new0 (GdaSqlStatement, 1);
	copy->stmt_type = stmt->stmt_type;

	if (stmt->sql)
		copy->sql = g_strdup (stmt->sql);
	if (infos && infos->copy) {
		copy->contents = infos->copy (stmt->contents);
		GDA_SQL_ANY_PART (copy->contents)->type = GDA_SQL_ANY_PART (stmt->contents)->type;
	}
	else if (infos && infos->construct) {
		copy->contents = infos->construct ();
		GDA_SQL_ANY_PART (copy->contents)->type = stmt->stmt_type;
	}
	else
		TO_IMPLEMENT;
	if (stmt->validity_meta_struct) {
		copy->validity_meta_struct = stmt->validity_meta_struct;
		g_object_ref (copy->validity_meta_struct);
	}

	return copy;
}
