AppendToRedobuffLit(
    char_u	*str,
    int		len)
{
    char_u	*s = str;
    int		c;
    char_u	*start;

    if (block_redo)
	return;

    while (len < 0 ? *s != NUL : s - str < len)
    {


	start = s;
	while (*s >= ' '
#ifndef EBCDIC
		&& *s < DEL
#endif
		&& (len < 0 || s - str < len))
	    ++s;


	if (*s == NUL && (s[-1] == '0' || s[-1] == '^'))
	    --s;
	if (s > start)
	    add_buff(&redobuff, start, (long)(s - start));

	if (*s == NUL || (len >= 0 && s - str >= len))
	    break;


	if (has_mbyte)

	    c = mb_cptr2char_adv(&s);
	else
	    c = *s++;
	if (c < ' ' || c == DEL || (*s == NUL && (c == '0' || c == '^')))
	    add_char_buff(&redobuff, Ctrl_V);


	if (*s == NUL && c == '0')
#ifdef EBCDIC
	    add_buff(&redobuff, (char_u *)"xf0", 3L);
#else
	    add_buff(&redobuff, (char_u *)"048", 3L);
#endif
	else
	    add_char_buff(&redobuff, c);
    }
}
