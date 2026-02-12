do_pending_operator(cmdarg_T *cap, int old_col, int gui_yank)
{
    oparg_T	*oap = cap->oap;
    pos_T	old_cursor;
    int		empty_region_error;
    int		restart_edit_save;
#ifdef FEAT_LINEBREAK
    int		lbr_saved = curwin->w_p_lbr;
#endif


    static redo_VIsual_T   redo_VIsual = {NUL, 0, 0, 0,0};

    int		    include_line_break = FALSE;

#if defined(FEAT_CLIPBOARD)


    if ((clip_star.available || clip_plus.available)
	    && oap->op_type != OP_NOP
	    && !gui_yank
	    && VIsual_active
	    && !redo_VIsual_busy
	    && oap->regname == 0)
	clip_auto_select();
#endif
    old_cursor = curwin->w_cursor;


    if ((finish_op || VIsual_active) && oap->op_type != OP_NOP)
    {


	int	redo_yank = vim_strchr(p_cpo, CPO_YANK) != NULL && !gui_yank;

#ifdef FEAT_LINEBREAK

	if (curwin->w_p_lbr)
	    curwin->w_valid &= ~VALID_VIRTCOL;
	curwin->w_p_lbr = FALSE;
#endif
	oap->is_VIsual = VIsual_active;
	if (oap->motion_force == 'V')
	    oap->motion_type = MLINE;
	else if (oap->motion_force == 'v')
	{


	    if (oap->motion_type == MLINE)
		oap->inclusive = FALSE;

	    else if (oap->motion_type == MCHAR)
		oap->inclusive = !oap->inclusive;
	    oap->motion_type = MCHAR;
	}
	else if (oap->motion_force == Ctrl_V)
	{

	    if (!VIsual_active)
	    {
		VIsual_active = TRUE;
		VIsual = oap->start;
	    }
	    VIsual_mode = Ctrl_V;
	    VIsual_select = FALSE;
	    VIsual_reselect = FALSE;
	}


	if ((redo_yank || oap->op_type != OP_YANK)
		&& ((!VIsual_active || oap->motion_force)

		    || (VIsual_active
			    && is_ex_cmdchar(cap) && oap->op_type != OP_COLON))
		&& cap->cmdchar != 'D'
#ifdef FEAT_FOLDING
		&& oap->op_type != OP_FOLD
		&& oap->op_type != OP_FOLDOPEN
		&& oap->op_type != OP_FOLDOPENREC
		&& oap->op_type != OP_FOLDCLOSE
		&& oap->op_type != OP_FOLDCLOSEREC
		&& oap->op_type != OP_FOLDDEL
		&& oap->op_type != OP_FOLDDELREC
#endif
		)
	{
	    prep_redo(oap->regname, cap->count0,
		    get_op_char(oap->op_type), get_extra_op_char(oap->op_type),
		    oap->motion_force, cap->cmdchar, cap->nchar);
	    if (cap->cmdchar == '/' || cap->cmdchar == '?')
	    {


		if (vim_strchr(p_cpo, CPO_REDO) == NULL)
		    AppendToRedobuffLit(cap->searchbuf, -1);
		AppendToRedobuff(NL_STR);
	    }
	    else if (is_ex_cmdchar(cap))
	    {


		if (repeat_cmdline == NULL)
		    ResetRedobuff();
		else
		{
		    AppendToRedobuffLit(repeat_cmdline, -1);
		    AppendToRedobuff(NL_STR);
		    VIM_CLEAR(repeat_cmdline);
		}
	    }
	}

	if (redo_VIsual_busy)
	{


	    oap->start = curwin->w_cursor;
	    curwin->w_cursor.lnum += redo_VIsual.rv_line_count - 1;
	    if (curwin->w_cursor.lnum > curbuf->b_ml.ml_line_count)
		curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
	    VIsual_mode = redo_VIsual.rv_mode;
	    if (redo_VIsual.rv_vcol == MAXCOL || VIsual_mode == 'v')
	    {
		if (VIsual_mode == 'v')
		{
		    if (redo_VIsual.rv_line_count <= 1)
		    {
			validate_virtcol();
			curwin->w_curswant =
				     curwin->w_virtcol + redo_VIsual.rv_vcol - 1;
		    }
		    else
			curwin->w_curswant = redo_VIsual.rv_vcol;
		}
		else
		{
		    curwin->w_curswant = MAXCOL;
		}
		coladvance(curwin->w_curswant);
	    }
	    cap->count0 = redo_VIsual.rv_count;
	    if (redo_VIsual.rv_count != 0)
		cap->count1 = redo_VIsual.rv_count;
	    else
		cap->count1 = 1;
	}
	else if (VIsual_active)
	{
	    if (!gui_yank)
	    {

		curbuf->b_visual.vi_start = VIsual;
		curbuf->b_visual.vi_end = curwin->w_cursor;
		curbuf->b_visual.vi_mode = VIsual_mode;
		restore_visual_mode();
		curbuf->b_visual.vi_curswant = curwin->w_curswant;
# ifdef FEAT_EVAL
		curbuf->b_visual_mode_eval = VIsual_mode;
# endif
	    }


	    if (VIsual_select && VIsual_mode == 'V'
					    && cap->oap->op_type != OP_DELETE)
	    {
		if (LT_POS(VIsual, curwin->w_cursor))
		{
		    VIsual.col = 0;
		    curwin->w_cursor.col =
			       (colnr_T)STRLEN(ml_get(curwin->w_cursor.lnum));
		}
		else
		{
		    curwin->w_cursor.col = 0;
		    VIsual.col = (colnr_T)STRLEN(ml_get(VIsual.lnum));
		}
		VIsual_mode = 'v';
	    }


	    else if (VIsual_mode == 'v')
		include_line_break = unadjust_for_sel();

	    oap->start = VIsual;
	    if (VIsual_mode == 'V')
	    {
		oap->start.col = 0;
		oap->start.coladd = 0;
	    }
	}


	if (LT_POS(oap->start, curwin->w_cursor))
	{
#ifdef FEAT_FOLDING

	    if (!VIsual_active)
	    {
		if (hasFolding(oap->start.lnum, &oap->start.lnum, NULL))
		    oap->start.col = 0;
		if ((curwin->w_cursor.col > 0 || oap->inclusive
						  || oap->motion_type == MLINE)
			&& hasFolding(curwin->w_cursor.lnum, NULL,
						      &curwin->w_cursor.lnum))
		    curwin->w_cursor.col = (colnr_T)STRLEN(ml_get_curline());
	    }
#endif
	    oap->end = curwin->w_cursor;
	    curwin->w_cursor = oap->start;


	    curwin->w_valid &= ~VALID_VIRTCOL;
	}
	else
	{
#ifdef FEAT_FOLDING

	    if (!VIsual_active && oap->motion_type == MLINE)
	    {
		if (hasFolding(curwin->w_cursor.lnum, &curwin->w_cursor.lnum,
									NULL))
		    curwin->w_cursor.col = 0;
		if (hasFolding(oap->start.lnum, NULL, &oap->start.lnum))
		    oap->start.col = (colnr_T)STRLEN(ml_get(oap->start.lnum));
	    }
#endif
	    oap->end = oap->start;
	    oap->start = curwin->w_cursor;
	}


	check_pos(curwin->w_buffer, &oap->end);
	oap->line_count = oap->end.lnum - oap->start.lnum + 1;


	virtual_op = virtual_active();

	if (VIsual_active || redo_VIsual_busy)
	{
	    get_op_vcol(oap, redo_VIsual.rv_vcol, TRUE);

	    if (!redo_VIsual_busy && !gui_yank)
	    {


		resel_VIsual_mode = VIsual_mode;
		if (curwin->w_curswant == MAXCOL)
		    resel_VIsual_vcol = MAXCOL;
		else
		{
		    if (VIsual_mode != Ctrl_V)
			getvvcol(curwin, &(oap->end),
						  NULL, NULL, &oap->end_vcol);
		    if (VIsual_mode == Ctrl_V || oap->line_count <= 1)
		    {
			if (VIsual_mode != Ctrl_V)
			    getvvcol(curwin, &(oap->start),
						&oap->start_vcol, NULL, NULL);
			resel_VIsual_vcol = oap->end_vcol - oap->start_vcol + 1;
		    }
		    else
			resel_VIsual_vcol = oap->end_vcol;
		}
		resel_VIsual_line_count = oap->line_count;
	    }


	    if ((redo_yank || oap->op_type != OP_YANK)
		    && oap->op_type != OP_COLON
#ifdef FEAT_FOLDING
		    && oap->op_type != OP_FOLD
		    && oap->op_type != OP_FOLDOPEN
		    && oap->op_type != OP_FOLDOPENREC
		    && oap->op_type != OP_FOLDCLOSE
		    && oap->op_type != OP_FOLDCLOSEREC
		    && oap->op_type != OP_FOLDDEL
		    && oap->op_type != OP_FOLDDELREC
#endif
		    && oap->motion_force == NUL
		    )
	    {


		if (cap->cmdchar == 'g' && (cap->nchar == 'n'
							|| cap->nchar == 'N'))
		    prep_redo(oap->regname, cap->count0,
			    get_op_char(oap->op_type),
			    get_extra_op_char(oap->op_type),
			    oap->motion_force, cap->cmdchar, cap->nchar);
		else if (!is_ex_cmdchar(cap))
		{
		    int opchar = get_op_char(oap->op_type);
		    int extra_opchar = get_extra_op_char(oap->op_type);
		    int nchar = oap->op_type == OP_REPLACE ? cap->nchar : NUL;


		    if (nchar == REPLACE_CR_NCHAR)
			nchar = CAR;
		    else if (nchar == REPLACE_NL_NCHAR)
			nchar = NL;

		    if (opchar == 'g' && extra_opchar == '@')

			prep_redo_num2(oap->regname, 0L, NUL, 'v',
				     cap->count0, opchar, extra_opchar, nchar);
		    else
			prep_redo(oap->regname, 0L, NUL, 'v',
						  opchar, extra_opchar, nchar);
		}
		if (!redo_VIsual_busy)
		{
		    redo_VIsual.rv_mode = resel_VIsual_mode;
		    redo_VIsual.rv_vcol = resel_VIsual_vcol;
		    redo_VIsual.rv_line_count = resel_VIsual_line_count;
		    redo_VIsual.rv_count = cap->count0;
		    redo_VIsual.rv_arg = cap->arg;
		}
	    }


	    if (oap->motion_force == NUL || oap->motion_type == MLINE)
		oap->inclusive = TRUE;
	    if (VIsual_mode == 'V')
		oap->motion_type = MLINE;
	    else
	    {
		oap->motion_type = MCHAR;
		if (VIsual_mode != Ctrl_V && *ml_get_pos(&(oap->end)) == NUL
			&& (include_line_break || !virtual_op))
		{
		    oap->inclusive = FALSE;


		    if (*p_sel != 'o'
			    && !op_on_lines(oap->op_type)
			    && oap->end.lnum < curbuf->b_ml.ml_line_count)
		    {
			++oap->end.lnum;
			oap->end.col = 0;
			oap->end.coladd = 0;
			++oap->line_count;
		    }
		}
	    }

	    redo_VIsual_busy = FALSE;


	    if (!gui_yank)
	    {
		VIsual_active = FALSE;
		setmouse();
		mouse_dragging = 0;
		may_clear_cmdline();
		if ((oap->op_type == OP_YANK
			    || oap->op_type == OP_COLON
			    || oap->op_type == OP_FUNCTION
			    || oap->op_type == OP_FILTER)
			&& oap->motion_force == NUL)
		{
#ifdef FEAT_LINEBREAK

		    curwin->w_p_lbr = lbr_saved;
#endif
		    redraw_curbuf_later(INVERTED);
		}
	    }
	}


	if (has_mbyte && oap->inclusive)
	{
	    int		l;

	    l = (*mb_ptr2len)(ml_get_pos(&oap->end));
	    if (l > 1)
		oap->end.col += l - 1;
	}
	curwin->w_set_curswant = TRUE;


	oap->empty = (oap->motion_type == MCHAR
		    && (!oap->inclusive
			|| (oap->op_type == OP_YANK
			    && gchar_pos(&oap->end) == NUL))
		    && EQUAL_POS(oap->start, oap->end)
		    && !(virtual_op && oap->start.coladd != oap->end.coladd));


	empty_region_error = (oap->empty
				&& vim_strchr(p_cpo, CPO_EMPTYREGION) != NULL);


	if (oap->is_VIsual && (oap->empty || !curbuf->b_p_ma
#ifdef FEAT_FOLDING
		    || oap->op_type == OP_FOLD
#endif
		    ))
	{
#ifdef FEAT_LINEBREAK
	    curwin->w_p_lbr = lbr_saved;
#endif
	    redraw_curbuf_later(INVERTED);
	}


	if (	   oap->motion_type == MCHAR
		&& oap->inclusive == FALSE
		&& !(cap->retval & CA_NO_ADJ_OP_END)
		&& oap->end.col == 0
		&& (!oap->is_VIsual || *p_sel == 'o')
		&& !oap->block_mode
		&& oap->line_count > 1)
	{
	    oap->end_adjusted = TRUE;
	    --oap->line_count;
	    --oap->end.lnum;
	    if (inindent(0))
		oap->motion_type = MLINE;
	    else
	    {
		oap->end.col = (colnr_T)STRLEN(ml_get(oap->end.lnum));
		if (oap->end.col)
		{
		    --oap->end.col;
		    oap->inclusive = TRUE;
		}
	    }
	}
	else
	    oap->end_adjusted = FALSE;

	switch (oap->op_type)
	{
	case OP_LSHIFT:
	case OP_RSHIFT:
	    op_shift(oap, TRUE, oap->is_VIsual ? (int)cap->count1 : 1);
	    auto_format(FALSE, TRUE);
	    break;

	case OP_JOIN_NS:
	case OP_JOIN:
	    if (oap->line_count < 2)
		oap->line_count = 2;
	    if (curwin->w_cursor.lnum + oap->line_count - 1 >
						   curbuf->b_ml.ml_line_count)
		beep_flush();
	    else
	    {
		(void)do_join(oap->line_count, oap->op_type == OP_JOIN,
							    TRUE, TRUE, TRUE);
		auto_format(FALSE, TRUE);
	    }
	    break;

	case OP_DELETE:
	    VIsual_reselect = FALSE;
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
	    {
		(void)op_delete(oap);

		if (oap->motion_type == MLINE && has_format_option(FO_AUTO)
						      && u_save_cursor() == OK)
		    auto_format(FALSE, TRUE);
	    }
	    break;

	case OP_YANK:
	    if (empty_region_error)
	    {
		if (!gui_yank)
		{
		    vim_beep(BO_OPER);
		    CancelRedo();
		}
	    }
	    else
	    {
#ifdef FEAT_LINEBREAK
		curwin->w_p_lbr = lbr_saved;
#endif
		oap->excl_tr_ws = cap->cmdchar == 'z';
		(void)op_yank(oap, FALSE, !gui_yank);
	    }
	    check_cursor_col();
	    break;

	case OP_CHANGE:
	    VIsual_reselect = FALSE;
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
	    {


		if (p_im || !KeyTyped)
		    restart_edit_save = restart_edit;
		else
		    restart_edit_save = 0;
		restart_edit = 0;
#ifdef FEAT_LINEBREAK


		curwin->w_p_lbr = lbr_saved;
#endif

		finish_op = FALSE;
		if (op_change(oap))
		    cap->retval |= CA_COMMAND_BUSY;
		if (restart_edit == 0)
		    restart_edit = restart_edit_save;
	    }
	    break;

	case OP_FILTER:
	    if (vim_strchr(p_cpo, CPO_FILTER) != NULL)
		AppendToRedobuff((char_u *)"!\r");
	    else
		bangredo = TRUE;


	case OP_INDENT:
	case OP_COLON:

#if defined(FEAT_LISP) || defined(FEAT_CINDENT)

	    if (oap->op_type == OP_INDENT && *get_equalprg() == NUL)
	    {
# ifdef FEAT_LISP
		if (curbuf->b_p_lisp)
		{
		    op_reindent(oap, get_lisp_indent);
		    break;
		}
# endif
# ifdef FEAT_CINDENT
		op_reindent(oap,
#  ifdef FEAT_EVAL
			*curbuf->b_p_inde != NUL ? get_expr_indent :
#  endif
			    get_c_indent);
		break;
# endif
	    }
#endif

	    op_colon(oap);
	    break;

	case OP_TILDE:
	case OP_UPPER:
	case OP_LOWER:
	case OP_ROT13:
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
		op_tilde(oap);
	    check_cursor_col();
	    break;

	case OP_FORMAT:
#if defined(FEAT_EVAL)
	    if (*curbuf->b_p_fex != NUL)
		op_formatexpr(oap);
	    else
#endif
	    {
		if (*p_fp != NUL || *curbuf->b_p_fp != NUL)
		    op_colon(oap);
		else
		    op_format(oap, FALSE);
	    }
	    break;
	case OP_FORMAT2:
	    op_format(oap, TRUE);
	    break;

	case OP_FUNCTION:
	    {
		redo_VIsual_T   save_redo_VIsual = redo_VIsual;

#ifdef FEAT_LINEBREAK


		curwin->w_p_lbr = lbr_saved;
#endif

		op_function(oap);


		redo_VIsual = save_redo_VIsual;
		break;
	    }

	case OP_INSERT:
	case OP_APPEND:
	    VIsual_reselect = FALSE;
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
	    {


		restart_edit_save = restart_edit;
		restart_edit = 0;
#ifdef FEAT_LINEBREAK


		curwin->w_p_lbr = lbr_saved;
#endif
		op_insert(oap, cap->count1);
#ifdef FEAT_LINEBREAK

		curwin->w_p_lbr = FALSE;
#endif


		auto_format(FALSE, TRUE);

		if (restart_edit == 0)
		    restart_edit = restart_edit_save;
		else
		    cap->retval |= CA_COMMAND_BUSY;
	    }
	    break;

	case OP_REPLACE:
	    VIsual_reselect = FALSE;
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
	    {
#ifdef FEAT_LINEBREAK


		curwin->w_p_lbr = lbr_saved;
#endif
		op_replace(oap, cap->nchar);
	    }
	    break;

#ifdef FEAT_FOLDING
	case OP_FOLD:
	    VIsual_reselect = FALSE;
	    foldCreate(oap->start.lnum, oap->end.lnum);
	    break;

	case OP_FOLDOPEN:
	case OP_FOLDOPENREC:
	case OP_FOLDCLOSE:
	case OP_FOLDCLOSEREC:
	    VIsual_reselect = FALSE;
	    opFoldRange(oap->start.lnum, oap->end.lnum,
		    oap->op_type == OP_FOLDOPEN
					    || oap->op_type == OP_FOLDOPENREC,
		    oap->op_type == OP_FOLDOPENREC
					  || oap->op_type == OP_FOLDCLOSEREC,
					  oap->is_VIsual);
	    break;

	case OP_FOLDDEL:
	case OP_FOLDDELREC:
	    VIsual_reselect = FALSE;
	    deleteFold(oap->start.lnum, oap->end.lnum,
			       oap->op_type == OP_FOLDDELREC, oap->is_VIsual);
	    break;
#endif
	case OP_NR_ADD:
	case OP_NR_SUB:
	    if (empty_region_error)
	    {
		vim_beep(BO_OPER);
		CancelRedo();
	    }
	    else
	    {
		VIsual_active = TRUE;
#ifdef FEAT_LINEBREAK
		curwin->w_p_lbr = lbr_saved;
#endif
		op_addsub(oap, cap->count1, redo_VIsual.rv_arg);
		VIsual_active = FALSE;
	    }
	    check_cursor_col();
	    break;
	default:
	    clearopbeep(oap);
	}
	virtual_op = MAYBE;
	if (!gui_yank)
	{

	    if (!p_sol && oap->motion_type == MLINE && !oap->end_adjusted
		    && (oap->op_type == OP_LSHIFT || oap->op_type == OP_RSHIFT
						|| oap->op_type == OP_DELETE))
	    {
#ifdef FEAT_LINEBREAK
		curwin->w_p_lbr = FALSE;
#endif
		coladvance(curwin->w_curswant = old_col);
	    }
	}
	else
	{
	    curwin->w_cursor = old_cursor;
	}
	oap->block_mode = FALSE;
	clearop(oap);
	motion_force = NUL;
    }
#ifdef FEAT_LINEBREAK
    curwin->w_p_lbr = lbr_saved;
#endif
}
