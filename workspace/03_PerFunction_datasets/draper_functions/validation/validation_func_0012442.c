ProcessPortbase(CONSENT *c, char *id)
#else
ProcessPortbase(c, id)
    CONSENT *c;
    char *id;
#endif
{
    char *p;

    if ((id == (char *)0) || (*id == '\000')) {
	c->portbase = 0;
	return;
    }


    if (id[0] == '-' && id[1] == '1' && id[2] == '\000') {
	c->portbase = 1;
	return;
    }

    for (p = id; *p != '\000'; p++)
	if (!isdigit((int)(*p)))
	    break;


    if (*p != '\000') {
	if (isMaster)
	    Error("invalid portbase number `%s' [%s:%d]", id, file, line);
	return;
    }
    c->portbase = (unsigned short)atoi(id) + 2;
}
