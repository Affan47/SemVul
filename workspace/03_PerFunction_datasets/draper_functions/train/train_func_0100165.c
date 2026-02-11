pool_strdup_withterm(POOL *pool, const char *string, int term)
{
	const char *p = strchr(string, term);
	int size = p ? p - string : strlen(string);
	return obstack_copy0(&pool->obstack, string, size);
}
