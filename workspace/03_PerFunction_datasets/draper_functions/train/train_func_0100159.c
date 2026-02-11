load_module(void)
{
	if (!ast_module_check("res_curl.so")) {
		if (ast_load_resource("res_curl.so") != AST_MODULE_LOAD_SUCCESS) {
			ast_log(LOG_ERROR, "Cannot load res_curl, so res_config_curl cannot be loaded\n");
			return AST_MODULE_LOAD_DECLINE;
		}
	}

	if (!ast_module_check("func_curl.so")) {
		if (ast_load_resource("func_curl.so") != AST_MODULE_LOAD_SUCCESS) {
			ast_log(LOG_ERROR, "Cannot load func_curl, so res_config_curl cannot be loaded\n");
			return AST_MODULE_LOAD_DECLINE;
		}
	}

	reload_module();

	ast_config_engine_register(&curl_engine);
	ast_verb(1, "res_config_curl loaded.\n");
	return 0;
}
