expandNextArg(poptContext con, const char * s)
{
    const char *a;
    size_t alen;
    char *t, *te;
    size_t tn = strlen(s) + 1;
    char c;

    te = t = (char*)malloc(tn);;
    while ((c = *s++) != '\0') {
	switch (c) {
#if 0
	case '\\':
	    c = *s++;
	    break;
#endif
	case '!':
	    if (!(s[0] == '#' && s[1] == ':' && s[2] == '+'))
		break;
	    if ((a = findNextArg(con, 1, 1)) == NULL)
		break;
	    s += 3;

	    alen = strlen(a);
	    tn += alen;
	    *te = '\0';
	    t = (char*)realloc(t, tn);
	    te = t + strlen(t);
	    strncpy(te, a, alen); te += alen;
	    continue;
	     break;
	default:
	    break;
	}
	*te++ = c;
    }
    *te = '\0';
    t = (char*)realloc(t, strlen(t)+1);
    return t;
}
