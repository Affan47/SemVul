thesarurs_add_words_in_line(
	char_u	*fname,
	char_u	**buf_arg,
	int	dir,
	char_u	*skip_word)
{
    int		status = OK;
    char_u	*ptr;
    char_u	*wstart;


    ptr = *buf_arg;
    while (!got_int)
    {


	ptr = find_word_start(ptr);
	if (*ptr == NUL || *ptr == NL)
	    break;
	wstart = ptr;


	if (has_mbyte)


	    while (*ptr != NUL)
	    {
		int l = (*mb_ptr2len)(ptr);

		if (l < 2 && !vim_iswordc(*ptr))
		    break;
		ptr += l;
	    }
	else
	    ptr = find_word_end(ptr);


	if (wstart != skip_word)
	{
	    status = ins_compl_add_infercase(wstart, (int)(ptr - wstart), p_ic,
							fname, dir, FALSE);
	    if (status == FAIL)
		break;
	}
    }

    *buf_arg = ptr;
    return status;
}
