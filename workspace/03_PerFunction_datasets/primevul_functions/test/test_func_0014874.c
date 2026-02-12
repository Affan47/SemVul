findtags_start_state_handler(
    findtags_state_T	*st,
    int			*sortic,
    tagsearch_info_T	*sinfo_p)
{
#ifdef FEAT_CSCOPE
    int		use_cscope = (st->flags & TAG_CSCOPE);
#endif
    int		noic = (st->flags & TAG_NOIC);
    off_T	filesize;


    if (STRNCMP(st->lbuf, "!_TAG_", 6) <= 0
	    || (st->lbuf[0] == '!' && ASCII_ISLOWER(st->lbuf[1])))
	return findtags_hdr_parse(st);


# ifdef FEAT_CSCOPE
    if (st->linear || use_cscope)
# else
    if (st->linear)
# endif
	st->state = TS_LINEAR;
    else if (st->tag_file_sorted == NUL)
	st->state = TS_BINARY;
    else if (st->tag_file_sorted == '1')
	st->state = TS_BINARY;
    else if (st->tag_file_sorted == '2')
    {
	st->state = TS_BINARY;
	*sortic = TRUE;
	st->orgpat->regmatch.rm_ic = (p_ic || !noic);
    }
    else
	st->state = TS_LINEAR;

    if (st->state == TS_BINARY && st->orgpat->regmatch.rm_ic && !*sortic)
    {


	st->linear = TRUE;
	st->state = TS_LINEAR;
    }


    if (st->state == TS_BINARY)
    {
	if (vim_fseek(st->fp, 0L, SEEK_END) != 0)

	    st->state = TS_LINEAR;
	else
	{


	    filesize = vim_ftell(st->fp);
	    vim_ignored = vim_fseek(st->fp, 0L, SEEK_SET);


	    sinfo_p->low_offset = 0;
	    sinfo_p->low_char = 0;
	    sinfo_p->high_offset = filesize;
	    sinfo_p->curr_offset = 0;
	    sinfo_p->high_char = 0xff;
	}
	return FALSE;
    }

    return TRUE;
}
