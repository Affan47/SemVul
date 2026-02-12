buf_reload(buf_T *buf, int orig_mode)
{
    exarg_T	ea;
    pos_T	old_cursor;
    linenr_T	old_topline;
    int		old_ro = buf->b_p_ro;
    buf_T	*savebuf;
    bufref_T	bufref;
    int		saved = OK;
    aco_save_T	aco;
    int		flags = READ_NEW;


    aucmd_prepbuf(&aco, buf);


    if (prep_exarg(&ea, buf) == OK)
    {
	old_cursor = curwin->w_cursor;
	old_topline = curwin->w_topline;

	if (p_ur < 0 || curbuf->b_ml.ml_line_count <= p_ur)
	{


	    u_sync(FALSE);
	    saved = u_savecommon(0, curbuf->b_ml.ml_line_count + 1, 0, TRUE);
	    flags |= READ_KEEP_UNDO;
	}


	if (BUFEMPTY() || saved == FAIL)
	    savebuf = NULL;
	else
	{

	    savebuf = buflist_new(NULL, NULL, (linenr_T)1, BLN_DUMMY);
	    set_bufref(&bufref, savebuf);
	    if (savebuf != NULL && buf == curbuf)
	    {

		curbuf = savebuf;
		curwin->w_buffer = savebuf;
		saved = ml_open(curbuf);
		curbuf = buf;
		curwin->w_buffer = buf;
	    }
	    if (savebuf == NULL || saved == FAIL || buf != curbuf
				      || move_lines(buf, savebuf) == FAIL)
	    {
		EMSG2(_("E462: Could not prepare for reloading \"%s\""),
							    buf->b_fname);
		saved = FAIL;
	    }
	}

	if (saved == OK)
	{
	    curbuf->b_flags |= BF_CHECK_RO;
#ifdef FEAT_AUTOCMD
	    keep_filetype = TRUE;
#endif
	    if (readfile(buf->b_ffname, buf->b_fname, (linenr_T)0,
			(linenr_T)0,
			(linenr_T)MAXLNUM, &ea, flags) != OK)
	    {
#if defined(FEAT_AUTOCMD) && defined(FEAT_EVAL)
		if (!aborting())
#endif
		    EMSG2(_("E321: Could not reload \"%s\""), buf->b_fname);
		if (savebuf != NULL && bufref_valid(&bufref) && buf == curbuf)
		{


		    while (!BUFEMPTY())
			if (ml_delete(buf->b_ml.ml_line_count, FALSE) == FAIL)
			    break;
		    (void)move_lines(savebuf, buf);
		}
	    }
	    else if (buf == curbuf)
	    {

		unchanged(buf, TRUE);
		if ((flags & READ_KEEP_UNDO) == 0)
		{
		    u_blockfree(buf);
		    u_clearall(buf);
		}
		else
		{

		    u_unchanged(curbuf);
		}
	    }
	}
	vim_free(ea.cmd);

	if (savebuf != NULL && bufref_valid(&bufref))
	    wipe_buffer(savebuf, FALSE);

#ifdef FEAT_DIFF

	diff_invalidate(curbuf);
#endif


	if (old_topline > curbuf->b_ml.ml_line_count)
	    curwin->w_topline = curbuf->b_ml.ml_line_count;
	else
	    curwin->w_topline = old_topline;
	curwin->w_cursor = old_cursor;
	check_cursor();
	update_topline();
#ifdef FEAT_AUTOCMD
	keep_filetype = FALSE;
#endif
#ifdef FEAT_FOLDING
	{
	    win_T	*wp;
	    tabpage_T	*tp;


	    FOR_ALL_TAB_WINDOWS(tp, wp)
		if (wp->w_buffer == curwin->w_buffer
			&& !foldmethodIsManual(wp))
		    foldUpdateAll(wp);
	}
#endif


	if (orig_mode == curbuf->b_orig_mode)
	    curbuf->b_p_ro |= old_ro;


	do_modelines(0);
    }


    aucmd_restbuf(&aco);

}
