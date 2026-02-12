findtags_in_file(findtags_state_T *st, char_u *buf_ffname)
{
    findtags_match_args_T margs;
#ifdef FEAT_CSCOPE
    int		use_cscope = (st->flags & TAG_CSCOPE);
#endif

    st->vimconv.vc_type = CONV_NONE;
    st->tag_file_sorted = NUL;
    st->fp = NULL;
    findtags_matchargs_init(&margs, st->flags);


#ifdef FEAT_CSCOPE
    if (use_cscope)
	st->fp = NULL;
    else
#endif
    {
#ifdef FEAT_MULTI_LANG
	if (curbuf->b_help)
	{
	    if (!findtags_in_help_init(st))
		return;
	}
#endif

	st->fp = mch_fopen((char *)st->tag_fname, "r");
	if (st->fp == NULL)
	    return;

	if (p_verbose >= 5)
	{
	    verbose_enter();
	    smsg(_("Searching tags file %s"), st->tag_fname);
	    verbose_leave();
	}
    }
    st->did_open = TRUE;

    st->state = TS_START;
#ifdef FEAT_EMACS_TAGS
    st->is_etag = FALSE;
#endif


    findtags_get_all_tags(st, &margs, buf_ffname);

    if (st->fp != NULL)
    {
	fclose(st->fp);
	st->fp = NULL;
    }
#ifdef FEAT_EMACS_TAGS
    emacs_tags_incstack_free();
#endif
    if (st->vimconv.vc_type != CONV_NONE)
	convert_setup(&st->vimconv, NULL, NULL);

    if (margs.sort_error)
	semsg(_(e_tags_file_not_sorted_str), st->tag_fname);


    if (st->match_count >= st->mincount)
	st->stop_searching = TRUE;
}
