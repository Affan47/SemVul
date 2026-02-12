op_addsub(
    oparg_T	*oap,
    linenr_T	Prenum1,
    int		g_cmd)
{
    pos_T		pos;
    struct block_def	bd;
    int			change_cnt = 0;
    linenr_T		amount = Prenum1;


#ifdef FEAT_FOLDING
   disable_fold_update++;
#endif

    if (!VIsual_active)
    {
	pos = curwin->w_cursor;
	if (u_save_cursor() == FAIL)
	{
#ifdef FEAT_FOLDING
	    disable_fold_update--;
#endif
	    return;
	}
	change_cnt = do_addsub(oap->op_type, &pos, 0, amount);
#ifdef FEAT_FOLDING
	disable_fold_update--;
#endif
	if (change_cnt)
	    changed_lines(pos.lnum, 0, pos.lnum + 1, 0L);
    }
    else
    {
	int	one_change;
	int	length;
	pos_T	startpos;

	if (u_save((linenr_T)(oap->start.lnum - 1),
					(linenr_T)(oap->end.lnum + 1)) == FAIL)
	{
#ifdef FEAT_FOLDING
	    disable_fold_update--;
#endif
	    return;
	}

	pos = oap->start;
	for (; pos.lnum <= oap->end.lnum; ++pos.lnum)
	{
	    if (oap->block_mode)
	    {
		block_prep(oap, &bd, pos.lnum, FALSE);
		pos.col = bd.textcol;
		length = bd.textlen;
	    }
	    else if (oap->motion_type == MLINE)
	    {
		curwin->w_cursor.col = 0;
		pos.col = 0;
		length = (colnr_T)STRLEN(ml_get(pos.lnum));
	    }
	    else
	    {
		if (pos.lnum == oap->start.lnum && !oap->inclusive)
		    dec(&(oap->end));
		length = (colnr_T)STRLEN(ml_get(pos.lnum));
		pos.col = 0;
		if (pos.lnum == oap->start.lnum)
		{
		    pos.col += oap->start.col;
		    length -= oap->start.col;
		}
		if (pos.lnum == oap->end.lnum)
		{
		    length = (int)STRLEN(ml_get(oap->end.lnum));
		    if (oap->end.col >= length)
			oap->end.col = length - 1;
		    length = oap->end.col - pos.col + 1;
		}
	    }
	    one_change = do_addsub(oap->op_type, &pos, length, amount);
	    if (one_change)
	    {

		if (change_cnt == 0)
		    startpos = curbuf->b_op_start;
		++change_cnt;
	    }

#ifdef FEAT_NETBEANS_INTG
	    if (netbeans_active() && one_change)
	    {
		char_u *ptr;

		netbeans_removed(curbuf, pos.lnum, pos.col, (long)length);
		ptr = ml_get_buf(curbuf, pos.lnum, FALSE);
		netbeans_inserted(curbuf, pos.lnum, pos.col,
						&ptr[pos.col], length);
	    }
#endif
	    if (g_cmd && one_change)
		amount += Prenum1;
	}

#ifdef FEAT_FOLDING
	disable_fold_update--;
#endif
	if (change_cnt)
	    changed_lines(oap->start.lnum, 0, oap->end.lnum + 1, 0L);

	if (!change_cnt && oap->is_VIsual)

	    redraw_curbuf_later(INVERTED);


	if (change_cnt > 0 && (cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	    curbuf->b_op_start = startpos;

	if (change_cnt > p_report)
	    smsg(NGETTEXT("%d line changed", "%d lines changed",
						      change_cnt), change_cnt);
    }
}
