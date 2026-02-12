add_sound_suggest(
    suginfo_T	*su,
    char_u	*goodword,
    int		score,
    langp_T	*lp)
{
    slang_T	*slang = lp->lp_slang;
    int		sfwordnr;
    char_u	*nrline;
    int		orgnr;
    char_u	theword[MAXWLEN];
    int		i;
    int		wlen;
    char_u	*byts;
    idx_T	*idxs;
    int		n;
    int		wordcount;
    int		wc;
    int		goodscore;
    hash_T	hash;
    hashitem_T  *hi;
    sftword_T	*sft;
    int		bc, gc;
    int		limit;


    hash = hash_hash(goodword);
    hi = hash_lookup(&slang->sl_sounddone, goodword, hash);
    if (HASHITEM_EMPTY(hi))
    {
	sft = alloc(sizeof(sftword_T) + STRLEN(goodword));
	if (sft != NULL)
	{
	    sft->sft_score = score;
	    STRCPY(sft->sft_word, goodword);
	    hash_add_item(&slang->sl_sounddone, hi, sft->sft_word, hash);
	}
    }
    else
    {
	sft = HI2SFT(hi);
	if (score >= sft->sft_score)
	    return;
	sft->sft_score = score;
    }


    sfwordnr = soundfold_find(slang, goodword);
    if (sfwordnr < 0)
    {
	internal_error("add_sound_suggest()");
	return;
    }


    nrline = ml_get_buf(slang->sl_sugbuf, (linenr_T)(sfwordnr + 1), FALSE);
    orgnr = 0;
    while (*nrline != NUL)
    {


	orgnr += bytes2offset(&nrline);

	byts = slang->sl_fbyts;
	idxs = slang->sl_fidxs;


	n = 0;
	wordcount = 0;
	for (wlen = 0; wlen < MAXWLEN - 3; ++wlen)
	{
	    i = 1;
	    if (wordcount == orgnr && byts[n + 1] == NUL)
		break;

	    if (byts[n + 1] == NUL)
		++wordcount;


	    for ( ; byts[n + i] == NUL; ++i)
		if (i > byts[n])
		{
		    STRCPY(theword + wlen, "BAD");
		    wlen += 3;
		    goto badword;
		}


	    for ( ; i < byts[n]; ++i)
	    {
		wc = idxs[idxs[n + i]];
		if (wordcount + wc > orgnr)
		    break;
		wordcount += wc;
	    }

	    theword[wlen] = byts[n + i];
	    n = idxs[n + i];
	}
badword:
	theword[wlen] = NUL;


	for (; i <= byts[n] && byts[n + i] == NUL; ++i)
	{
	    char_u	cword[MAXWLEN];
	    char_u	*p;
	    int		flags = (int)idxs[n + i];


	    if (flags & WF_NOSUGGEST)
		continue;

	    if (flags & WF_KEEPCAP)
	    {

		find_keepcap_word(slang, theword, cword);
		p = cword;
	    }
	    else
	    {
		flags |= su->su_badflags;
		if ((flags & WF_CAPMASK) != 0)
		{

		    make_case_word(theword, cword, flags);
		    p = cword;
		}
		else
		    p = theword;
	    }


	    if (sps_flags & SPS_DOUBLE)
	    {

		if (score <= su->su_maxscore)
		    add_suggestion(su, &su->su_sga, p, su->su_badlen,
					       score, 0, FALSE, slang, FALSE);
	    }
	    else
	    {

		if ((flags & WF_REGION)
			    && (((unsigned)flags >> 16) & lp->lp_region) == 0)
		    goodscore = SCORE_REGION;
		else
		    goodscore = 0;


		gc = PTR2CHAR(p);
		if (SPELL_ISUPPER(gc))
		{
		    bc = PTR2CHAR(su->su_badword);
		    if (!SPELL_ISUPPER(bc)
				      && SPELL_TOFOLD(bc) != SPELL_TOFOLD(gc))
			goodscore += SCORE_ICASE / 2;
		}


		limit = MAXSCORE(su->su_sfmaxscore - goodscore, score);
		if (limit > SCORE_LIMITMAX)
		    goodscore += spell_edit_score(slang, su->su_badword, p);
		else
		    goodscore += spell_edit_score_limit(slang, su->su_badword,
								    p, limit);


		if (goodscore < SCORE_MAXMAX)
		{

		    goodscore = score_wordcount_adj(slang, goodscore, p, FALSE);


		    goodscore = RESCORE(goodscore, score);
		    if (goodscore <= su->su_sfmaxscore)
			add_suggestion(su, &su->su_ga, p, su->su_badlen,
					 goodscore, score, TRUE, slang, TRUE);
		}
	    }
	}

    }
}
