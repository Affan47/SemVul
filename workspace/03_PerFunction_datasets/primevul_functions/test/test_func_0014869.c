findtags_get_all_tags(
    findtags_state_T		*st,
    findtags_match_args_T	*margs,
    char_u			*buf_ffname)
{
    tagptrs_T		tagp;
    tagsearch_info_T	search_info;
    int			retval;
#ifdef FEAT_CSCOPE
    int			use_cscope = (st->flags & TAG_CSCOPE);
#endif
    hash_T		hash = 0;


    CLEAR_FIELD(search_info);


    for (;;)
    {

	if (st->state == TS_BINARY || st->state == TS_SKIP_BACK)
	    line_breakcheck();
	else
	    fast_breakcheck();
	if ((st->flags & TAG_INS_COMP))
	    ins_compl_check_keys(30, FALSE);
	if (got_int || ins_compl_interrupted())
	{
	    st->stop_searching = TRUE;
	    break;
	}


	if (st->mincount == TAG_MANY && st->match_count >= TAG_MANY)
	{
	    st->stop_searching = TRUE;
	    break;
	}
	if (st->get_searchpat)
	    goto line_read_in;

	retval = findtags_get_next_line(st, &search_info);
	if (retval == TAGS_READ_IGNORE)
	    continue;
	if (retval == TAGS_READ_EOF)
	    break;

line_read_in:

	if (st->vimconv.vc_type != CONV_NONE)
	    findtags_string_convert(st);

#ifdef FEAT_EMACS_TAGS


	if (*st->lbuf == Ctrl_L
# ifdef FEAT_CSCOPE
		&& !use_cscope
# endif
	   )
	{
	    st->is_etag = TRUE;
	    st->state = TS_LINEAR;
	    emacs_tags_new_filename(st);
	    continue;
	}
#endif


	if (st->state == TS_START)
	{
	    if (findtags_start_state_handler(st, &margs->sortic, &search_info) == FALSE)
		continue;
	}


	if (st->lbuf[st->lbuf_size - 2] != NUL
#ifdef FEAT_CSCOPE
		&& !use_cscope
#endif
	   )
	{
	    st->lbuf_size *= 2;
	    vim_free(st->lbuf);
	    st->lbuf = alloc(st->lbuf_size);
	    if (st->lbuf == NULL)
	    {
		if (st->fp != NULL)
		    fclose(st->fp);
		st->fp = NULL;
		st->stop_searching = TRUE;
		return;
	    }

	    if (st->state == TS_STEP_FORWARD || st->state == TS_LINEAR)

		vim_ignored = vim_fseek(st->fp, search_info.curr_offset,
								     SEEK_SET);


	    search_info.curr_offset = 0;
	    continue;
	}

	retval = findtags_parse_line(st, &tagp, margs, &search_info);
	if (retval == TAG_MATCH_NEXT)
	    continue;
	if (retval == TAG_MATCH_STOP)
	    break;
	if (retval == TAG_MATCH_FAIL)
	{
	    semsg(_(e_format_error_in_tags_file_str), st->tag_fname);
#ifdef FEAT_CSCOPE
	    if (!use_cscope)
#endif
		semsg(_("Before byte %ld"), (long)vim_ftell(st->fp));
	    st->stop_searching = TRUE;
	    return;
	}

	retval = findtags_match_tag(st, &tagp, margs);
	if (retval == TAG_MATCH_NEXT)
	    continue;
	if (retval == TAG_MATCH_STOP)
	    break;


	if (retval == TAG_MATCH_SUCCESS)
	{
	    if (findtags_add_match(st, &tagp, margs, buf_ffname, &hash)
								== FAIL)
		break;
	}
    }
}
