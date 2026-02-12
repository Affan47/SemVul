emacs_tags_new_filename(findtags_state_T *st)
{
    char_u	*p;
    char_u	*fullpath_ebuf;

    if (vim_fgets(st->ebuf, LSIZE, st->fp))
	return;

    for (p = st->ebuf; *p && *p != ','; p++)
	;
    *p = NUL;


    if (STRNCMP(p + 1, "include", 7) != 0 || incstack_idx >= INCSTACK_SIZE)
	return;


    incstack[incstack_idx].etag_fname = vim_strsave(st->tag_fname);
    if (incstack[incstack_idx].etag_fname == NULL)
	return;

    incstack[incstack_idx].fp = st->fp;
    st->fp = NULL;


    fullpath_ebuf = expand_tag_fname(st->ebuf, st->tag_fname, FALSE);
    if (fullpath_ebuf != NULL)
    {
	st->fp = mch_fopen((char *)fullpath_ebuf, "r");
	if (st->fp != NULL)
	{
	    if (STRLEN(fullpath_ebuf) > LSIZE)
		semsg(_(e_tag_file_path_truncated_for_str), st->ebuf);
	    vim_strncpy(st->tag_fname, fullpath_ebuf, MAXPATHL);
	    ++incstack_idx;
	    st->is_etag = FALSE;
	}
	vim_free(fullpath_ebuf);
    }
    if (st->fp == NULL)
    {


	st->fp = incstack[incstack_idx].fp;
	vim_free(incstack[incstack_idx].etag_fname);
    }
}
