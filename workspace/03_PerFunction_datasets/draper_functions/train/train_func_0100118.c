load_module(void)
{
	if(!reload_followme(0))
		return AST_MODULE_LOAD_DECLINE;

	return ast_register_application_xml(app, app_exec);
}
