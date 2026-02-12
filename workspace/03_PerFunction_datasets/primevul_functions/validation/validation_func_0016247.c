stuffescaped(char_u *arg, int literally)
{
    int		c;
    char_u	*start;

    while (*arg != NUL)
    {


	start = arg;
	while ((*arg >= ' '
#ifndef EBCDIC
		    && *arg < DEL
#endif
		    )
		|| (*arg == K_SPECIAL && !literally))
	    ++arg;
	if (arg > start)
	    stuffReadbuffLen(start, (long)(arg - start));


	if (*arg != NUL)
	{
	    if (has_mbyte)
		c = mb_cptr2char_adv(&arg);
	    else
		c = *arg++;
	    if (literally && ((c < ' ' && c != TAB) || c == DEL))
		stuffcharReadbuff(Ctrl_V);
	    stuffcharReadbuff(c);
	}
    }
}
