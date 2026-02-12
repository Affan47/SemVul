find_tags(
    char_u	*pat,
    int		*num_matches,
    char_u	***matchesp,
    int		flags,
    int		mincount,

    char_u	*buf_ffname)
{
    findtags_state_T	st;
    tagname_T	tn;
    int		first_file;
    int		retval = FAIL;
    int		round;

    int		save_emsg_off;

    int		help_save;
#ifdef FEAT_MULTI_LANG
    int		i;
    char_u	*saved_pat = NULL;
#endif

    int		findall = (mincount == MAXCOL || mincount == TAG_MANY);

    int		has_re = (flags & TAG_REGEXP);
    int		noic = (flags & TAG_NOIC);
#ifdef FEAT_CSCOPE
    int		use_cscope = (flags & TAG_CSCOPE);
#endif
    int		verbose = (flags & TAG_VERBOSE);
    int		save_p_ic = p_ic;


    switch (curbuf->b_tc_flags ? curbuf->b_tc_flags : tc_flags)
    {
	case TC_FOLLOWIC:		 break;
	case TC_IGNORE:    p_ic = TRUE;  break;
	case TC_MATCH:     p_ic = FALSE; break;
	case TC_FOLLOWSCS: p_ic = ignorecase(pat); break;
	case TC_SMART:     p_ic = ignorecase_opt(pat, TRUE, TRUE); break;
    }

    help_save = curbuf->b_help;

    if (findtags_state_init(&st, pat, flags, mincount) == FAIL)
	goto findtag_end;

#ifdef FEAT_CSCOPE
    STRCPY(st.tag_fname, "from cscope");
#endif


    if (st.help_only)
	curbuf->b_help = TRUE;
#ifdef FEAT_CSCOPE
    else if (use_cscope)
    {

	st.help_only = FALSE;
	curbuf->b_help = FALSE;
    }
#endif

#ifdef FEAT_MULTI_LANG
    if (curbuf->b_help)
    {


	if (st.orgpat->len > 3 && pat[st.orgpat->len - 3] == '@'
				&& ASCII_ISALPHA(pat[st.orgpat->len - 2])
				&& ASCII_ISALPHA(pat[st.orgpat->len - 1]))
	{
	    saved_pat = vim_strnsave(pat, st.orgpat->len - 3);
	    if (saved_pat != NULL)
	    {
		st.help_lang_find = &pat[st.orgpat->len - 2];
		st.orgpat->pat = saved_pat;
		st.orgpat->len -= 3;
	    }
	}
    }
#endif
    if (p_tl != 0 && st.orgpat->len > p_tl)
	st.orgpat->len = p_tl;

    save_emsg_off = emsg_off;
    emsg_off = TRUE;
    prepare_pats(st.orgpat, has_re);
    emsg_off = save_emsg_off;
    if (has_re && st.orgpat->regmatch.regprog == NULL)
	goto findtag_end;

#ifdef FEAT_EVAL
    retval = findtags_apply_tfu(&st, pat, buf_ffname);
    if (retval != NOTDONE)
	goto findtag_end;


    retval = FAIL;
#endif

#ifdef FEAT_MULTI_LANG

    if ((flags & TAG_KEEP_LANG)
	    && st.help_lang_find == NULL
	    && curbuf->b_fname != NULL
	    && (i = (int)STRLEN(curbuf->b_fname)) > 4
	    && STRICMP(curbuf->b_fname + i - 4, ".txt") == 0)
	st.is_txt = TRUE;
#endif


    st.orgpat->regmatch.rm_ic = ((p_ic || !noic)
			&& (findall || st.orgpat->headlen == 0 || !p_tbs));
    for (round = 1; round <= 2; ++round)
    {
	st.linear = (st.orgpat->headlen == 0 || !p_tbs || round == 2);


      for (first_file = TRUE;
#ifdef FEAT_CSCOPE
	    use_cscope ||
#endif
		get_tagfname(&tn, first_file, st.tag_fname) == OK;
							   first_file = FALSE)
      {
	  findtags_in_file(&st, buf_ffname);
	  if (st.stop_searching
#ifdef FEAT_CSCOPE
		  || use_cscope
#endif
	     )
	  {
	      retval = OK;
	      break;
	  }
      }

#ifdef FEAT_CSCOPE
	if (!use_cscope)
#endif
	    tagname_free(&tn);


	if (st.stop_searching || st.linear || (!p_ic && noic) ||
						st.orgpat->regmatch.rm_ic)
	    break;
# ifdef FEAT_CSCOPE
	if (use_cscope)
	    break;
# endif


	st.orgpat->regmatch.rm_ic = TRUE;
    }

    if (!st.stop_searching)
    {
	if (!st.did_open && verbose)
	    emsg(_(e_no_tags_file));
	retval = OK;
    }

findtag_end:
    findtags_state_free(&st);


    if (retval == FAIL)
	st.match_count = 0;

    *num_matches = findtags_copy_matches(&st, matchesp);

    curbuf->b_help = help_save;
#ifdef FEAT_MULTI_LANG
    vim_free(saved_pat);
#endif

    p_ic = save_p_ic;

    return retval;
}
