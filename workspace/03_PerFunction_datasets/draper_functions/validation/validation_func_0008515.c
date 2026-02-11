uniquify_deps(char **deps)
{
	unsigned int i, j, num;

	num = talloc_array_length(deps) - 1;
	for (i = 0; i < num; i++) {
		for (j = i + 1; j < num; j++) {
			if (streq(deps[i], deps[j])) {
				memmove(&deps[j], &deps[j+1],
					(num - j - 1) * sizeof(char *));
				num--;
			}
		}
	}
	deps[num] = NULL;

	return talloc_realloc(NULL, deps, char *, num + 1);
}
