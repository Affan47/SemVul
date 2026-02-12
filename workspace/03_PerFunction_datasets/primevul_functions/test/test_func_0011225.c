load_dummy_buffer(
    char_u	*fname,
    char_u	*dirname_start,
    char_u	*resulting_dir)
{
    buf_T	*newbuf;
    bufref_T	newbufref;
    bufref_T	newbuf_to_wipe;
    int		failed = TRUE;
    aco_save_T	aco;
    int		readfile_result;


    newbuf = buflist_new(NULL, NULL, (linenr_T)1, BLN_DUMMY);
    if (newbuf == NULL)
	return NULL;
    set_bufref(&newbufref, newbuf);


    buf_copy_options(newbuf, BCO_ENTER | BCO_NOHELP);


    if (ml_open(newbuf) == OK)
    {

	++newbuf->b_locked;


	aucmd_prepbuf(&aco, newbuf);


	(void)setfname(curbuf, fname, NULL, FALSE);


	check_need_swap(TRUE);


	curbuf->b_flags &= ~BF_DUMMY;

	newbuf_to_wipe.br_buf = NULL;
	readfile_result = readfile(fname, NULL,
		    (linenr_T)0, (linenr_T)0, (linenr_T)MAXLNUM,
		    NULL, READ_NEW | READ_DUMMY);
	--newbuf->b_locked;
	if (readfile_result == OK
		&& !got_int
		&& !(curbuf->b_flags & BF_NEW))
	{
	    failed = FALSE;
	    if (curbuf != newbuf)
	    {


		set_bufref(&newbuf_to_wipe, newbuf);
		newbuf = curbuf;
	    }
	}


	aucmd_restbuf(&aco);
	if (newbuf_to_wipe.br_buf != NULL && bufref_valid(&newbuf_to_wipe))
	    wipe_buffer(newbuf_to_wipe.br_buf, FALSE);


	newbuf->b_flags |= BF_DUMMY;
    }


    mch_dirname(resulting_dir, MAXPATHL);
    restore_start_dir(dirname_start);

    if (!bufref_valid(&newbufref))
	return NULL;
    if (failed)
    {
	wipe_dummy_buffer(newbuf, dirname_start);
	return NULL;
    }
    return newbuf;
}
