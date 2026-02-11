isl_arg_str_list_append(struct isl_arg *decl, void *opt,
	const char *s)
{
	int *n = (int *)(((char *) opt) + decl->u.str_list.offset_n);
	char **list = *(char ***)(((char *) opt) + decl->offset);

	list = realloc(list, (*n + 1) * sizeof(char *));
	if (!list)
		return -1;
	*(char ***)(((char *) opt) + decl->offset) = list;
	list[*n] = strdup(s);
	(*n)++;
	return 0;
}
