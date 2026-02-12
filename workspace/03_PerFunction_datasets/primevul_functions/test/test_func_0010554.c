soundalike_score(
    char_u	*goodstart,
    char_u	*badstart)
{
    char_u	*goodsound = goodstart;
    char_u	*badsound = badstart;
    int		goodlen;
    int		badlen;
    int		n;
    char_u	*pl, *ps;
    char_u	*pl2, *ps2;
    int		score = 0;


    if ((*badsound == '*' || *goodsound == '*') && *badsound != *goodsound)
    {
	if ((badsound[0] == NUL && goodsound[1] == NUL)
	    || (goodsound[0] == NUL && badsound[1] == NUL))

	    return SCORE_DEL;
	if (badsound[0] == NUL || goodsound[0] == NUL)

	    return SCORE_MAXMAX;

	if (badsound[1] == goodsound[1]
		|| (badsound[1] != NUL
		    && goodsound[1] != NUL
		    && badsound[2] == goodsound[2]))
	{

	}
	else
	{
	    score = 2 * SCORE_DEL / 3;
	    if (*badsound == '*')
		++badsound;
	    else
		++goodsound;
	}
    }

    goodlen = (int)STRLEN(goodsound);
    badlen = (int)STRLEN(badsound);


    n = goodlen - badlen;
    if (n < -2 || n > 2)
	return SCORE_MAXMAX;

    if (n > 0)
    {
	pl = goodsound;
	ps = badsound;
    }
    else
    {
	pl = badsound;
	ps = goodsound;
    }


    while (*pl == *ps && *pl != NUL)
    {
	++pl;
	++ps;
    }

    switch (n)
    {
	case -2:
	case 2:

	    ++pl;
	    while (*pl == *ps)
	    {
		++pl;
		++ps;
	    }

	    if (STRCMP(pl + 1, ps) == 0)
		return score + SCORE_DEL * 2;


	    break;

	case -1:
	case 1:


	    pl2 = pl + 1;
	    ps2 = ps;
	    while (*pl2 == *ps2)
	    {
		if (*pl2 == NUL)
		    return score + SCORE_DEL;
		++pl2;
		++ps2;
	    }


	    if (pl2[0] == ps2[1] && pl2[1] == ps2[0]
					     && STRCMP(pl2 + 2, ps2 + 2) == 0)
		return score + SCORE_DEL + SCORE_SWAP;


	    if (STRCMP(pl2 + 1, ps2 + 1) == 0)
		return score + SCORE_DEL + SCORE_SUBST;


	    if (pl[0] == ps[1] && pl[1] == ps[0])
	    {
		pl2 = pl + 2;
		ps2 = ps + 2;
		while (*pl2 == *ps2)
		{
		    ++pl2;
		    ++ps2;
		}

		if (STRCMP(pl2 + 1, ps2) == 0)
		    return score + SCORE_SWAP + SCORE_DEL;
	    }


	    pl2 = pl + 1;
	    ps2 = ps + 1;
	    while (*pl2 == *ps2)
	    {
		++pl2;
		++ps2;
	    }

	    if (STRCMP(pl2 + 1, ps2) == 0)
		return score + SCORE_SUBST + SCORE_DEL;


	    break;

	case 0:


	    if (*pl == NUL)
		return score;


	    if (pl[0] == ps[1] && pl[1] == ps[0])
	    {
		pl2 = pl + 2;
		ps2 = ps + 2;
		while (*pl2 == *ps2)
		{
		    if (*pl2 == NUL)
			return score + SCORE_SWAP;
		    ++pl2;
		    ++ps2;
		}

		if (pl2[0] == ps2[1] && pl2[1] == ps2[0]
					     && STRCMP(pl2 + 2, ps2 + 2) == 0)
		    return score + SCORE_SWAP + SCORE_SWAP;


		if (STRCMP(pl2 + 1, ps2 + 1) == 0)
		    return score + SCORE_SWAP + SCORE_SUBST;
	    }


	    pl2 = pl + 1;
	    ps2 = ps + 1;
	    while (*pl2 == *ps2)
	    {
		if (*pl2 == NUL)
		    return score + SCORE_SUBST;
		++pl2;
		++ps2;
	    }


	    if (pl2[0] == ps2[1] && pl2[1] == ps2[0]
					     && STRCMP(pl2 + 2, ps2 + 2) == 0)
		return score + SCORE_SUBST + SCORE_SWAP;


	    if (STRCMP(pl2 + 1, ps2 + 1) == 0)
		return score + SCORE_SUBST + SCORE_SUBST;


	    pl2 = pl;
	    ps2 = ps + 1;
	    while (*pl2 == *ps2)
	    {
		++pl2;
		++ps2;
	    }
	    if (STRCMP(pl2 + 1, ps2) == 0)
		return score + SCORE_INS + SCORE_DEL;


	    pl2 = pl + 1;
	    ps2 = ps;
	    while (*pl2 == *ps2)
	    {
		++pl2;
		++ps2;
	    }
	    if (STRCMP(pl2, ps2 + 1) == 0)
		return score + SCORE_INS + SCORE_DEL;


	    break;
    }

    return SCORE_MAXMAX;
}
