set_sofo(slang_T *lp, char_u *from, char_u *to)
{
    int		i;

#ifdef FEAT_MBYTE
    garray_T	*gap;
    char_u	*s;
    char_u	*p;
    int		c;
    int		*inp;

    if (has_mbyte)
    {


	gap = &lp->sl_sal;
	ga_init2(gap, sizeof(int *), 1);
	if (ga_grow(gap, 256) == FAIL)
	    return SP_OTHERERROR;
	vim_memset(gap->ga_data, 0, sizeof(int *) * 256);
	gap->ga_len = 256;


	for (p = from, s = to; *p != NUL && *s != NUL; )
	{
	    c = mb_cptr2char_adv(&p);
	    mb_cptr_adv(s);
	    if (c >= 256)
		++lp->sl_sal_first[c & 0xff];
	}
	if (*p != NUL || *s != NUL)
	    return SP_FORMERROR;


	for (i = 0; i < 256; ++i)
	    if (lp->sl_sal_first[i] > 0)
	    {
		p = alloc(sizeof(int) * (lp->sl_sal_first[i] * 2 + 1));
		if (p == NULL)
		    return SP_OTHERERROR;
		((int **)gap->ga_data)[i] = (int *)p;
		*(int *)p = 0;
	    }


	vim_memset(lp->sl_sal_first, 0, sizeof(salfirst_T) * 256);
	for (p = from, s = to; *p != NUL && *s != NUL; )
	{
	    c = mb_cptr2char_adv(&p);
	    i = mb_cptr2char_adv(&s);
	    if (c >= 256)
	    {


		inp = ((int **)gap->ga_data)[c & 0xff];
		while (*inp != 0)
		    ++inp;
		*inp++ = c;
		*inp++ = i;
		*inp++ = NUL;
	    }
	    else

		lp->sl_sal_first[c] = i;
	}
    }
    else
#endif
    {

	if (STRLEN(from) != STRLEN(to))
	    return SP_FORMERROR;

	for (i = 0; to[i] != NUL; ++i)
	    lp->sl_sal_first[from[i]] = to[i];
	lp->sl_sal.ga_len = 1;
    }

    return 0;
}
