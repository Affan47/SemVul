set_map_str(slang_T *lp, char_u *map)
{
    char_u	*p;
    int		headc = 0;
    int		c;
    int		i;

    if (*map == NUL)
    {
	lp->sl_has_map = FALSE;
	return;
    }
    lp->sl_has_map = TRUE;


    for (i = 0; i < 256; ++i)
	lp->sl_map_array[i] = 0;
#ifdef FEAT_MBYTE
    hash_init(&lp->sl_map_hash);
#endif


    for (p = map; *p != NUL; )
    {
#ifdef FEAT_MBYTE
	c = mb_cptr2char_adv(&p);
#else
	c = *p++;
#endif
	if (c == '/')
	    headc = 0;
	else
	{
	    if (headc == 0)
		 headc = c;

#ifdef FEAT_MBYTE


	    if (c >= 256)
	    {
		int	    cl = mb_char2len(c);
		int	    headcl = mb_char2len(headc);
		char_u	    *b;
		hash_T	    hash;
		hashitem_T  *hi;

		b = alloc((unsigned)(cl + headcl + 2));
		if (b == NULL)
		    return;
		mb_char2bytes(c, b);
		b[cl] = NUL;
		mb_char2bytes(headc, b + cl + 1);
		b[cl + 1 + headcl] = NUL;
		hash = hash_hash(b);
		hi = hash_lookup(&lp->sl_map_hash, b, hash);
		if (HASHITEM_EMPTY(hi))
		    hash_add_item(&lp->sl_map_hash, hi, b, hash);
		else
		{


		    EMSG(_("E783: duplicate char in MAP entry"));
		    vim_free(b);
		}
	    }
	    else
#endif
		lp->sl_map_array[c] = headc;
	}
    }
}
