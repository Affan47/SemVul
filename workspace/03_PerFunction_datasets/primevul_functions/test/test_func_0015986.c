transchar_buf(buf_T *buf, int c)
{
    int			i;

    i = 0;
    if (IS_SPECIAL(c))
    {
	transchar_charbuf[0] = '~';
	transchar_charbuf[1] = '@';
	i = 2;
	c = K_SECOND(c);
    }

    if ((!chartab_initialized && ((c >= ' ' && c <= '~')))
					|| (c < 256 && vim_isprintc_strict(c)))
    {

	transchar_charbuf[i] = c;
	transchar_charbuf[i + 1] = NUL;
    }
    else
	transchar_nonprint(buf, transchar_charbuf + i, c);
    return transchar_charbuf;
}
