xstrsep(char *str)
{
    int i = 0, size = 10;
    char **list = (char **) xmalloc(size * sizeof(char *));
    char *ptr = str, *nptr;
    while ((nptr = strchr(ptr, ',')) != 0L)
    {
	if (i > size-2)
	    list = xrealloc(list, (size *= 2) * sizeof(char *));
	*nptr = '\000';
	list[i++] = ptr;
	ptr = nptr+1;
    }
    if (*ptr != '\000')
	list[i++] = ptr;
    list[i] = 0L;
    return list;
}
