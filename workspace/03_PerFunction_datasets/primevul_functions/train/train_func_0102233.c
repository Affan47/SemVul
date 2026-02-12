dump_prefixes(
    slang_T	*slang,
    char_u	*word,
    char_u	*pat,
    int		*dir,
    int		dumpflags,
    int		flags,
    linenr_T	startlnum)
{
    idx_T	arridx[MAXWLEN];
    int		curi[MAXWLEN];
    char_u	prefix[MAXWLEN];
    char_u	word_up[MAXWLEN];
    int		has_word_up = FALSE;
    int		c;
    char_u	*byts;
    idx_T	*idxs;
    linenr_T	lnum = startlnum;
    int		depth;
    int		n;
    int		len;
    int		i;


    c = PTR2CHAR(word);
    if (SPELL_TOUPPER(c) != c)
    {
	onecap_copy(word, word_up, TRUE);
	has_word_up = TRUE;
    }

    byts = slang->sl_pbyts;
    idxs = slang->sl_pidxs;
    if (byts != NULL)
    {


	depth = 0;
	arridx[0] = 0;
	curi[0] = 1;
	while (depth >= 0 && !got_int)
	{
	    n = arridx[depth];
	    len = byts[n];
	    if (curi[depth] > len)
	    {

		--depth;
		line_breakcheck();
	    }
	    else
	    {

		n += curi[depth];
		++curi[depth];
		c = byts[n];
		if (c == 0)
		{

		    for (i = 1; i < len; ++i)
			if (byts[n + i] != 0)
			    break;
		    curi[depth] += i - 1;

		    c = valid_word_prefix(i, n, flags, word, slang, FALSE);
		    if (c != 0)
		    {
			vim_strncpy(prefix + depth, word, MAXWLEN - depth - 1);
			dump_word(slang, prefix, pat, dir, dumpflags,
				(c & WF_RAREPFX) ? (flags | WF_RARE)
							       : flags, lnum);
			if (lnum != 0)
			    ++lnum;
		    }


		    if (has_word_up)
		    {
			c = valid_word_prefix(i, n, flags, word_up, slang,
									TRUE);
			if (c != 0)
			{
			    vim_strncpy(prefix + depth, word_up,
							 MAXWLEN - depth - 1);
			    dump_word(slang, prefix, pat, dir, dumpflags,
				    (c & WF_RAREPFX) ? (flags | WF_RARE)
							       : flags, lnum);
			    if (lnum != 0)
				++lnum;
			}
		    }
		}
		else
		{

		    prefix[depth++] = c;
		    arridx[depth] = idxs[n];
		    curi[depth] = 1;
		}
	    }
	}
    }

    return lnum;
}
