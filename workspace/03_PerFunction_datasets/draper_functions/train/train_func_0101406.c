db__send_char(int d)
{
    int stat = DB_OK;
    char c = (char)d;

    if (!db__send(&c, sizeof(c)))
	stat = DB_PROTOCOL_ERR;

    if (stat == DB_PROTOCOL_ERR)
	db_protocol_error();

    return stat;
}
