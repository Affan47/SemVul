DXLGetInputInteger(DXLConnection *conn,
    const char *macro, const char *module, const int instance, const int number,
    int *value)
{
    char rbuf[128];
    int sts;

    sts = DXLGetInputValue(conn, macro, module, instance,number,
					sizeof(rbuf), rbuf);
    if (sts == OK && sscanf(rbuf, "%d", value) != 1)
	sts = ERROR;
    return sts;
}
