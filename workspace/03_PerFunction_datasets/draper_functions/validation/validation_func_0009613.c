set_string(dbString * x, char *s, int copy)
{
    int len;
    int stat;

    if (s == NULL) {
	s = "";
	copy = 1;
    }

    len = strlen(s) + 1;

    if (copy) {
	stat = db_enlarge_string(x, len);
	if (stat != DB_OK)
	    return stat;
	strcpy(x->string, s);
    }
    else {
	db_free_string(x);
	x->string = s;
	x->nalloc = -1;
    }
    return DB_OK;
}
