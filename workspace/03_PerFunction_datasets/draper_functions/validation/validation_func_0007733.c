append_var_and_value_to_filter(struct ast_str **filter,
	struct ldap_table_config *table_config,
	const char *name, const char *value)
{
	char *new_name = NULL;
	char *new_value = NULL;
	char *like_pos = strstr(name, " LIKE");

	ast_debug(2, "name='%s' value='%s'\n", name, value);

	if (like_pos) {
		int len = like_pos - name;

		name = new_name = ast_strdupa(name);
		new_name[len] = '\0';
		value = new_value = ast_strdupa(value);
		replace_string_in_string(new_value, "\\_", "_");
		replace_string_in_string(new_value, "%", "*");
	}

	name = convert_attribute_name_to_ldap(table_config, name);

	ast_str_append(filter, 0, "(%s=%s)", name, value);
}
