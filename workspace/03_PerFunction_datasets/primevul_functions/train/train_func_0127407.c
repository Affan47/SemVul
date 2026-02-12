nv_zet(cmdarg_T *cap)
{
    long	n;
    colnr_T	col;
    int		nchar = cap->nchar;
#ifdef FEAT_FOLDING
    long	old_fdl = curwin->w_p_fdl;
    int		old_fen = curwin->w_p_fen;
#endif
#ifdef FEAT_SPELL
    int		undo = FALSE;
#endif
    long        siso = get_sidescrolloff_value();

    if (VIM_ISDIGIT(nchar))
    {


	if (checkclearop(cap->oap))
	    return;
	n = nchar - '0';
	for (;;)
	{
#ifdef USE_ON_FLY_SCROLL
	    dont_scroll = TRUE;
#endif
	    ++no_mapping;
	    ++allow_keys;
	    nchar = plain_vgetc();
	    LANGMAP_ADJUST(nchar, TRUE);
	    --no_mapping;
	    --allow_keys;
#ifdef FEAT_CMDL_INFO
	    (void)add_to_showcmd(nchar);
#endif
	    if (nchar == K_DEL || nchar == K_KDEL)
		n /= 10;
	    else if (VIM_ISDIGIT(nchar))
		n = n * 10 + (nchar - '0');
	    else if (nchar == CAR)
	    {
#ifdef FEAT_GUI
		need_mouse_correct = TRUE;
#endif
		win_setheight((int)n);
		break;
	    }
	    else if (nchar == 'l'
		    || nchar == 'h'
		    || nchar == K_LEFT
		    || nchar == K_RIGHT)
	    {
		cap->count1 = n ? n * cap->count1 : cap->count1;
		goto dozet;
	    }
	    else
	    {
		clearopbeep(cap->oap);
		break;
	    }
	}
	cap->oap->op_type = OP_NOP;
	return;
    }

dozet:
    if (
#ifdef FEAT_FOLDING


	    cap->nchar != 'f' && cap->nchar != 'F'
	    && !(VIsual_active && vim_strchr((char_u *)"dcCoO", cap->nchar))
	    && cap->nchar != 'j' && cap->nchar != 'k'
	    &&
#endif
	    checkclearop(cap->oap))
	return;


    if ((vim_strchr((char_u *)"+\r\nt.z^-b", nchar) != NULL)
	    && cap->count0
	    && cap->count0 != curwin->w_cursor.lnum)
    {
	setpcmark();
	if (cap->count0 > curbuf->b_ml.ml_line_count)
	    curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
	else
	    curwin->w_cursor.lnum = cap->count0;
	check_cursor_col();
    }

    switch (nchar)
    {

    case '+':
		if (cap->count0 == 0)
		{

		    validate_botline();
		    if (curwin->w_botline > curbuf->b_ml.ml_line_count)
			curwin->w_cursor.lnum = curbuf->b_ml.ml_line_count;
		    else
			curwin->w_cursor.lnum = curwin->w_botline;
		}

    case NL:
    case CAR:
    case K_KENTER:
		beginline(BL_WHITE | BL_FIX);


    case 't':	scroll_cursor_top(0, TRUE);
		redraw_later(VALID);
		set_fraction(curwin);
		break;


    case '.':	beginline(BL_WHITE | BL_FIX);


    case 'z':	scroll_cursor_halfway(TRUE);
		redraw_later(VALID);
		set_fraction(curwin);
		break;


    case '^':


		if (cap->count0 != 0)
		{
		    scroll_cursor_bot(0, TRUE);
		    curwin->w_cursor.lnum = curwin->w_topline;
		}
		else if (curwin->w_topline == 1)
		    curwin->w_cursor.lnum = 1;
		else
		    curwin->w_cursor.lnum = curwin->w_topline - 1;

    case '-':
		beginline(BL_WHITE | BL_FIX);


    case 'b':	scroll_cursor_bot(0, TRUE);
		redraw_later(VALID);
		set_fraction(curwin);
		break;


    case 'H':
		cap->count1 *= curwin->w_width / 2;


    case 'h':
    case K_LEFT:
		if (!curwin->w_p_wrap)
		{
		    if ((colnr_T)cap->count1 > curwin->w_leftcol)
			curwin->w_leftcol = 0;
		    else
			curwin->w_leftcol -= (colnr_T)cap->count1;
		    leftcol_changed();
		}
		break;


    case 'L':	cap->count1 *= curwin->w_width / 2;


    case 'l':
    case K_RIGHT:
		if (!curwin->w_p_wrap)
		{

		    curwin->w_leftcol += (colnr_T)cap->count1;
		    leftcol_changed();
		}
		break;


    case 's':	if (!curwin->w_p_wrap)
		{
#ifdef FEAT_FOLDING
		    if (hasFolding(curwin->w_cursor.lnum, NULL, NULL))
			col = 0;
		    else
#endif
		    getvcol(curwin, &curwin->w_cursor, &col, NULL, NULL);
		    if ((long)col > siso)
			col -= siso;
		    else
			col = 0;
		    if (curwin->w_leftcol != col)
		    {
			curwin->w_leftcol = col;
			redraw_later(NOT_VALID);
		    }
		}
		break;


    case 'e':	if (!curwin->w_p_wrap)
		{
#ifdef FEAT_FOLDING
		    if (hasFolding(curwin->w_cursor.lnum, NULL, NULL))
			col = 0;
		    else
#endif
		    getvcol(curwin, &curwin->w_cursor, NULL, NULL, &col);
		    n = curwin->w_width - curwin_col_off();
		    if ((long)col + siso < n)
			col = 0;
		    else
			col = col + siso - n + 1;
		    if (curwin->w_leftcol != col)
		    {
			curwin->w_leftcol = col;
			redraw_later(NOT_VALID);
		    }
		}
		break;


    case 'P':
    case 'p':  nv_put(cap);
	       break;

    case 'y':  nv_operator(cap);
	       break;
#ifdef FEAT_FOLDING


    case 'F':
    case 'f':   if (foldManualAllowed(TRUE))
		{
		    cap->nchar = 'f';
		    nv_operator(cap);
		    curwin->w_p_fen = TRUE;


		    if (nchar == 'F' && cap->oap->op_type == OP_FOLD)
		    {
			nv_operator(cap);
			finish_op = TRUE;
		    }
		}
		else
		    clearopbeep(cap->oap);
		break;


    case 'd':
    case 'D':	if (foldManualAllowed(FALSE))
		{
		    if (VIsual_active)
			nv_operator(cap);
		    else
			deleteFold(curwin->w_cursor.lnum,
				  curwin->w_cursor.lnum, nchar == 'D', FALSE);
		}
		break;


    case 'E':	if (foldmethodIsManual(curwin))
		{
		    clearFolding(curwin);
		    changed_window_setting();
		}
		else if (foldmethodIsMarker(curwin))
		    deleteFold((linenr_T)1, curbuf->b_ml.ml_line_count,
								 TRUE, FALSE);
		else
		    emsg(_("E352: Cannot erase folds with current 'foldmethod'"));
		break;


    case 'n':	curwin->w_p_fen = FALSE;
		break;


    case 'N':	curwin->w_p_fen = TRUE;
		break;


    case 'i':	curwin->w_p_fen = !curwin->w_p_fen;
		break;


    case 'a':	if (hasFolding(curwin->w_cursor.lnum, NULL, NULL))
		    openFold(curwin->w_cursor.lnum, cap->count1);
		else
		{
		    closeFold(curwin->w_cursor.lnum, cap->count1);
		    curwin->w_p_fen = TRUE;
		}
		break;


    case 'A':	if (hasFolding(curwin->w_cursor.lnum, NULL, NULL))
		    openFoldRecurse(curwin->w_cursor.lnum);
		else
		{
		    closeFoldRecurse(curwin->w_cursor.lnum);
		    curwin->w_p_fen = TRUE;
		}
		break;


    case 'o':	if (VIsual_active)
		    nv_operator(cap);
		else
		    openFold(curwin->w_cursor.lnum, cap->count1);
		break;


    case 'O':	if (VIsual_active)
		    nv_operator(cap);
		else
		    openFoldRecurse(curwin->w_cursor.lnum);
		break;


    case 'c':	if (VIsual_active)
		    nv_operator(cap);
		else
		    closeFold(curwin->w_cursor.lnum, cap->count1);
		curwin->w_p_fen = TRUE;
		break;


    case 'C':	if (VIsual_active)
		    nv_operator(cap);
		else
		    closeFoldRecurse(curwin->w_cursor.lnum);
		curwin->w_p_fen = TRUE;
		break;


    case 'v':	foldOpenCursor();
		break;


    case 'x':	curwin->w_p_fen = TRUE;
		curwin->w_foldinvalid = TRUE;
		newFoldLevel();
		foldOpenCursor();
		break;


    case 'X':	curwin->w_p_fen = TRUE;
		curwin->w_foldinvalid = TRUE;
		old_fdl = -1;
		break;


    case 'm':	if (curwin->w_p_fdl > 0)
		{
		    curwin->w_p_fdl -= cap->count1;
		    if (curwin->w_p_fdl < 0)
			curwin->w_p_fdl = 0;
		}
		old_fdl = -1;
		curwin->w_p_fen = TRUE;
		break;


    case 'M':	curwin->w_p_fdl = 0;
		old_fdl = -1;
		curwin->w_p_fen = TRUE;
		break;


    case 'r':	curwin->w_p_fdl += cap->count1;
		{
		    int d = getDeepestNesting();

		    if (curwin->w_p_fdl >= d)
			curwin->w_p_fdl = d;
		}
		break;


    case 'R':	curwin->w_p_fdl = getDeepestNesting();
		old_fdl = -1;
		break;

    case 'j':
    case 'k':
		if (foldMoveTo(TRUE, nchar == 'j' ? FORWARD : BACKWARD,
							  cap->count1) == FAIL)
		    clearopbeep(cap->oap);
		break;

#endif

#ifdef FEAT_SPELL
    case 'u':
		++no_mapping;
		++allow_keys;
		nchar = plain_vgetc();
		LANGMAP_ADJUST(nchar, TRUE);
		--no_mapping;
		--allow_keys;
#ifdef FEAT_CMDL_INFO
		(void)add_to_showcmd(nchar);
#endif
		if (vim_strchr((char_u *)"gGwW", nchar) == NULL)
		{
		    clearopbeep(cap->oap);
		    break;
		}
		undo = TRUE;


    case 'g':
    case 'w':
    case 'G':
    case 'W':
		{
		    char_u  *ptr = NULL;
		    int	    len;

		    if (checkclearop(cap->oap))
			break;
		    if (VIsual_active && get_visual_text(cap, &ptr, &len)
								      == FAIL)
			return;
		    if (ptr == NULL)
		    {
			pos_T	pos = curwin->w_cursor;


			emsg_off++;
			len = spell_move_to(curwin, FORWARD, TRUE, TRUE, NULL);
			emsg_off--;
			if (len != 0 && curwin->w_cursor.col <= pos.col)
			    ptr = ml_get_pos(&curwin->w_cursor);
			curwin->w_cursor = pos;
		    }

		    if (ptr == NULL && (len = find_ident_under_cursor(&ptr,
							    FIND_IDENT)) == 0)
			return;
		    spell_add_word(ptr, len, nchar == 'w' || nchar == 'W'
					      ? SPELL_ADD_BAD : SPELL_ADD_GOOD,
					    (nchar == 'G' || nchar == 'W')
						       ? 0 : (int)cap->count1,
					    undo);
		}
		break;

    case '=':
		if (!checkclearop(cap->oap))
		    spell_suggest((int)cap->count0);
		break;
#endif

    default:	clearopbeep(cap->oap);
    }

#ifdef FEAT_FOLDING

    if (old_fen != curwin->w_p_fen)
    {
# ifdef FEAT_DIFF
	win_T	    *wp;

	if (foldmethodIsDiff(curwin) && curwin->w_p_scb)
	{

	    FOR_ALL_WINDOWS(wp)
	    {
		if (wp != curwin && foldmethodIsDiff(wp) && wp->w_p_scb)
		{
		    wp->w_p_fen = curwin->w_p_fen;
		    changed_window_setting_win(wp);
		}
	    }
	}
# endif
	changed_window_setting();
    }


    if (old_fdl != curwin->w_p_fdl)
	newFoldLevel();
#endif
}
