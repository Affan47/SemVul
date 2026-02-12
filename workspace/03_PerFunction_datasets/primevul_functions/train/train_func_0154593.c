langmap_set(void)
{
    char_u  *p;
    char_u  *p2;
    int	    from, to;

#ifdef FEAT_MBYTE
    ga_clear(&langmap_mapga);
#endif
    langmap_init();

    for (p = p_langmap; p[0] != NUL; )
    {
	for (p2 = p; p2[0] != NUL && p2[0] != ',' && p2[0] != ';';
							       mb_ptr_adv(p2))
	{
	    if (p2[0] == '\\' && p2[1] != NUL)
		++p2;
	}
	if (p2[0] == ';')
	    ++p2;
	else
	    p2 = NULL;
	while (p[0])
	{
	    if (p[0] == ',')
	    {
		++p;
		break;
	    }
	    if (p[0] == '\\' && p[1] != NUL)
		++p;
#ifdef FEAT_MBYTE
	    from = (*mb_ptr2char)(p);
#else
	    from = p[0];
#endif
	    to = NUL;
	    if (p2 == NULL)
	    {
		mb_ptr_adv(p);
		if (p[0] != ',')
		{
		    if (p[0] == '\\')
			++p;
#ifdef FEAT_MBYTE
		    to = (*mb_ptr2char)(p);
#else
		    to = p[0];
#endif
		}
	    }
	    else
	    {
		if (p2[0] != ',')
		{
		    if (p2[0] == '\\')
			++p2;
#ifdef FEAT_MBYTE
		    to = (*mb_ptr2char)(p2);
#else
		    to = p2[0];
#endif
		}
	    }
	    if (to == NUL)
	    {
		EMSG2(_("E357: 'langmap': Matching character missing for %s"),
							     transchar(from));
		return;
	    }

#ifdef FEAT_MBYTE
	    if (from >= 256)
		langmap_set_entry(from, to);
	    else
#endif
		langmap_mapchar[from & 255] = to;


	    mb_ptr_adv(p);
	    if (p2 != NULL)
	    {
		mb_ptr_adv(p2);
		if (*p == ';')
		{
		    p = p2;
		    if (p[0] != NUL)
		    {
			if (p[0] != ',')
			{
			    EMSG2(_("E358: 'langmap': Extra characters after semicolon: %s"), p);
			    return;
			}
			++p;
		    }
		    break;
		}
	    }
	}
    }
}
