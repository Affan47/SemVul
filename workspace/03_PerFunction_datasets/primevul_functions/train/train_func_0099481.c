msg_strtrunc(
    char_u	*s,
    int		force)
{
    char_u	*buf = NULL;
    int		len;
    int		room;


    if ((!msg_scroll && !need_wait_return && shortmess(SHM_TRUNCALL)
			       && !exmode_active && msg_silent == 0) || force)
    {
	len = vim_strsize(s);
	if (msg_scrolled != 0)

	    room = (int)(Rows - msg_row) * Columns - 1;
	else

	    room = (int)(Rows - msg_row - 1) * Columns + sc_col - 1;
	if (len > room && room > 0)
	{
	    if (enc_utf8)


		len = (room + 2) * 18;
	    else if (enc_dbcs == DBCS_JPNU)

		len = (room + 2) * 2;
	    else
		len = room + 2;
	    buf = alloc(len);
	    if (buf != NULL)
		trunc_string(s, buf, room, len);
	}
    }
    return buf;
}
