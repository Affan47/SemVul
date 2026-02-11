db_syserror(const char *s)
{
    char lead[1024];
    char msg[1024];


    err_flag = 0;
    if (errno <= 0)
	return;

    *lead = 0;
    if (who)
	sprintf(lead, "%s: ", who);

    if (errno > 0)
	sprintf(msg, "%s%s: %s", lead, strerror(errno), s);

    db_error(msg);
}
