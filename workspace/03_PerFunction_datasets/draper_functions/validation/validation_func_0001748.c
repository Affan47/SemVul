amatch(pattern,start,endp)
char *pattern, *endp, *start;
{
    int sarg = arg;

    while (*pattern) {
	if (*pattern == CLOSURE) {


	    char *oldstart = start;

	    ++pattern;
	    while (start <= endp && omatch(pattern,&start,endp))
		 ;


	    patsize(&pattern);
	    while (start >= oldstart)
		if (amatch(pattern,start--,endp))
		    return TRUE;
	    arg = sarg;
	    return FALSE;
	}
	else {
	    if (!omatch(pattern,&start,endp)) {
		arg = sarg;
		return FALSE;
	    }
	    patsize(&pattern);
	}
    }
    lastp = start-core;
    return TRUE;
}
