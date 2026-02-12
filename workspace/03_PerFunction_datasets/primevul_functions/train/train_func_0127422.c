nv_g_cmd(cmdarg_T *cap)
{
    oparg_T	*oap = cap->oap;
    pos_T	tpos;
    int		i;
    int		flag = FALSE;

    switch (cap->nchar)
    {
    case Ctrl_A:
    case Ctrl_X:
#ifdef MEM_PROFILE


	if (!VIsual_active && cap->nchar == Ctrl_A)
	    vim_mem_profile_dump();
	else
#endif


	     if (VIsual_active)
	{
	    cap->arg = TRUE;
	    cap->cmdchar = cap->nchar;
	    cap->nchar = NUL;
	    nv_addsub(cap);
	}
	else
	    clearopbeep(oap);
	break;


    case 'R':
	cap->arg = TRUE;
	nv_Replace(cap);
	break;

    case 'r':
	nv_vreplace(cap);
	break;

    case '&':
	do_cmdline_cmd((char_u *)"%s//~/&");
	break;


    case 'v':
	if (checkclearop(oap))
	    break;

	if (	   curbuf->b_visual.vi_start.lnum == 0
		|| curbuf->b_visual.vi_start.lnum > curbuf->b_ml.ml_line_count
		|| curbuf->b_visual.vi_end.lnum == 0)
	    beep_flush();
	else
	{

	    if (VIsual_active)
	    {
		i = VIsual_mode;
		VIsual_mode = curbuf->b_visual.vi_mode;
		curbuf->b_visual.vi_mode = i;
# ifdef FEAT_EVAL
		curbuf->b_visual_mode_eval = i;
# endif
		i = curwin->w_curswant;
		curwin->w_curswant = curbuf->b_visual.vi_curswant;
		curbuf->b_visual.vi_curswant = i;

		tpos = curbuf->b_visual.vi_end;
		curbuf->b_visual.vi_end = curwin->w_cursor;
		curwin->w_cursor = curbuf->b_visual.vi_start;
		curbuf->b_visual.vi_start = VIsual;
	    }
	    else
	    {
		VIsual_mode = curbuf->b_visual.vi_mode;
		curwin->w_curswant = curbuf->b_visual.vi_curswant;
		tpos = curbuf->b_visual.vi_end;
		curwin->w_cursor = curbuf->b_visual.vi_start;
	    }

	    VIsual_active = TRUE;
	    VIsual_reselect = TRUE;


	    check_cursor();
	    VIsual = curwin->w_cursor;
	    curwin->w_cursor = tpos;
	    check_cursor();
	    update_topline();


	    if (cap->arg)
		VIsual_select = TRUE;
	    else
		may_start_select('c');
	    setmouse();
#ifdef FEAT_CLIPBOARD


	    clip_star.vmode = NUL;
#endif
	    redraw_curbuf_later(INVERTED);
	    showmode();
	}
	break;


    case 'V':
	VIsual_reselect = FALSE;
	break;


    case K_BS:
	cap->nchar = Ctrl_H;

    case 'h':
    case 'H':
    case Ctrl_H:
# ifdef EBCDIC

	if (cap->nchar == Ctrl_H)
	    cap->cmdchar = Ctrl_V;
	else
# endif
	cap->cmdchar = cap->nchar + ('v' - 'h');
	cap->arg = TRUE;
	nv_visual(cap);
	break;


    case 'N':
    case 'n':
	if (!current_search(cap->count1, cap->nchar == 'n'))
	    clearopbeep(oap);
	break;


    case 'j':
    case K_DOWN:

	if (!curwin->w_p_wrap)
	{
	    oap->motion_type = MLINE;
	    i = cursor_down(cap->count1, oap->op_type == OP_NOP);
	}
	else
	    i = nv_screengo(oap, FORWARD, cap->count1);
	if (i == FAIL)
	    clearopbeep(oap);
	break;

    case 'k':
    case K_UP:

	if (!curwin->w_p_wrap)
	{
	    oap->motion_type = MLINE;
	    i = cursor_up(cap->count1, oap->op_type == OP_NOP);
	}
	else
	    i = nv_screengo(oap, BACKWARD, cap->count1);
	if (i == FAIL)
	    clearopbeep(oap);
	break;


    case 'J':
	nv_join(cap);
	break;


    case '^':
	flag = TRUE;


    case '0':
    case 'm':
    case K_HOME:
    case K_KHOME:
	oap->motion_type = MCHAR;
	oap->inclusive = FALSE;
	if (curwin->w_p_wrap && curwin->w_width != 0)
	{
	    int		width1 = curwin->w_width - curwin_col_off();
	    int		width2 = width1 + curwin_col_off2();

	    validate_virtcol();
	    i = 0;
	    if (curwin->w_virtcol >= (colnr_T)width1 && width2 > 0)
		i = (curwin->w_virtcol - width1) / width2 * width2 + width1;
	}
	else
	    i = curwin->w_leftcol;


	if (cap->nchar == 'm')
	    i += (curwin->w_width - curwin_col_off()
		    + ((curwin->w_p_wrap && i > 0)
			? curwin_col_off2() : 0)) / 2;
	coladvance((colnr_T)i);
	if (flag)
	{
	    do
		i = gchar_cursor();
	    while (VIM_ISWHITE(i) && oneright() == OK);
	    curwin->w_valid &= ~VALID_WCOL;
	}
	curwin->w_set_curswant = TRUE;
	break;

    case 'M':
	{
	    char_u  *ptr = ml_get_curline();

	    oap->motion_type = MCHAR;
	    oap->inclusive = FALSE;
	    if (has_mbyte)
		i = mb_string2cells(ptr, (int)STRLEN(ptr));
	    else
		i = (int)STRLEN(ptr);
	    if (cap->count0 > 0 && cap->count0 <= 100)
		coladvance((colnr_T)(i * cap->count0 / 100));
	    else
		coladvance((colnr_T)(i / 2));
	    curwin->w_set_curswant = TRUE;
	}
	break;

    case '_':


	cap->oap->motion_type = MCHAR;
	cap->oap->inclusive = TRUE;
	curwin->w_curswant = MAXCOL;
	if (cursor_down((long)(cap->count1 - 1),
					 cap->oap->op_type == OP_NOP) == FAIL)
	    clearopbeep(cap->oap);
	else
	{
	    char_u  *ptr = ml_get_curline();


	    if (curwin->w_cursor.col > 0 && ptr[curwin->w_cursor.col] == NUL)
		--curwin->w_cursor.col;


	    while (curwin->w_cursor.col > 0
				    && VIM_ISWHITE(ptr[curwin->w_cursor.col]))
		--curwin->w_cursor.col;
	    curwin->w_set_curswant = TRUE;
	    adjust_for_sel(cap);
	}
	break;

    case '$':
    case K_END:
    case K_KEND:
	{
	    int col_off = curwin_col_off();

	    oap->motion_type = MCHAR;
	    oap->inclusive = TRUE;
	    if (curwin->w_p_wrap && curwin->w_width != 0)
	    {
		curwin->w_curswant = MAXCOL;
		if (cap->count1 == 1)
		{
		    int		width1 = curwin->w_width - col_off;
		    int		width2 = width1 + curwin_col_off2();

		    validate_virtcol();
		    i = width1 - 1;
		    if (curwin->w_virtcol >= (colnr_T)width1)
			i += ((curwin->w_virtcol - width1) / width2 + 1)
								     * width2;
		    coladvance((colnr_T)i);


		    validate_virtcol();
		    curwin->w_curswant = curwin->w_virtcol;
		    curwin->w_set_curswant = FALSE;
		    if (curwin->w_cursor.col > 0 && curwin->w_p_wrap)
		    {


			if (curwin->w_virtcol > (colnr_T)i)
			    --curwin->w_cursor.col;
		    }
		}
		else if (nv_screengo(oap, FORWARD, cap->count1 - 1) == FAIL)
		    clearopbeep(oap);
	    }
	    else
	    {
		if (cap->count1 > 1)

		    (void)cursor_down(cap->count1 - 1, FALSE);

		i = curwin->w_leftcol + curwin->w_width - col_off - 1;
		coladvance((colnr_T)i);


		if (curwin->w_cursor.col > 0
				       && (*mb_ptr2cells)(ml_get_cursor()) > 1)
		{
		    colnr_T vcol;

		    getvvcol(curwin, &curwin->w_cursor, NULL, NULL, &vcol);
		    if (vcol >= curwin->w_leftcol + curwin->w_width - col_off)
			--curwin->w_cursor.col;
		}


		validate_virtcol();
		curwin->w_curswant = curwin->w_virtcol;
		curwin->w_set_curswant = FALSE;
	    }
	}
	break;


    case '*':
    case '#':
#if POUND != '#'
    case POUND:
#endif
    case Ctrl_RSB:
    case ']':
	nv_ident(cap);
	break;


    case 'e':
    case 'E':
	oap->motion_type = MCHAR;
	curwin->w_set_curswant = TRUE;
	oap->inclusive = TRUE;
	if (bckend_word(cap->count1, cap->nchar == 'E', FALSE) == FAIL)
	    clearopbeep(oap);
	break;


    case Ctrl_G:
	cursor_pos_info(NULL);
	break;


    case 'i':
	if (curbuf->b_last_insert.lnum != 0)
	{
	    curwin->w_cursor = curbuf->b_last_insert;
	    check_cursor_lnum();
	    i = (int)STRLEN(ml_get_curline());
	    if (curwin->w_cursor.col > (colnr_T)i)
	    {
		if (virtual_active())
		    curwin->w_cursor.coladd += curwin->w_cursor.col - i;
		curwin->w_cursor.col = i;
	    }
	}
	cap->cmdchar = 'i';
	nv_edit(cap);
	break;


    case 'I':
	beginline(0);
	if (!checkclearopq(oap))
	    invoke_edit(cap, FALSE, 'g', FALSE);
	break;

#ifdef FEAT_SEARCHPATH


    case 'f':
    case 'F':
	nv_gotofile(cap);
	break;
#endif


    case '\'':
	cap->arg = TRUE;

    case '`':
	nv_gomark(cap);
	break;


    case 's':
	do_sleep(cap->count1 * 1000L, FALSE);
	break;


    case 'a':
	do_ascii(NULL);
	break;


    case '8':
	if (cap->count0 == 8)
	    utf_find_illegal();
	else
	    show_utf8();
	break;


    case '<':
	show_sb_text();
	break;


    case 'g':
	cap->arg = FALSE;
	nv_goto(cap);
	break;


    case 'q':
    case 'w':
	oap->cursor_start = curwin->w_cursor;

    case '~':
    case 'u':
    case 'U':
    case '?':
    case '@':
	nv_operator(cap);
	break;


    case 'd':
    case 'D':
	nv_gd(oap, cap->nchar, (int)cap->count0);
	break;


    case K_MIDDLEMOUSE:
    case K_MIDDLEDRAG:
    case K_MIDDLERELEASE:
    case K_LEFTMOUSE:
    case K_LEFTDRAG:
    case K_LEFTRELEASE:
    case K_MOUSEMOVE:
    case K_RIGHTMOUSE:
    case K_RIGHTDRAG:
    case K_RIGHTRELEASE:
    case K_X1MOUSE:
    case K_X1DRAG:
    case K_X1RELEASE:
    case K_X2MOUSE:
    case K_X2DRAG:
    case K_X2RELEASE:
	mod_mask = MOD_MASK_CTRL;
	(void)do_mouse(oap, cap->nchar, BACKWARD, cap->count1, 0);
	break;

    case K_IGNORE:
	break;


    case 'p':
    case 'P':
	nv_put(cap);
	break;

#ifdef FEAT_BYTEOFF

    case 'o':
	goto_byte(cap->count0);
	break;
#endif


    case 'Q':
	if (text_locked())
	{
	    clearopbeep(cap->oap);
	    text_locked_msg();
	    break;
	}

	if (!checkclearopq(oap))
	    do_exmode(TRUE);
	break;

#ifdef FEAT_JUMPLIST
    case ',':
	nv_pcmark(cap);
	break;

    case ';':
	cap->count1 = -cap->count1;
	nv_pcmark(cap);
	break;
#endif

    case 't':
	if (!checkclearop(oap))
	    goto_tabpage((int)cap->count0);
	break;
    case 'T':
	if (!checkclearop(oap))
	    goto_tabpage(-(int)cap->count1);
	break;

    case TAB:
	if (!checkclearop(oap) && goto_tabpage_lastused() == FAIL)
	    clearopbeep(oap);
	break;

    case '+':
    case '-':
	if (!checkclearopq(oap))
	    undo_time(cap->nchar == '-' ? -cap->count1 : cap->count1,
							 FALSE, FALSE, FALSE);
	break;

    default:
	clearopbeep(oap);
	break;
    }
}
