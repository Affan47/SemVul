find_user_realtime(const char *domain, const char *username)
{
	struct ast_variable *var;
	struct minivm_account *retval;
	char name[MAXHOSTNAMELEN];

	retval = mvm_user_alloc();
	if (!retval)
		return NULL;

	if (username)
		ast_copy_string(retval->username, username, sizeof(retval->username));

	populate_defaults(retval);
	var = ast_load_realtime("minivm", "username", username, "domain", domain, SENTINEL);

	if (!var) {
		ast_free(retval);
		return NULL;
	}

	snprintf(name, sizeof(name), "%s@%s", username, domain);
	create_vmaccount(name, var, TRUE);

	ast_variables_destroy(var);
	return retval;
}
