load_module(void)
{
	struct ast_format tmp;
	if (!(softmix_bridge.format_capabilities = ast_format_cap_alloc())) {
		return AST_MODULE_LOAD_DECLINE;
	}
	ast_format_cap_add(softmix_bridge.format_capabilities, ast_format_set(&tmp, AST_FORMAT_SLINEAR, 0));
	return ast_bridge_technology_register(&softmix_bridge);
}
