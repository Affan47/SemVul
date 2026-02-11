ff_check_visited(visited_list, fname
#ifdef FEAT_PATH_EXTRA
	, wc_path
#endif
	)
    ff_visited_T	**visited_list;
    char_u		*fname;
#ifdef FEAT_PATH_EXTRA
    char_u		*wc_path;
#endif
{
    ff_visited_T	*vp;
#ifdef UNIX
    struct stat		st;
    int			url = FALSE;
#endif


    if (path_with_url(fname))
    {
	vim_strncpy(ff_expand_buffer, fname, MAXPATHL - 1);
#ifdef UNIX
	url = TRUE;
#endif
    }
    else
    {
	ff_expand_buffer[0] = NUL;
#ifdef UNIX
	if (mch_stat((char *)fname, &st) < 0)
#else
	if (vim_FullName(fname, ff_expand_buffer, MAXPATHL, TRUE) == FAIL)
#endif
	    return FAIL;
    }


    for (vp = *visited_list; vp != NULL; vp = vp->ffv_next)
    {
	if (
#ifdef UNIX
		!url
		    ? (vp->ffv_dev == st.st_dev
			&& vp->ffv_ino == st.st_ino)
		    :
#endif
		fnamecmp(vp->ffv_fname, ff_expand_buffer) == 0
	   )
	{
#ifdef FEAT_PATH_EXTRA

	    if (ff_wc_equal(vp->ffv_wc_path, wc_path) == TRUE)
#endif

		return FAIL;
	}
    }


    vp = (ff_visited_T *)alloc((unsigned)(sizeof(ff_visited_T)
						 + STRLEN(ff_expand_buffer)));

    if (vp != NULL)
    {
#ifdef UNIX
	if (!url)
	{
	    vp->ffv_ino = st.st_ino;
	    vp->ffv_dev = st.st_dev;
	    vp->ffv_fname[0] = NUL;
	}
	else
	{
	    vp->ffv_ino = 0;
	    vp->ffv_dev = -1;
#endif
	    STRCPY(vp->ffv_fname, ff_expand_buffer);
#ifdef UNIX
	}
#endif
#ifdef FEAT_PATH_EXTRA
	if (wc_path != NULL)
	    vp->ffv_wc_path = vim_strsave(wc_path);
	else
	    vp->ffv_wc_path = NULL;
#endif

	vp->ffv_next = *visited_list;
	*visited_list = vp;
    }

    return OK;
}
