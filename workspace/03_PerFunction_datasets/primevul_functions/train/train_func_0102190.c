count_syllables(slang_T *slang, char_u *word)
{
    int		cnt = 0;
    int		skip = FALSE;
    char_u	*p;
    int		len;
    int		i;
    syl_item_T	*syl;
    int		c;

    if (slang->sl_syllable == NULL)
	return 0;

    for (p = word; *p != NUL; p += len)
    {

	if (*p == ' ')
	{
	    len = 1;
	    cnt = 0;
	    continue;
	}


	len = 0;
	for (i = 0; i < slang->sl_syl_items.ga_len; ++i)
	{
	    syl = ((syl_item_T *)slang->sl_syl_items.ga_data) + i;
	    if (syl->sy_len > len
			       && STRNCMP(p, syl->sy_chars, syl->sy_len) == 0)
		len = syl->sy_len;
	}
	if (len != 0)
	{
	    ++cnt;
	    skip = FALSE;
	}
	else
	{

	    c = mb_ptr2char(p);
	    len = (*mb_ptr2len)(p);
	    if (vim_strchr(slang->sl_syllable, c) == NULL)
		skip = FALSE;
	    else if (!skip)
	    {
		++cnt;
		skip = TRUE;
	    }
	}
    }
    return cnt;
}
