printdigraph(p)
	char_u *p;
{
	char_u		buf[9];
	static int	len;

	if (p == NULL)
		len = 0;
	else if (p[2] != 0)
	{
		if (len > Columns - 11)
		{
			msg_outchar('\n');
			len = 0;
		}
		if (len)
			msg_outstr((char_u *)"   ");
		sprintf((char *)buf, "%c%c %c %3d", p[0], p[1], p[2], p[2]);
		msg_outstr(buf);
		len += 11;
	}
}
