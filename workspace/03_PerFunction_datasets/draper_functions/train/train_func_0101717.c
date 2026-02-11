load_module(void)
{
	if (AST_RWLIST_WRLOCK(&odbc_tables)) {
		ast_log(LOG_ERROR, "Unable to lock column list.  Load failed.\n");
		return 0;
	}

	load_config();
	AST_RWLIST_UNLOCK(&odbc_tables);
	ast_cdr_register(name, ast_module_info->description, odbc_log);
	return 0;
}
