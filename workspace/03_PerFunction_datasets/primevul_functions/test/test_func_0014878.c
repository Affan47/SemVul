findtags_add_match(
    findtags_state_T	*st,
    tagptrs_T		*tagpp,
    findtags_match_args_T   *margs,
    char_u		*buf_ffname,
    hash_T		*hash)
{
#ifdef FEAT_CSCOPE
    int		use_cscope = (st->flags & TAG_CSCOPE);
#endif
    int		name_only = (st->flags & TAG_NAMES);
    int		mtt;
    int		len = 0;
    int		is_current;
    int		is_static;
    char_u	*mfp;
    char_u	*p;
    char_u	*s;

#ifdef FEAT_CSCOPE
    if (use_cscope)
    {

	mtt = MT_GL_OTH;
    }
    else
#endif
    {

	is_current = test_for_current(
#ifdef FEAT_EMACS_TAGS
		st->is_etag,
#endif
		tagpp->fname, tagpp->fname_end, st->tag_fname, buf_ffname);
#ifdef FEAT_EMACS_TAGS
	is_static = FALSE;
	if (!st->is_etag)
#endif
	    is_static = test_for_static(tagpp);


	if (is_static)
	{
	    if (is_current)
		mtt = MT_ST_CUR;
	    else
		mtt = MT_ST_OTH;
	}
	else
	{
	    if (is_current)
		mtt = MT_GL_CUR;
	    else
		mtt = MT_GL_OTH;
	}
	if (st->orgpat->regmatch.rm_ic && !margs->match_no_ic)
	    mtt += MT_IC_OFF;
	if (margs->match_re)
	    mtt += MT_RE_OFF;
    }


    if (st->help_only)
    {
#ifdef FEAT_MULTI_LANG
# define ML_EXTRA 3
#else
# define ML_EXTRA 0
#endif


	*tagpp->tagname_end = NUL;
	len = (int)(tagpp->tagname_end - tagpp->tagname);
	mfp = alloc(sizeof(char_u) + len + 10 + ML_EXTRA + 1);
	if (mfp != NULL)
	{
	    int heuristic;

	    p = mfp;
	    STRCPY(p, tagpp->tagname);
#ifdef FEAT_MULTI_LANG
	    p[len] = '@';
	    STRCPY(p + len + 1, st->help_lang);
#endif

	    heuristic = help_heuristic(tagpp->tagname,
				margs->match_re ? margs->matchoff : 0,
				!margs->match_no_ic);
#ifdef FEAT_MULTI_LANG
	    heuristic += st->help_pri;
#endif
	    sprintf((char *)p + len + 1 + ML_EXTRA, "%06d",
		    heuristic);
	}
	*tagpp->tagname_end = TAB;
    }
    else if (name_only)
    {
	if (st->get_searchpat)
	{
	    char_u *temp_end = tagpp->command;

	    if (*temp_end == '/')
		while (*temp_end && *temp_end != '\r'
			&& *temp_end != '\n'
			&& *temp_end != '$')
		    temp_end++;

	    if (tagpp->command + 2 < temp_end)
	    {
		len = (int)(temp_end - tagpp->command - 2);
		mfp = alloc(len + 2);
		if (mfp != NULL)
		    vim_strncpy(mfp, tagpp->command + 2, len);
	    }
	    else
		mfp = NULL;
	    st->get_searchpat = FALSE;
	}
	else
	{
	    len = (int)(tagpp->tagname_end - tagpp->tagname);
	    mfp = alloc(sizeof(char_u) + len + 1);
	    if (mfp != NULL)
		vim_strncpy(mfp, tagpp->tagname, len);


	    if (State & MODE_INSERT)
		st->get_searchpat = p_sft;
	}
    }
    else
    {
	size_t tag_fname_len = STRLEN(st->tag_fname);
#ifdef FEAT_EMACS_TAGS
	size_t ebuf_len = 0;
#endif


	len = (int)tag_fname_len + (int)STRLEN(st->lbuf) + 3;
#ifdef FEAT_EMACS_TAGS
	if (st->is_etag)
	{
	    ebuf_len = STRLEN(st->ebuf);
	    len += (int)ebuf_len + 1;
	}
	else
	    ++len;
#endif
	mfp = alloc(sizeof(char_u) + len + 1);
	if (mfp != NULL)
	{
	    p = mfp;
	    p[0] = mtt + 1;
	    STRCPY(p + 1, st->tag_fname);
#ifdef BACKSLASH_IN_FILENAME


	    slash_adjust(p + 1);
#endif
	    p[tag_fname_len + 1] = TAG_SEP;
	    s = p + 1 + tag_fname_len + 1;
#ifdef FEAT_EMACS_TAGS
	    if (st->is_etag)
	    {
		STRCPY(s, st->ebuf);
		s[ebuf_len] = TAG_SEP;
		s += ebuf_len + 1;
	    }
	    else
		*s++ = TAG_SEP;
#endif
	    STRCPY(s, st->lbuf);
	}
    }

    if (mfp != NULL)
    {
	hashitem_T	*hi;


#ifdef FEAT_CSCOPE
	if (use_cscope)
	    ++*hash;
	else
#endif
	    *hash = hash_hash(mfp);
	hi = hash_lookup(&st->ht_match[mtt], mfp, *hash);
	if (HASHITEM_EMPTY(hi))
	{
	    if (hash_add_item(&st->ht_match[mtt], hi, mfp, *hash) == FAIL
		    || ga_grow(&st->ga_match[mtt], 1) != OK)
	    {

		st->stop_searching = TRUE;
		return FAIL;
	    }

	    ((char_u **)(st->ga_match[mtt].ga_data))
		[st->ga_match[mtt].ga_len++] = mfp;
	    st->match_count++;
	}
	else

	    vim_free(mfp);
    }

    return OK;
}
