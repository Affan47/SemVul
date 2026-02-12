bytes2offset(char_u **pp)
{
    char_u	*p = *pp;
    int		nr;
    int		c;

    c = *p++;
    if ((c & 0x80) == 0x00)
    {
	nr = c - 1;
    }
    else if ((c & 0xc0) == 0x80)
    {
	nr = (c & 0x3f) - 1;
	nr = nr * 255 + (*p++ - 1);
    }
    else if ((c & 0xe0) == 0xc0)
    {
	nr = (c & 0x1f) - 1;
	nr = nr * 255 + (*p++ - 1);
	nr = nr * 255 + (*p++ - 1);
    }
    else
    {
	nr = (c & 0x0f) - 1;
	nr = nr * 255 + (*p++ - 1);
	nr = nr * 255 + (*p++ - 1);
	nr = nr * 255 + (*p++ - 1);
    }

    *pp = p;
    return nr;
}
