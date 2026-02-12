static const char *diff_funcname_pattern(struct diff_filespec *one)
{
	const char *ident, *pattern;
	int i;

	diff_filespec_check_attr(one);
	ident = one->funcname_pattern_ident;

	if (!ident)


		return funcname_pattern("default");


	pattern = funcname_pattern(ident);
	if (pattern)
		return pattern;


	for (i = 0; i < ARRAY_SIZE(builtin_funcname_pattern); i++)
		if (!strcmp(ident, builtin_funcname_pattern[i].name))
			return builtin_funcname_pattern[i].pattern;

	return NULL;
}
