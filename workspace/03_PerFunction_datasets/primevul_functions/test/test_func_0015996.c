transchar_nonprint(buf_T *buf, char_u *charbuf, int c)
{
    if (c == NL)
	c = NUL;
    else if (c == CAR && get_fileformat(buf) == EOL_MAC)
	c = NL;

    if (dy_flags & DY_UHEX)
	transchar_hex(charbuf, c);

    else if (c <= 0x7f)
    {
	charbuf[0] = '^';
	charbuf[1] = c ^ 0x40;
	charbuf[2] = NUL;
    }
    else if (enc_utf8 && c >= 0x80)
    {
	transchar_hex(charbuf, c);
    }
    else if (c >= ' ' + 0x80 && c <= '~' + 0x80)
    {
	charbuf[0] = '|';
	charbuf[1] = c - 0x80;
	charbuf[2] = NUL;
    }
    else
    {
	charbuf[0] = '~';
	charbuf[1] = (c - 0x80) ^ 0x40;
	charbuf[2] = NUL;
    }
}
