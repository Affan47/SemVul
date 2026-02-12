findtags_parse_line(
    findtags_state_T		*st,
    tagptrs_T			*tagpp,
    findtags_match_args_T	*margs,
    tagsearch_info_T		*sinfo_p)
{
    int		status;
    int		i;
    int		cmplen;
    int		tagcmp;


    if (st->orgpat->headlen
#ifdef FEAT_EMACS_TAGS
	    && !st->is_etag
#endif
       )
    {
	CLEAR_FIELD(*tagpp);
	tagpp->tagname = st->lbuf;
	tagpp->tagname_end = vim_strchr(st->lbuf, TAB);
	if (tagpp->tagname_end == NULL)

	    return TAG_MATCH_FAIL;


	cmplen = (int)(tagpp->tagname_end - tagpp->tagname);
	if (p_tl != 0 && cmplen > p_tl)
	    cmplen = p_tl;
	if ((st->flags & TAG_REGEXP) && st->orgpat->headlen < cmplen)
	    cmplen = st->orgpat->headlen;
	else if (st->state == TS_LINEAR && st->orgpat->headlen != cmplen)
	    return TAG_MATCH_NEXT;

	if (st->state == TS_BINARY)
	{

	    i = (int)tagpp->tagname[0];
	    if (margs->sortic)
		i = (int)TOUPPER_ASC(tagpp->tagname[0]);
	    if (i < sinfo_p->low_char || i > sinfo_p->high_char)
		margs->sort_error = TRUE;


	    if (margs->sortic)
		tagcmp = tag_strnicmp(tagpp->tagname, st->orgpat->head,
							(size_t)cmplen);
	    else
		tagcmp = STRNCMP(tagpp->tagname, st->orgpat->head, cmplen);


	    if (tagcmp == 0)
	    {
		if (cmplen < st->orgpat->headlen)
		    tagcmp = -1;
		else if (cmplen > st->orgpat->headlen)
		    tagcmp = 1;
	    }

	    if (tagcmp == 0)
	    {


		st->state = TS_SKIP_BACK;
		sinfo_p->match_offset = sinfo_p->curr_offset;
		return TAG_MATCH_NEXT;
	    }
	    if (tagcmp < 0)
	    {
		sinfo_p->curr_offset = vim_ftell(st->fp);
		if (sinfo_p->curr_offset < sinfo_p->high_offset)
		{
		    sinfo_p->low_offset = sinfo_p->curr_offset;
		    if (margs->sortic)
			sinfo_p->low_char = TOUPPER_ASC(tagpp->tagname[0]);
		    else
			sinfo_p->low_char = tagpp->tagname[0];
		    return TAG_MATCH_NEXT;
		}
	    }
	    if (tagcmp > 0 && sinfo_p->curr_offset != sinfo_p->high_offset)
	    {
		sinfo_p->high_offset = sinfo_p->curr_offset;
		if (margs->sortic)
		    sinfo_p->high_char = TOUPPER_ASC(tagpp->tagname[0]);
		else
		    sinfo_p->high_char = tagpp->tagname[0];
		return TAG_MATCH_NEXT;
	    }


	    return TAG_MATCH_STOP;
	}
	else if (st->state == TS_SKIP_BACK)
	{
	    if (MB_STRNICMP(tagpp->tagname, st->orgpat->head, cmplen) != 0)
		st->state = TS_STEP_FORWARD;
	    else


		sinfo_p->curr_offset = sinfo_p->curr_offset_used;
	    return TAG_MATCH_NEXT;
	}
	else if (st->state == TS_STEP_FORWARD)
	{
	    if (MB_STRNICMP(tagpp->tagname, st->orgpat->head, cmplen) != 0)
	    {
		if ((off_T)vim_ftell(st->fp) > sinfo_p->match_offset)
		    return TAG_MATCH_STOP;
		else
		    return TAG_MATCH_NEXT;
	    }
	}
	else

	    if (MB_STRNICMP(tagpp->tagname, st->orgpat->head, cmplen) != 0)
		return TAG_MATCH_NEXT;


	tagpp->fname = tagpp->tagname_end + 1;
	tagpp->fname_end = vim_strchr(tagpp->fname, TAB);
	if (tagpp->fname_end == NULL)
	    status = FAIL;
	else
	{
	    tagpp->command = tagpp->fname_end + 1;
	    status = OK;
	}
    }
    else
	status = parse_tag_line(st->lbuf,
#ifdef FEAT_EMACS_TAGS
		st->is_etag,
#endif
		tagpp);

    if (status == FAIL)
	return TAG_MATCH_FAIL;

#ifdef FEAT_EMACS_TAGS
    if (st->is_etag)
	tagpp->fname = st->ebuf;
#endif

    return TAG_MATCH_SUCCESS;
}
