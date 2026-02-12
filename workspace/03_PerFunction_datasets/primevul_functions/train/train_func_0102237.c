captype(
    char_u	*word,
    char_u	*end)
{
    char_u	*p;
    int		c;
    int		firstcap;
    int		allcap;
    int		past_second = FALSE;


    for (p = word; !spell_iswordp_nmw(p, curwin); MB_PTR_ADV(p))
	if (end == NULL ? *p == NUL : p >= end)
	    return 0;
    if (has_mbyte)
	c = mb_ptr2char_adv(&p);
    else
	c = *p++;
    firstcap = allcap = SPELL_ISUPPER(c);


    for ( ; end == NULL ? *p != NUL : p < end; MB_PTR_ADV(p))
	if (spell_iswordp_nmw(p, curwin))
	{
	    c = PTR2CHAR(p);
	    if (!SPELL_ISUPPER(c))
	    {

		if (past_second && allcap)
		    return WF_KEEPCAP;
		allcap = FALSE;
	    }
	    else if (!allcap)

		return WF_KEEPCAP;
	    past_second = TRUE;
	}

    if (allcap)
	return WF_ALLCAP;
    if (firstcap)
	return WF_ONECAP;
    return 0;
}
