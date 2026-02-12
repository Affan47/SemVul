cleanup_suggestions(
    garray_T	*gap,
    int		maxscore,
    int		keep)
{
    if (gap->ga_len > 0)
    {

	qsort(gap->ga_data, (size_t)gap->ga_len, sizeof(suggest_T),
								  sug_compare);


	if (gap->ga_len > keep)
	{
	    int		i;
	    suggest_T   *stp = &SUG(*gap, 0);

	    for (i = keep; i < gap->ga_len; ++i)
		vim_free(stp[i].st_word);
	    gap->ga_len = keep;
	    if (keep >= 1)
		return stp[keep - 1].st_score;
	}
    }
    return maxscore;
}
