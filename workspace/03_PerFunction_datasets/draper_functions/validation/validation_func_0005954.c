arg_pgno(char *p, int *subno)
{
    char *end;
    int pgno;

    *subno = ANY_SUB;
    if (*p)
    {
	pgno = strtol(p, &end, 16);
	if ((*end == ':' || *end == '/' || *end == '.') && end[1])
	    *subno = strtol(end + 1, &end, 16);
	if (*end == 0)
	    if (pgno >= 0x100 && pgno <= 0x899)
		if (*subno == ANY_SUB || (*subno >= 0x00 && *subno <= 0x3f7f))
		    return pgno;
    }
    fatal("%s: invalid page number", p);
}
