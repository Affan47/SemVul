spell_edit_score_limit(
    slang_T	*slang,
    char_u	*badword,
    char_u	*goodword,
    int		limit)
{
    limitscore_T    stack[10];
    int		    stackidx;
    int		    bi, gi;
    int		    bi2, gi2;
    int		    bc, gc;
    int		    score;
    int		    score_off;
    int		    minscore;
    int		    round;


    if (has_mbyte)
	return spell_edit_score_limit_w(slang, badword, goodword, limit);


    stackidx = 0;
    bi = 0;
    gi = 0;
    score = 0;
    minscore = limit + 1;

    for (;;)
    {

	for (;;)
	{
	    bc = badword[bi];
	    gc = goodword[gi];
	    if (bc != gc)
		break;
	    if (bc == NUL)
	    {
		if (score < minscore)
		    minscore = score;
		goto pop;
	    }
	    ++bi;
	    ++gi;
	}

	if (gc == NUL)
	{
	    do
	    {
		if ((score += SCORE_DEL) >= minscore)
		    goto pop;
	    } while (badword[++bi] != NUL);
	    minscore = score;
	}
	else if (bc == NUL)
	{
	    do
	    {
		if ((score += SCORE_INS) >= minscore)
		    goto pop;
	    } while (goodword[++gi] != NUL);
	    minscore = score;
	}
	else
	{


	    for (round = 0; round <= 1; ++round)
	    {
		score_off = score + (round == 0 ? SCORE_DEL : SCORE_INS);
		if (score_off < minscore)
		{
		    if (score_off + SCORE_EDIT_MIN >= minscore)
		    {


			bi2 = bi + 1 - round;
			gi2 = gi + round;
			while (goodword[gi2] == badword[bi2])
			{
			    if (goodword[gi2] == NUL)
			    {
				minscore = score_off;
				break;
			    }
			    ++bi2;
			    ++gi2;
			}
		    }
		    else
		    {

			stack[stackidx].badi = bi + 1 - round;
			stack[stackidx].goodi = gi + round;
			stack[stackidx].score = score_off;
			++stackidx;
		    }
		}
	    }

	    if (score + SCORE_SWAP < minscore)
	    {


		if (gc == badword[bi + 1] && bc == goodword[gi + 1])
		{

		    gi += 2;
		    bi += 2;
		    score += SCORE_SWAP;
		    continue;
		}
	    }


	    if (SPELL_TOFOLD(bc) == SPELL_TOFOLD(gc))
		score += SCORE_ICASE;
	    else
	    {

		if (slang != NULL
			&& slang->sl_has_map
			&& similar_chars(slang, gc, bc))
		    score += SCORE_SIMILAR;
		else
		    score += SCORE_SUBST;
	    }

	    if (score < minscore)
	    {

		++gi;
		++bi;
		continue;
	    }
	}
pop:

	if (stackidx == 0)
	    break;


	--stackidx;
	gi = stack[stackidx].goodi;
	bi = stack[stackidx].badi;
	score = stack[stackidx].score;
    }


    if (minscore > limit)
	return SCORE_MAXMAX;
    return minscore;
}
