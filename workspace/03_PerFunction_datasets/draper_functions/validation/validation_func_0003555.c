ast_verbose_get_by_module(const char *module)
{
	struct module_level *ml;
	unsigned int res = 0;

	AST_RWLIST_RDLOCK(&verbose_modules);
	AST_LIST_TRAVERSE(&verbose_modules, ml, entry) {
		if (!strcasecmp(ml->module, module)) {
			res = ml->level;
			break;
		}
	}
	AST_RWLIST_UNLOCK(&verbose_modules);

	return res;
}
