help_compare(const void *s1, const void *s2)
{
    char    *p1;
    char    *p2;
    int	    cmp;

    p1 = *(char **)s1 + strlen(*(char **)s1) + 1;
    p2 = *(char **)s2 + strlen(*(char **)s2) + 1;


    cmp = strcmp(p1, p2);
    if (cmp != 0)
	return cmp;


    return strcmp(*(char **)s1, *(char **)s2);
}
