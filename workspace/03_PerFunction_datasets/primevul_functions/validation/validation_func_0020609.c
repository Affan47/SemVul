tag_fgets(char_u *buf, int size, FILE *fp)
{
    int		i = 0;
    int		c;
    int		eof = FALSE;

    for (;;)
    {
	c = fgetc(fp);
	if (c == EOF)
	{
	    eof = TRUE;
	    break;
	}
	if (c == '\r')
	{

	    if (i < size - 1)
		buf[i++] = '\n';
	    c = fgetc(fp);
	    if (c != '\n')
		ungetc(c, fp);
	    break;
	}
	if (i < size - 1)
	    buf[i++] = c;
	if (c == '\n')
	    break;
    }
    buf[i] = NUL;
    return eof;
}
