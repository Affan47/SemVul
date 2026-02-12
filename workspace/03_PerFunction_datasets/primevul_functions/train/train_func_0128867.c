edit(
    int		cmdchar,
    int		startln,
    long	count)
{
    int		c = 0;
    char_u	*ptr;
    int		lastc = 0;
    int		mincol;
    static linenr_T o_lnum = 0;
    int		i;
    int		did_backspace = TRUE;
#ifdef FEAT_CINDENT
    int		line_is_white = FALSE;
#endif
    linenr_T	old_topline = 0;
#ifdef FEAT_DIFF
    int		old_topfill = -1;
#endif
    int		inserted_space = FALSE;
    int		replaceState = REPLACE;
    int		nomove = FALSE;
#ifdef FEAT_JOB_CHANNEL
    int		cmdchar_todo = cmdchar;
#endif


    did_restart_edit = restart_edit;


    check_for_delay(TRUE);


    update_Insstart_orig = TRUE;

#ifdef HAVE_SANDBOX

    if (sandbox != 0)
    {
	emsg(_(e_sandbox));
	return FALSE;
    }
#endif


    if (textlock != 0)
    {
	emsg(_(e_secure));
	return FALSE;
    }


    if (ins_compl_active() || compl_busy || pum_visible())
    {
	emsg(_(e_secure));
	return FALSE;
    }
    ins_compl_clear();


    if (cmdchar != 'r' && cmdchar != 'v')
    {
	pos_T   save_cursor = curwin->w_cursor;

#ifdef FEAT_EVAL
	if (cmdchar == 'R')
	    ptr = (char_u *)"r";
	else if (cmdchar == 'V')
	    ptr = (char_u *)"v";
	else
	    ptr = (char_u *)"i";
	set_vim_var_string(VV_INSERTMODE, ptr, 1);
	set_vim_var_string(VV_CHAR, NULL, -1);
#endif
	ins_apply_autocmds(EVENT_INSERTENTER);


	if (!EQUAL_POS(curwin->w_cursor, save_cursor)
#ifdef FEAT_EVAL
		&& *get_vim_var_str(VV_CHAR) == NUL
#endif
		&& save_cursor.lnum <= curbuf->b_ml.ml_line_count)
	{
	    int save_state = State;

	    curwin->w_cursor = save_cursor;
	    State = INSERT;
	    check_cursor_col();
	    State = save_state;
	}
    }

#ifdef FEAT_CONCEAL


    conceal_check_cursor_line();
#endif


    if (where_paste_started.lnum != 0)
	Insstart = where_paste_started;
    else
    {
	Insstart = curwin->w_cursor;
	if (startln)
	    Insstart.col = 0;
    }
    Insstart_textlen = (colnr_T)linetabsize(ml_get_curline());
    Insstart_blank_vcol = MAXCOL;
    if (!did_ai)
	ai_col = 0;

    if (cmdchar != NUL && restart_edit == 0)
    {
	ResetRedobuff();
	AppendNumberToRedobuff(count);
	if (cmdchar == 'V' || cmdchar == 'v')
	{

	    AppendCharToRedobuff('g');
	    AppendCharToRedobuff((cmdchar == 'v') ? 'r' : 'R');
	}
	else
	{
	    if (cmdchar == K_PS)
		AppendCharToRedobuff('a');
	    else
		AppendCharToRedobuff(cmdchar);
	    if (cmdchar == 'g')
		AppendCharToRedobuff('I');
	    else if (cmdchar == 'r')
		count = 1;
	}
    }

    if (cmdchar == 'R')
    {
	State = REPLACE;
    }
    else if (cmdchar == 'V' || cmdchar == 'v')
    {
	State = VREPLACE;
	replaceState = VREPLACE;
	orig_line_count = curbuf->b_ml.ml_line_count;
	vr_lines_changed = 1;
    }
    else
	State = INSERT;

    stop_insert_mode = FALSE;


    curs_columns(TRUE);


    if (curbuf->b_p_iminsert == B_IMODE_LMAP)
	State |= LANGMAP;
#ifdef HAVE_INPUT_METHOD
    im_set_active(curbuf->b_p_iminsert == B_IMODE_IM);
#endif

    setmouse();
#ifdef FEAT_CMDL_INFO
    clear_showcmd();
#endif
#ifdef FEAT_RIGHTLEFT

    revins_on = (State == INSERT && p_ri);
    if (revins_on)
	undisplay_dollar();
    revins_chars = 0;
    revins_legal = 0;
    revins_scol = -1;
#endif
    if (!p_ek)
    {


	out_str(T_BD);


	out_str(T_CTE);
    }


    if (restart_edit != 0 && stuff_empty())
    {


	if (where_paste_started.lnum)
	    arrow_used = FALSE;
	else
	    arrow_used = TRUE;
	restart_edit = 0;


	validate_virtcol();
	update_curswant();
	if (((ins_at_eol && curwin->w_cursor.lnum == o_lnum)
		    || curwin->w_curswant > curwin->w_virtcol)
		&& *(ptr = ml_get_curline() + curwin->w_cursor.col) != NUL)
	{
	    if (ptr[1] == NUL)
		++curwin->w_cursor.col;
	    else if (has_mbyte)
	    {
		i = (*mb_ptr2len)(ptr);
		if (ptr[i] == NUL)
		    curwin->w_cursor.col += i;
	    }
	}
	ins_at_eol = FALSE;
    }
    else
	arrow_used = FALSE;


    need_start_insertmode = FALSE;


    ins_need_undo = TRUE;

    where_paste_started.lnum = 0;
#ifdef FEAT_CINDENT
    can_cindent = TRUE;
#endif
#ifdef FEAT_FOLDING


    if (!p_im && did_restart_edit == 0)
	foldOpenCursor();
#endif


    i = 0;
    if (p_smd && msg_silent == 0)
	i = showmode();

    if (!p_im && did_restart_edit == 0)
	change_warning(i == 0 ? 0 : i + 1);

#ifdef CURSOR_SHAPE
    ui_cursor_shape();
#endif
#ifdef FEAT_DIGRAPHS
    do_digraph(-1);
#endif


    ptr = get_inserted();
    if (ptr == NULL)
	new_insert_skip = 0;
    else
    {
	new_insert_skip = (int)STRLEN(ptr);
	vim_free(ptr);
    }

    old_indent = 0;


    for (;;)
    {
#ifdef FEAT_RIGHTLEFT
	if (!revins_legal)
	    revins_scol = -1;
	else
	    revins_legal = 0;
#endif
	if (arrow_used)
	    count = 0;

	if (update_Insstart_orig)
	    Insstart_orig = Insstart;

	if (stop_insert_mode && !pum_visible())
	{

	    count = 0;
	    goto doESCkey;
	}


	if (!arrow_used)
	    curwin->w_set_curswant = TRUE;


	if (stuff_empty())
	{
	    did_check_timestamps = FALSE;
	    if (need_check_timestamps)
		check_timestamps(FALSE);
	}


	msg_scroll = FALSE;

#ifdef FEAT_GUI


	if (need_mouse_correct)
	    gui_mouse_correct();
#endif

#ifdef FEAT_FOLDING

	if (fdo_flags & FDO_INSERT)
	    foldOpenCursor();

	if (!char_avail())
	    foldCheckClose();
#endif

#ifdef FEAT_JOB_CHANNEL
	if (bt_prompt(curbuf))
	{
	    init_prompt(cmdchar_todo);
	    cmdchar_todo = NUL;
	}
#endif


	if (curbuf->b_mod_set
		&& curwin->w_p_wrap
		&& !did_backspace
		&& curwin->w_topline == old_topline
#ifdef FEAT_DIFF
		&& curwin->w_topfill == old_topfill
#endif
		)
	{
	    mincol = curwin->w_wcol;
	    validate_cursor_col();

	    if (
#ifdef FEAT_VARTABS
		(int)curwin->w_wcol < mincol - tabstop_at(
					  get_nolist_virtcol(), curbuf->b_p_ts,
							 curbuf->b_p_vts_array)
#else
		(int)curwin->w_wcol < mincol - curbuf->b_p_ts
#endif
		    && curwin->w_wrow == W_WINROW(curwin)
				 + curwin->w_height - 1 - get_scrolloff_value()
		    && (curwin->w_cursor.lnum != curwin->w_topline
#ifdef FEAT_DIFF
			|| curwin->w_topfill > 0
#endif
		    ))
	    {
#ifdef FEAT_DIFF
		if (curwin->w_topfill > 0)
		    --curwin->w_topfill;
		else
#endif
#ifdef FEAT_FOLDING
		if (hasFolding(curwin->w_topline, NULL, &old_topline))
		    set_topline(curwin, old_topline + 1);
		else
#endif
		    set_topline(curwin, curwin->w_topline + 1);
	    }
	}


	update_topline();

	did_backspace = FALSE;

	validate_cursor();


	ins_redraw(TRUE);

	if (curwin->w_p_scb)
	    do_check_scrollbind(TRUE);

	if (curwin->w_p_crb)
	    do_check_cursorbind();
	update_curswant();
	old_topline = curwin->w_topline;
#ifdef FEAT_DIFF
	old_topfill = curwin->w_topfill;
#endif

#ifdef USE_ON_FLY_SCROLL
	dont_scroll = FALSE;
#endif


	if (c != K_CURSORHOLD)
	    lastc = c;


	if (dont_sync_undo == MAYBE)
	    dont_sync_undo = TRUE;
	else
	    dont_sync_undo = FALSE;
	if (cmdchar == K_PS)

	    c = K_PS;
	else
	    do
	    {
		c = safe_vgetc();

		if (stop_insert_mode)
		{

		    count = 0;
		    nomove = TRUE;
		    goto doESCkey;
		}
	    } while (c == K_IGNORE || c == K_NOP);


	did_cursorhold = TRUE;

#ifdef FEAT_RIGHTLEFT
	if (p_hkmap && KeyTyped)
	    c = hkmap(c);
#endif


	if (ins_compl_active()
		&& pum_wanted()
		&& curwin->w_cursor.col >= ins_compl_col()
		&& ins_compl_has_shown_match())
	{

	    if ((c == K_BS || c == Ctrl_H)
			&& curwin->w_cursor.col > ins_compl_col()
			&& (c = ins_compl_bs()) == NUL)
		continue;


	    if (!ins_compl_used_match())
	    {


		if (c == Ctrl_L
			&& (!ctrl_x_mode_line_or_eval()
			    || ins_compl_long_shown_match()))
		{
		    ins_compl_addfrommatch();
		    continue;
		}


		if (ins_compl_accept_char(c))
		{
#if defined(FEAT_EVAL)

		    char_u *str = do_insert_char_pre(c);
		    char_u *p;

		    if (str != NULL)
		    {
			for (p = str; *p != NUL; MB_PTR_ADV(p))
			    ins_compl_addleader(PTR2CHAR(p));
			vim_free(str);
		    }
		    else
#endif
			ins_compl_addleader(c);
		    continue;
		}


		if ((c == Ctrl_Y || (ins_compl_enter_selects()
				    && (c == CAR || c == K_KENTER || c == NL)))
			&& stop_arrow() == OK)
		{
		    ins_compl_delete();
		    ins_compl_insert(FALSE);
		}
	    }
	}


	ins_compl_init_get_longest();
	if (ins_compl_prep(c))
	    continue;


	if (c == Ctrl_BSL)
	{

	    ins_redraw(FALSE);
	    ++no_mapping;
	    ++allow_keys;
	    c = plain_vgetc();
	    --no_mapping;
	    --allow_keys;
	    if (c != Ctrl_N && c != Ctrl_G && c != Ctrl_O)
	    {

		vungetc(c);
		c = Ctrl_BSL;
	    }
	    else if (c == Ctrl_G && p_im)
		continue;
	    else
	    {
		if (c == Ctrl_O)
		{
		    ins_ctrl_o();
		    ins_at_eol = FALSE;
		    nomove = TRUE;
		}
		count = 0;
		goto doESCkey;
	    }
	}

#ifdef FEAT_DIGRAPHS
	c = do_digraph(c);
#endif

	if ((c == Ctrl_V || c == Ctrl_Q) && ctrl_x_mode_cmdline())
	    goto docomplete;
	if (c == Ctrl_V || c == Ctrl_Q)
	{
	    ins_ctrl_v();
	    c = Ctrl_V;
	    continue;
	}

#ifdef FEAT_CINDENT
	if (cindent_on() && ctrl_x_mode_none())
	{


	    line_is_white = inindent(0);
	    if (in_cinkeys(c, '!', line_is_white))
		goto force_cindent;
	    if (can_cindent && in_cinkeys(c, '*', line_is_white)
							&& stop_arrow() == OK)
		do_c_expr_indent();
	}
#endif

#ifdef FEAT_RIGHTLEFT
	if (curwin->w_p_rl)
	    switch (c)
	    {
		case K_LEFT:	c = K_RIGHT; break;
		case K_S_LEFT:	c = K_S_RIGHT; break;
		case K_C_LEFT:	c = K_C_RIGHT; break;
		case K_RIGHT:	c = K_LEFT; break;
		case K_S_RIGHT: c = K_S_LEFT; break;
		case K_C_RIGHT: c = K_C_LEFT; break;
	    }
#endif


	if (ins_start_select(c))
	    continue;


	switch (c)
	{
	case ESC:
	    if (echeck_abbr(ESC + ABBR_OFF))
		break;


	case Ctrl_C:
#ifdef FEAT_CMDWIN
	    if (c == Ctrl_C && cmdwin_type != 0)
	    {

		cmdwin_result = K_IGNORE;
		got_int = FALSE;
		nomove = TRUE;
		goto doESCkey;
	    }
#endif
#ifdef FEAT_JOB_CHANNEL
	    if (c == Ctrl_C && bt_prompt(curbuf))
	    {
		if (invoke_prompt_interrupt())
		{
		    if (!bt_prompt(curbuf))


			goto doESCkey;
		    break;
		}
	    }
#endif

#ifdef UNIX
do_intr:
#endif


	    if (goto_im())
	    {
		if (got_int)
		{
		    (void)vgetc();
		    got_int = FALSE;
		}
		else
		    vim_beep(BO_IM);
		break;
	    }
doESCkey:


	    if (ins_at_eol && gchar_cursor() == NUL)
		o_lnum = curwin->w_cursor.lnum;

	    if (ins_esc(&count, cmdchar, nomove))
	    {


		if (cmdchar != 'r' && cmdchar != 'v' && c != Ctrl_C)
		    ins_apply_autocmds(EVENT_INSERTLEAVE);
		did_cursorhold = FALSE;
		return (c == Ctrl_O);
	    }
	    continue;

	case Ctrl_Z:
	    if (!p_im)
		goto normalchar;
	    do_cmdline_cmd((char_u *)"stop");
#ifdef CURSOR_SHAPE
	    ui_cursor_shape();
#endif
	    continue;

	case Ctrl_O:
#ifdef FEAT_COMPL_FUNC
	    if (ctrl_x_mode_omni())
		goto docomplete;
#endif
	    if (echeck_abbr(Ctrl_O + ABBR_OFF))
		break;
	    ins_ctrl_o();


	    if (ve_flags & VE_ONEMORE)
	    {
		ins_at_eol = FALSE;
		nomove = TRUE;
	    }
	    count = 0;
	    goto doESCkey;

	case K_INS:
	case K_KINS:
	    ins_insert(replaceState);
	    break;

	case K_SELECT:
	    break;

	case K_HELP:
	case K_F1:
	case K_XF1:
	    stuffcharReadbuff(K_HELP);
	    if (p_im)
		need_start_insertmode = TRUE;
	    goto doESCkey;

#ifdef FEAT_NETBEANS_INTG
	case K_F21:
	    ++no_mapping;
	    i = plain_vgetc();
	    --no_mapping;
	    netbeans_keycommand(i);
	    break;
#endif

	case K_ZERO:
	case NUL:
	case Ctrl_A:


	    if (stuff_inserted(NUL, 1L, (c == Ctrl_A)) == FAIL
						   && c != Ctrl_A && !p_im)
		goto doESCkey;
	    inserted_space = FALSE;
	    break;

	case Ctrl_R:
	    ins_reg();
	    auto_format(FALSE, TRUE);
	    inserted_space = FALSE;
	    break;

	case Ctrl_G:
	    ins_ctrl_g();
	    break;

	case Ctrl_HAT:
	    ins_ctrl_hat();
	    break;

#ifdef FEAT_RIGHTLEFT
	case Ctrl__:
	    if (!p_ari)
		goto normalchar;
	    ins_ctrl_();
	    break;
#endif

	case Ctrl_D:
#if defined(FEAT_FIND_ID)
	    if (ctrl_x_mode_path_defines())
		goto docomplete;
#endif


	case Ctrl_T:
	    if (c == Ctrl_T && ctrl_x_mode_thesaurus())
	    {
		if (has_compl_option(FALSE))
		    goto docomplete;
		break;
	    }

	    ins_shift(c, lastc);
	    auto_format(FALSE, TRUE);
	    inserted_space = FALSE;
	    break;

	case K_DEL:
	case K_KDEL:
	    ins_del();
	    auto_format(FALSE, TRUE);
	    break;

	case K_BS:
	case Ctrl_H:
	    did_backspace = ins_bs(c, BACKSPACE_CHAR, &inserted_space);
	    auto_format(FALSE, TRUE);
	    break;

	case Ctrl_W:
#ifdef FEAT_JOB_CHANNEL
	    if (bt_prompt(curbuf) && (mod_mask & MOD_MASK_SHIFT) == 0)
	    {


		stuffcharReadbuff(Ctrl_W);
		restart_edit = 'A';
		nomove = TRUE;
		count = 0;
		goto doESCkey;
	    }
#endif
	    did_backspace = ins_bs(c, BACKSPACE_WORD, &inserted_space);
	    auto_format(FALSE, TRUE);
	    break;

	case Ctrl_U:
# ifdef FEAT_COMPL_FUNC

	    if (ctrl_x_mode_function())
		goto docomplete;
# endif
	    did_backspace = ins_bs(c, BACKSPACE_LINE, &inserted_space);
	    auto_format(FALSE, TRUE);
	    inserted_space = FALSE;
	    break;

	case K_LEFTMOUSE:
	case K_LEFTMOUSE_NM:
	case K_LEFTDRAG:
	case K_LEFTRELEASE:
	case K_LEFTRELEASE_NM:
	case K_MOUSEMOVE:
	case K_MIDDLEMOUSE:
	case K_MIDDLEDRAG:
	case K_MIDDLERELEASE:
	case K_RIGHTMOUSE:
	case K_RIGHTDRAG:
	case K_RIGHTRELEASE:
	case K_X1MOUSE:
	case K_X1DRAG:
	case K_X1RELEASE:
	case K_X2MOUSE:
	case K_X2DRAG:
	case K_X2RELEASE:
	    ins_mouse(c);
	    break;

	case K_MOUSEDOWN:
	    ins_mousescroll(MSCR_DOWN);
	    break;

	case K_MOUSEUP:
	    ins_mousescroll(MSCR_UP);
	    break;

	case K_MOUSELEFT:
	    ins_mousescroll(MSCR_LEFT);
	    break;

	case K_MOUSERIGHT:
	    ins_mousescroll(MSCR_RIGHT);
	    break;

	case K_PS:
	    bracketed_paste(PASTE_INSERT, FALSE, NULL);
	    if (cmdchar == K_PS)

		goto doESCkey;
	    break;
	case K_PE:

	    break;

#ifdef FEAT_GUI_TABLINE
	case K_TABLINE:
	case K_TABMENU:
	    ins_tabline(c);
	    break;
#endif

	case K_IGNORE:
	    break;

	case K_CURSORHOLD:
	    ins_apply_autocmds(EVENT_CURSORHOLDI);
	    did_cursorhold = TRUE;
	    break;

#ifdef FEAT_GUI_MSWIN


	case K_F4:
	    if (mod_mask != MOD_MASK_ALT)
		goto normalchar;
	    break;
#endif

#ifdef FEAT_GUI
	case K_VER_SCROLLBAR:
	    ins_scroll();
	    break;

	case K_HOR_SCROLLBAR:
	    ins_horscroll();
	    break;
#endif

	case K_HOME:
	case K_KHOME:
	case K_S_HOME:
	case K_C_HOME:
	    ins_home(c);
	    break;

	case K_END:
	case K_KEND:
	case K_S_END:
	case K_C_END:
	    ins_end(c);
	    break;

	case K_LEFT:
	    if (mod_mask & (MOD_MASK_SHIFT|MOD_MASK_CTRL))
		ins_s_left();
	    else
		ins_left();
	    break;

	case K_S_LEFT:
	case K_C_LEFT:
	    ins_s_left();
	    break;

	case K_RIGHT:
	    if (mod_mask & (MOD_MASK_SHIFT|MOD_MASK_CTRL))
		ins_s_right();
	    else
		ins_right();
	    break;

	case K_S_RIGHT:
	case K_C_RIGHT:
	    ins_s_right();
	    break;

	case K_UP:
	    if (pum_visible())
		goto docomplete;
	    if (mod_mask & MOD_MASK_SHIFT)
		ins_pageup();
	    else
		ins_up(FALSE);
	    break;

	case K_S_UP:
	case K_PAGEUP:
	case K_KPAGEUP:
	    if (pum_visible())
		goto docomplete;
	    ins_pageup();
	    break;

	case K_DOWN:
	    if (pum_visible())
		goto docomplete;
	    if (mod_mask & MOD_MASK_SHIFT)
		ins_pagedown();
	    else
		ins_down(FALSE);
	    break;

	case K_S_DOWN:
	case K_PAGEDOWN:
	case K_KPAGEDOWN:
	    if (pum_visible())
		goto docomplete;
	    ins_pagedown();
	    break;

#ifdef FEAT_DND
	case K_DROP:
	    ins_drop();
	    break;
#endif

	case K_S_TAB:
	    c = TAB;


	case TAB:
#if defined(FEAT_FIND_ID)
	    if (ctrl_x_mode_path_patterns())
		goto docomplete;
#endif
	    inserted_space = FALSE;
	    if (ins_tab())
		goto normalchar;
	    auto_format(FALSE, TRUE);
	    break;

	case K_KENTER:
	    c = CAR;

	case CAR:
	case NL:
#if defined(FEAT_QUICKFIX)


	    if (bt_quickfix(curbuf) && c == CAR)
	    {
		if (curwin->w_llist_ref == NULL)
		    do_cmdline_cmd((char_u *)".cc");
		else
		    do_cmdline_cmd((char_u *)".ll");
		break;
	    }
#endif
#ifdef FEAT_CMDWIN
	    if (cmdwin_type != 0)
	    {

		cmdwin_result = CAR;
		goto doESCkey;
	    }
#endif
#ifdef FEAT_JOB_CHANNEL
	    if (bt_prompt(curbuf))
	    {
		invoke_prompt_callback();
		if (!bt_prompt(curbuf))


		    goto doESCkey;
		break;
	    }
#endif
	    if (ins_eol(c) == FAIL && !p_im)
		goto doESCkey;
	    auto_format(FALSE, FALSE);
	    inserted_space = FALSE;
	    break;

	case Ctrl_K:
	    if (ctrl_x_mode_dictionary())
	    {
		if (has_compl_option(TRUE))
		    goto docomplete;
		break;
	    }
#ifdef FEAT_DIGRAPHS
	    c = ins_digraph();
	    if (c == NUL)
		break;
#endif
	    goto normalchar;

	case Ctrl_X:
	    ins_ctrl_x();
	    break;

	case Ctrl_RSB:
	    if (!ctrl_x_mode_tags())
		goto normalchar;
	    goto docomplete;

	case Ctrl_F:
	    if (!ctrl_x_mode_files())
		goto normalchar;
	    goto docomplete;

	case 's':
	case Ctrl_S:
	    if (!ctrl_x_mode_spell())
		goto normalchar;
	    goto docomplete;

	case Ctrl_L:
	    if (!ctrl_x_mode_whole_line())
	    {

		if (p_im)
		{
		    if (echeck_abbr(Ctrl_L + ABBR_OFF))
			break;
		    goto doESCkey;
		}
		goto normalchar;
	    }


	case Ctrl_P:
	case Ctrl_N:


	    if (*curbuf->b_p_cpt == NUL
		    && (ctrl_x_mode_normal() || ctrl_x_mode_whole_line())
		    && !(compl_cont_status & CONT_LOCAL))
		goto normalchar;

docomplete:
	    compl_busy = TRUE;
#ifdef FEAT_FOLDING
	    disable_fold_update++;
#endif
	    if (ins_complete(c, TRUE) == FAIL)
		compl_cont_status = 0;
#ifdef FEAT_FOLDING
	    disable_fold_update--;
#endif
	    compl_busy = FALSE;
	    break;

	case Ctrl_Y:
	case Ctrl_E:
	    c = ins_ctrl_ey(c);
	    break;

	  default:
#ifdef UNIX
	    if (c == intr_char)
		goto do_intr;
#endif

normalchar:


#if defined(FEAT_EVAL)
	    if (!p_paste)
	    {

		char_u *str = do_insert_char_pre(c);
		char_u *p;

		if (str != NULL)
		{
		    if (*str != NUL && stop_arrow() != FAIL)
		    {

			for (p = str; *p != NUL; MB_PTR_ADV(p))
			{
			    c = PTR2CHAR(p);
			    if (c == CAR || c == K_KENTER || c == NL)
				ins_eol(c);
			    else
				ins_char(c);
			}
			AppendToRedobuffLit(str, -1);
		    }
		    vim_free(str);
		    c = NUL;
		}


		if (c == NUL)
		    break;
	    }
#endif
#ifdef FEAT_SMARTINDENT

	    ins_try_si(c);
#endif

	    if (c == ' ')
	    {
		inserted_space = TRUE;
#ifdef FEAT_CINDENT
		if (inindent(0))
		    can_cindent = FALSE;
#endif
		if (Insstart_blank_vcol == MAXCOL
			&& curwin->w_cursor.lnum == Insstart.lnum)
		    Insstart_blank_vcol = get_nolist_virtcol();
	    }


	    if (vim_iswordc(c) || (!echeck_abbr(


				(has_mbyte && c >= 0x100) ? (c + ABBR_OFF) : c)
			&& c != Ctrl_RSB))
	    {
		insert_special(c, FALSE, FALSE);
#ifdef FEAT_RIGHTLEFT
		revins_legal++;
		revins_chars++;
#endif
	    }

	    auto_format(FALSE, TRUE);

#ifdef FEAT_FOLDING


	    foldOpenCursor();
#endif
	    break;
	}


	if (c != K_CURSORHOLD
#ifdef FEAT_COMPL_FUNC

		&& ctrl_x_mode_normal()
#endif
	       )
	    did_cursorhold = FALSE;


	if (arrow_used)
	    inserted_space = FALSE;

#ifdef FEAT_CINDENT
	if (can_cindent && cindent_on() && ctrl_x_mode_normal())
	{
force_cindent:


	    if (in_cinkeys(c, ' ', line_is_white))
	    {
		if (stop_arrow() == OK)

		    do_c_expr_indent();
	    }
	}
#endif

    }

}
