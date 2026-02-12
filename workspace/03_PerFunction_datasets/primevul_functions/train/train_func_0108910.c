gotchars(char_u *chars, int len)
{
    char_u		*s = chars;
    int			i;
    static char_u	buf[4];
    static int		buflen = 0;
    int			todo = len;

    while (todo--)
    {
	buf[buflen++] = *s++;


	if (buflen == 1 && buf[0] == K_SPECIAL)
	    continue;
	if (buflen == 2)
	    continue;
	if (buflen == 3 && buf[1] == KS_EXTRA
		       && (buf[2] == KE_FOCUSGAINED || buf[2] == KE_FOCUSLOST))
	{


	    buflen = 0;
	    continue;
	}


	for (i = 0; i < buflen; ++i)
	    updatescript(buf[i]);

	if (reg_recording != 0)
	{
	    buf[buflen] = NUL;
	    add_buff(&recordbuff, buf, (long)buflen);

	    last_recorded_len += buflen;
	}
	buflen = 0;
    }
    may_sync_undo();

#ifdef FEAT_EVAL

    debug_did_msg = FALSE;
#endif


    ++maptick;
}
