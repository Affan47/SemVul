script_var_changed(const char *var) {
	script_var_t	 *temp = script_var_find(var);

	SCRIPT_HANDLER_HEADER(script_handler_var_t);

	SCRIPT_HANDLER_MULTI_FOOTER(script_handler_var, temp->value);
	return;
}
