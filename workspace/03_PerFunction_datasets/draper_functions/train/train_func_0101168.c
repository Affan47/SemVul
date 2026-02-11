next_node_name(char **path)
{
	char *res;

	do {
		res = strsep(path, "/");
	} while (res && ast_strlen_zero(res));

	return res;
}
