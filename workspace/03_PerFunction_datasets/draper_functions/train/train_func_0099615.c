NextHeader(p)
    register char	*p;
{
    for ( ; (p = strchr(p, '\n')) != NULL; p++) {
	if (ISWHITE(p[1]))
	    continue;
	*p = '\0';
	return p + 1;
    }
    return NULL;
}
