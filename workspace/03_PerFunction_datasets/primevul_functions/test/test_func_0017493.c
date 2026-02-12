get_bytes_from_buf(char_u *buf, char_u *bytes, int num_bytes)
{
    int	    len = 0;
    int	    i;
    char_u  c;

    for (i = 0; i < num_bytes; i++)
    {
	if ((c = buf[len++]) == NUL)
	    return -1;
	if (c == K_SPECIAL)
	{
	    if (buf[len] == NUL || buf[len + 1] == NUL)
		return -1;
	    if (buf[len++] == (int)KS_ZERO)
		c = NUL;


	    if (buf[len++] == (int)KE_CSI)
		c = CSI;
	}
	else if (c == CSI && buf[len] == KS_EXTRA
					       && buf[len + 1] == (int)KE_CSI)


	    len += 2;
	bytes[i] = c;
    }
    return len;
}
