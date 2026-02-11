hash_write(struct ast_channel *chan, const char *cmd, char *var, const char *value)
{
	char varname[256];
	AST_DECLARE_APP_ARGS(arg,
		AST_APP_ARG(hashname);
		AST_APP_ARG(hashkey);
	);

	if (!strchr(var, ',')) {

		return array(chan, "HASH", var, value);
	}

	AST_STANDARD_APP_ARGS(arg, var);
	if (arg.hashname[0] == '_') {
		if (arg.hashname[1] == '_') {
			snprintf(varname, sizeof(varname), "__" HASH_FORMAT, arg.hashname + 2, arg.hashkey);
		} else {
			snprintf(varname, sizeof(varname), "_" HASH_FORMAT, arg.hashname + 1, arg.hashkey);
		}
	} else {
		snprintf(varname, sizeof(varname), HASH_FORMAT, arg.hashname, arg.hashkey);
	}
	pbx_builtin_setvar_helper(chan, varname, value);

	return 0;
}
