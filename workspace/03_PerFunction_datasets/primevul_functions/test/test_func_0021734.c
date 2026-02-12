transchar_nonprint(buf_T *buf, char_u *charbuf, int c)
{
    if (c == NL)
	c = NUL;
    else if (c == CAR && get_fileformat(buf) == EOL_MAC)
	c = NL;

    if (dy_flags & DY_UHEX)
	transchar_hex(charbuf, c);

#ifdef EBCDIC

    else if (CtrlChar(c) != 0 || c == DEL)
#else
    else if (c <= 0x7f)
#endif
    {
	charbuf[0] = '^';
#ifdef EBCDIC
	if (c == DEL)
	    charbuf[1] = '?';
	else
	    charbuf[1] = CtrlChar(c);
#else
	charbuf[1] = c ^ 0x40;
#endif

	charbuf[2] = NUL;
    }
    else if (enc_utf8 && c >= 0x80)
    {
	transchar_hex(charbuf, c);
    }
#ifndef EBCDIC
    else if (c >= ' ' + 0x80 && c <= '~' + 0x80)
    {
	charbuf[0] = '|';
	charbuf[1] = c - 0x80;
	charbuf[2] = NUL;
    }
#else
    else if (c < 64)
    {
	charbuf[0] = '~';
	charbuf[1] = MetaChar(c);
	charbuf[2] = NUL;
    }
#endif
    else
    {


	charbuf[0] = '~';
#ifdef EBCDIC
	charbuf[1] = '?';
#else
	charbuf[1] = (c - 0x80) ^ 0x40;
#endif
	charbuf[2] = NUL;
    }
}
