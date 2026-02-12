u_undoredo(int undo)
{
    char_u	**newarray = NULL;
    linenr_T	oldsize;
    linenr_T	newsize;
    linenr_T	top, bot;
    linenr_T	lnum;
    linenr_T	newlnum = MAXLNUM;
    long	i;
    u_entry_T	*uep, *nuep;
    u_entry_T	*newlist = NULL;
    int		old_flags;
    int		new_flags;
    pos_T	namedm[NMARKS];
    visualinfo_T visualinfo;
    int		empty_buffer;
    u_header_T	*curhead = curbuf->b_u_curhead;

#ifdef FEAT_AUTOCMD


    block_autocmds();
#endif

#ifdef U_DEBUG
    u_check(FALSE);
#endif
    old_flags = curhead->uh_flags;
    new_flags = (curbuf->b_changed ? UH_CHANGED : 0) +
	       ((curbuf->b_ml.ml_flags & ML_EMPTY) ? UH_EMPTYBUF : 0);
    setpcmark();


    mch_memmove(namedm, curbuf->b_namedm, sizeof(pos_T) * NMARKS);
    visualinfo = curbuf->b_visual;
    curbuf->b_op_start.lnum = curbuf->b_ml.ml_line_count;
    curbuf->b_op_start.col = 0;
    curbuf->b_op_end.lnum = 0;
    curbuf->b_op_end.col = 0;

    for (uep = curhead->uh_entry; uep != NULL; uep = nuep)
    {
	top = uep->ue_top;
	bot = uep->ue_bot;
	if (bot == 0)
	    bot = curbuf->b_ml.ml_line_count + 1;
	if (top > curbuf->b_ml.ml_line_count || top >= bot
				      || bot > curbuf->b_ml.ml_line_count + 1)
	{
#ifdef FEAT_AUTOCMD
	    unblock_autocmds();
#endif
	    IEMSG(_("E438: u_undo: line numbers wrong"));
	    changed();
	    return;
	}

	oldsize = bot - top - 1;
	newsize = uep->ue_size;

	if (top < newlnum)
	{


	    lnum = curhead->uh_cursor.lnum;
	    if (lnum >= top && lnum <= top + newsize + 1)
	    {
		curwin->w_cursor = curhead->uh_cursor;
		newlnum = curwin->w_cursor.lnum - 1;
	    }
	    else
	    {


		for (i = 0; i < newsize && i < oldsize; ++i)
		    if (STRCMP(uep->ue_array[i], ml_get(top + 1 + i)) != 0)
			break;
		if (i == newsize && newlnum == MAXLNUM && uep->ue_next == NULL)
		{
		    newlnum = top;
		    curwin->w_cursor.lnum = newlnum + 1;
		}
		else if (i < newsize)
		{
		    newlnum = top + i;
		    curwin->w_cursor.lnum = newlnum + 1;
		}
	    }
	}

	empty_buffer = FALSE;


	if (oldsize > 0)
	{
	    if ((newarray = (char_u **)U_ALLOC_LINE(
					 sizeof(char_u *) * oldsize)) == NULL)
	    {
		do_outofmem_msg((long_u)(sizeof(char_u *) * oldsize));


		while (uep != NULL)
		{
		    nuep = uep->ue_next;
		    u_freeentry(uep, uep->ue_size);
		    uep = nuep;
		}
		break;
	    }

	    for (lnum = bot - 1, i = oldsize; --i >= 0; --lnum)
	    {

		if ((newarray[i] = u_save_line(lnum)) == NULL)
		    do_outofmem_msg((long_u)0);


		if (curbuf->b_ml.ml_line_count == 1)
		    empty_buffer = TRUE;
		ml_delete(lnum, FALSE);
	    }
	}
	else
	    newarray = NULL;


	if (newsize)
	{
	    for (lnum = top, i = 0; i < newsize; ++i, ++lnum)
	    {


		if (empty_buffer && lnum == 0)
		    ml_replace((linenr_T)1, uep->ue_array[i], TRUE);
		else
		    ml_append(lnum, uep->ue_array[i], (colnr_T)0, FALSE);
		vim_free(uep->ue_array[i]);
	    }
	    vim_free((char_u *)uep->ue_array);
	}


	if (oldsize != newsize)
	{
	    mark_adjust(top + 1, top + oldsize, (long)MAXLNUM,
					       (long)newsize - (long)oldsize);
	    if (curbuf->b_op_start.lnum > top + oldsize)
		curbuf->b_op_start.lnum += newsize - oldsize;
	    if (curbuf->b_op_end.lnum > top + oldsize)
		curbuf->b_op_end.lnum += newsize - oldsize;
	}

	changed_lines(top + 1, 0, bot, newsize - oldsize);


	if (top + 1 < curbuf->b_op_start.lnum)
	    curbuf->b_op_start.lnum = top + 1;
	if (newsize == 0 && top + 1 > curbuf->b_op_end.lnum)
	    curbuf->b_op_end.lnum = top + 1;
	else if (top + newsize > curbuf->b_op_end.lnum)
	    curbuf->b_op_end.lnum = top + newsize;

	u_newcount += newsize;
	u_oldcount += oldsize;
	uep->ue_size = oldsize;
	uep->ue_array = newarray;
	uep->ue_bot = top + newsize + 1;


	nuep = uep->ue_next;
	uep->ue_next = newlist;
	newlist = uep;
    }

    curhead->uh_entry = newlist;
    curhead->uh_flags = new_flags;
    if ((old_flags & UH_EMPTYBUF) && bufempty())
	curbuf->b_ml.ml_flags |= ML_EMPTY;
    if (old_flags & UH_CHANGED)
	changed();
    else
#ifdef FEAT_NETBEANS_INTG

	if (!isNetbeansModified(curbuf))
#endif
	unchanged(curbuf, FALSE);


    for (i = 0; i < NMARKS; ++i)
    {
	if (curhead->uh_namedm[i].lnum != 0)
	    curbuf->b_namedm[i] = curhead->uh_namedm[i];
	if (namedm[i].lnum != 0)
	    curhead->uh_namedm[i] = namedm[i];
	else
	    curhead->uh_namedm[i].lnum = 0;
    }
    if (curhead->uh_visual.vi_start.lnum != 0)
    {
	curbuf->b_visual = curhead->uh_visual;
	curhead->uh_visual = visualinfo;
    }


    if (curhead->uh_cursor.lnum + 1 == curwin->w_cursor.lnum
						 && curwin->w_cursor.lnum > 1)
	--curwin->w_cursor.lnum;
    if (curwin->w_cursor.lnum <= curbuf->b_ml.ml_line_count)
    {
	if (curhead->uh_cursor.lnum == curwin->w_cursor.lnum)
	{
	    curwin->w_cursor.col = curhead->uh_cursor.col;
#ifdef FEAT_VIRTUALEDIT
	    if (virtual_active() && curhead->uh_cursor_vcol >= 0)
		coladvance((colnr_T)curhead->uh_cursor_vcol);
	    else
		curwin->w_cursor.coladd = 0;
#endif
	}
	else
	    beginline(BL_SOL | BL_FIX);
    }
    else
    {


	curwin->w_cursor.col = 0;
#ifdef FEAT_VIRTUALEDIT
	curwin->w_cursor.coladd = 0;
#endif
    }


    check_cursor();


    curbuf->b_u_seq_cur = curhead->uh_seq;
    if (undo)


	--curbuf->b_u_seq_cur;


    if (curhead->uh_save_nr != 0)
    {
	if (undo)
	    curbuf->b_u_save_nr_cur = curhead->uh_save_nr - 1;
	else
	    curbuf->b_u_save_nr_cur = curhead->uh_save_nr;
    }


    curbuf->b_u_time_cur = curhead->uh_time;

#ifdef FEAT_AUTOCMD
    unblock_autocmds();
#endif
#ifdef U_DEBUG
    u_check(FALSE);
#endif
}
