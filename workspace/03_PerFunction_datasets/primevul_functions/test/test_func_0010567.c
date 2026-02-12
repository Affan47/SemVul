add_suggestion(
    suginfo_T	*su,
    garray_T	*gap,
    char_u	*goodword,
    int		badlenarg,
    int		score,
    int		altscore,
    int		had_bonus,
    slang_T	*slang,
    int		maxsf)

{
    int		goodlen;
    int		badlen;
    suggest_T   *stp;
    suggest_T   new_sug;
    int		i;
    char_u	*pgood, *pbad;


    pgood = goodword + STRLEN(goodword);
    pbad = su->su_badptr + badlenarg;
    for (;;)
    {
	goodlen = (int)(pgood - goodword);
	badlen = (int)(pbad - su->su_badptr);
	if (goodlen <= 0 || badlen <= 0)
	    break;
	MB_PTR_BACK(goodword, pgood);
	MB_PTR_BACK(su->su_badptr, pbad);
	if (has_mbyte)
	{
	    if (mb_ptr2char(pgood) != mb_ptr2char(pbad))
		break;
	}
	else if (*pgood != *pbad)
		break;
    }

    if (badlen == 0 && goodlen == 0)


	return;

    if (gap->ga_len == 0)
	i = -1;
    else
    {


	stp = &SUG(*gap, 0);
	for (i = gap->ga_len; --i >= 0; ++stp)
	    if (stp->st_wordlen == goodlen
		    && stp->st_orglen == badlen
		    && STRNCMP(stp->st_word, goodword, goodlen) == 0)
	    {

		if (stp->st_slang == NULL)
		    stp->st_slang = slang;

		new_sug.st_score = score;
		new_sug.st_altscore = altscore;
		new_sug.st_had_bonus = had_bonus;

		if (stp->st_had_bonus != had_bonus)
		{


		    if (had_bonus)
			rescore_one(su, stp);
		    else
		    {
			new_sug.st_word = stp->st_word;
			new_sug.st_wordlen = stp->st_wordlen;
			new_sug.st_slang = stp->st_slang;
			new_sug.st_orglen = badlen;
			rescore_one(su, &new_sug);
		    }
		}

		if (stp->st_score > new_sug.st_score)
		{
		    stp->st_score = new_sug.st_score;
		    stp->st_altscore = new_sug.st_altscore;
		    stp->st_had_bonus = new_sug.st_had_bonus;
		}
		break;
	    }
    }

    if (i < 0 && ga_grow(gap, 1) == OK)
    {

	stp = &SUG(*gap, gap->ga_len);
	stp->st_word = vim_strnsave(goodword, goodlen);
	if (stp->st_word != NULL)
	{
	    stp->st_wordlen = goodlen;
	    stp->st_score = score;
	    stp->st_altscore = altscore;
	    stp->st_had_bonus = had_bonus;
	    stp->st_orglen = badlen;
	    stp->st_slang = slang;
	    ++gap->ga_len;


	    if (gap->ga_len > SUG_MAX_COUNT(su))
	    {
		if (maxsf)
		    su->su_sfmaxscore = cleanup_suggestions(gap,
				      su->su_sfmaxscore, SUG_CLEAN_COUNT(su));
		else
		    su->su_maxscore = cleanup_suggestions(gap,
					su->su_maxscore, SUG_CLEAN_COUNT(su));
	    }
	}
    }
}
