normal_cmd(
    oparg_T	*oap,
    int		toplevel UNUSED)
{
    cmdarg_T	ca;
    int		c;
    int		ctrl_w = FALSE;
    int		old_col = curwin->w_curswant;
#ifdef FEAT_CMDL_INFO
    int		need_flushbuf;
#endif
    pos_T	old_pos;
    int		mapped_len;
    static int	old_mapped_len = 0;
    int		idx;
#ifdef FEAT_EVAL
    int		set_prevcount = FALSE;
#endif
    int		save_did_cursorhold = did_cursorhold;

    CLEAR_FIELD(ca);
    ca.oap = oap;


    ca.opcount = opcount;


#ifdef CURSOR_SHAPE
    c = finish_op;
#endif
    finish_op = (oap->op_type != OP_NOP);
#ifdef CURSOR_SHAPE
    if (finish_op != c)
    {
	ui_cursor_shape();
# ifdef FEAT_MOUSESHAPE
	update_mouseshape(-1);
# endif
    }
#endif
    trigger_modechanged();


    if (!finish_op && !oap->regname)
    {
	ca.opcount = 0;
#ifdef FEAT_EVAL
	set_prevcount = TRUE;
#endif
    }


    if (oap->prev_opcount > 0 || oap->prev_count0 > 0)
    {
	ca.opcount = oap->prev_opcount;
	ca.count0 = oap->prev_count0;
	oap->prev_opcount = 0;
	oap->prev_count0 = 0;
    }

    mapped_len = typebuf_maplen();

    State = NORMAL_BUSY;
#ifdef USE_ON_FLY_SCROLL
    dont_scroll = FALSE;
#endif

#ifdef FEAT_EVAL


    if (toplevel && readbuf1_empty())
	set_vcount_ca(&ca, &set_prevcount);
#endif


    c = safe_vgetc();
    LANGMAP_ADJUST(c, get_real_state() != SELECTMODE);


    if (restart_edit == 0)
	old_mapped_len = 0;
    else if (old_mapped_len
		|| (VIsual_active && mapped_len == 0 && typebuf_maplen() > 0))
	old_mapped_len = typebuf_maplen();

    if (c == NUL)
	c = K_ZERO;


    if (VIsual_active
	    && VIsual_select
	    && (vim_isprintc(c) || c == NL || c == CAR || c == K_KENTER))
    {


	ins_char_typebuf(vgetc_char, vgetc_mod_mask);
	if (restart_edit != 0)
	    c = 'd';
	else
	    c = 'c';
	msg_nowait = TRUE;
	old_mapped_len = 0;
    }

#ifdef FEAT_CMDL_INFO
    need_flushbuf = add_to_showcmd(c);
#endif

getcount:
    if (!(VIsual_active && VIsual_select))
    {


	while (    (c >= '1' && c <= '9')
		|| (ca.count0 != 0 && (c == K_DEL || c == K_KDEL || c == '0')))
	{
	    if (c == K_DEL || c == K_KDEL)
	    {
		ca.count0 /= 10;
#ifdef FEAT_CMDL_INFO
		del_from_showcmd(4);
#endif
	    }
	    else
		ca.count0 = ca.count0 * 10 + (c - '0');
	    if (ca.count0 < 0)
		ca.count0 = 999999999L;
#ifdef FEAT_EVAL


	    if (toplevel && readbuf1_empty())
		set_vcount_ca(&ca, &set_prevcount);
#endif
	    if (ctrl_w)
	    {
		++no_mapping;
		++allow_keys;
	    }
	    ++no_zero_mapping;
	    c = plain_vgetc();
	    LANGMAP_ADJUST(c, TRUE);
	    --no_zero_mapping;
	    if (ctrl_w)
	    {
		--no_mapping;
		--allow_keys;
	    }
#ifdef FEAT_CMDL_INFO
	    need_flushbuf |= add_to_showcmd(c);
#endif
	}


	if (c == Ctrl_W && !ctrl_w && oap->op_type == OP_NOP)
	{
	    ctrl_w = TRUE;
	    ca.opcount = ca.count0;
	    ca.count0 = 0;
	    ++no_mapping;
	    ++allow_keys;
	    c = plain_vgetc();
	    LANGMAP_ADJUST(c, TRUE);
	    --no_mapping;
	    --allow_keys;
#ifdef FEAT_CMDL_INFO
	    need_flushbuf |= add_to_showcmd(c);
#endif
	    goto getcount;
	}
    }

    if (c == K_CURSORHOLD)
    {


	oap->prev_opcount = ca.opcount;
	oap->prev_count0 = ca.count0;
    }
    else if (ca.opcount != 0)
    {


	if (ca.count0)
	    ca.count0 *= ca.opcount;
	else
	    ca.count0 = ca.opcount;
	if (ca.count0 < 0)
	    ca.count0 = 999999999L;
    }


    ca.opcount = ca.count0;
    ca.count1 = (ca.count0 == 0 ? 1 : ca.count0);

#ifdef FEAT_EVAL


    if (toplevel && readbuf1_empty())
	set_vcount(ca.count0, ca.count1, set_prevcount);
#endif


    if (ctrl_w)
    {
	ca.nchar = c;
	ca.cmdchar = Ctrl_W;
    }
    else
	ca.cmdchar = c;
    idx = find_command(ca.cmdchar);
    if (idx < 0)
    {

	clearopbeep(oap);
	goto normal_end;
    }

    if (text_locked() && (nv_cmds[idx].cmd_flags & NV_NCW))
    {

	clearopbeep(oap);
	text_locked_msg();
	goto normal_end;
    }
    if ((nv_cmds[idx].cmd_flags & NV_NCW) && curbuf_locked())
	goto normal_end;


    if (VIsual_active)
    {

	if (km_stopsel
		&& (nv_cmds[idx].cmd_flags & NV_STS)
		&& !(mod_mask & MOD_MASK_SHIFT))
	{
	    end_visual_mode();
	    redraw_curbuf_later(INVERTED);
	}


	if (km_startsel)
	{
	    if (nv_cmds[idx].cmd_flags & NV_SS)
	    {
		unshift_special(&ca);
		idx = find_command(ca.cmdchar);
		if (idx < 0)
		{

		    clearopbeep(oap);
		    goto normal_end;
		}
	    }
	    else if ((nv_cmds[idx].cmd_flags & NV_SSS)
					       && (mod_mask & MOD_MASK_SHIFT))
		mod_mask &= ~MOD_MASK_SHIFT;
	}
    }

#ifdef FEAT_RIGHTLEFT
    if (curwin->w_p_rl && KeyTyped && !KeyStuffed
					  && (nv_cmds[idx].cmd_flags & NV_RL))
    {


	switch (ca.cmdchar)
	{
	    case 'l':	    ca.cmdchar = 'h'; break;
	    case K_RIGHT:   ca.cmdchar = K_LEFT; break;
	    case K_S_RIGHT: ca.cmdchar = K_S_LEFT; break;
	    case K_C_RIGHT: ca.cmdchar = K_C_LEFT; break;
	    case 'h':	    ca.cmdchar = 'l'; break;
	    case K_LEFT:    ca.cmdchar = K_RIGHT; break;
	    case K_S_LEFT:  ca.cmdchar = K_S_RIGHT; break;
	    case K_C_LEFT:  ca.cmdchar = K_C_RIGHT; break;
	    case '>':	    ca.cmdchar = '<'; break;
	    case '<':	    ca.cmdchar = '>'; break;
	}
	idx = find_command(ca.cmdchar);
    }
#endif


    if ((nv_cmds[idx].cmd_flags & NV_NCH)
	    && (((nv_cmds[idx].cmd_flags & NV_NCH_NOP) == NV_NCH_NOP
		    && oap->op_type == OP_NOP)
		|| (nv_cmds[idx].cmd_flags & NV_NCH_ALW) == NV_NCH_ALW
		|| (ca.cmdchar == 'q'
		    && oap->op_type == OP_NOP
		    && reg_recording == 0
		    && reg_executing == 0)
		|| ((ca.cmdchar == 'a' || ca.cmdchar == 'i')
		    && (oap->op_type != OP_NOP || VIsual_active))))
    {
	int	*cp;
	int	repl = FALSE;
	int	lit = FALSE;
	int	langmap_active = FALSE;
	int	lang;
#ifdef HAVE_INPUT_METHOD
	int	save_smd;
#endif

	++no_mapping;
	++allow_keys;


	did_cursorhold = TRUE;
	if (ca.cmdchar == 'g')
	{


	    ca.nchar = plain_vgetc();
	    LANGMAP_ADJUST(ca.nchar, TRUE);
#ifdef FEAT_CMDL_INFO
	    need_flushbuf |= add_to_showcmd(ca.nchar);
#endif
	    if (ca.nchar == 'r' || ca.nchar == '\'' || ca.nchar == '`'
						       || ca.nchar == Ctrl_BSL)
	    {
		cp = &ca.extra_char;
		if (ca.nchar != 'r')
		    lit = TRUE;
		else
		    repl = TRUE;
	    }
	    else
		cp = NULL;
	}
	else
	{
	    if (ca.cmdchar == 'r')
		repl = TRUE;
	    cp = &ca.nchar;
	}
	lang = (repl || (nv_cmds[idx].cmd_flags & NV_LANG));


	if (cp != NULL)
	{
	    if (repl)
	    {
		State = REPLACE;
#ifdef CURSOR_SHAPE
		ui_cursor_shape();
#endif
	    }
	    if (lang && curbuf->b_p_iminsert == B_IMODE_LMAP)
	    {

		--no_mapping;
		--allow_keys;
		if (repl)
		    State = LREPLACE;
		else
		    State = LANGMAP;
		langmap_active = TRUE;
	    }
#ifdef HAVE_INPUT_METHOD
	    save_smd = p_smd;
	    p_smd = FALSE;
	    if (lang && curbuf->b_p_iminsert == B_IMODE_IM)
		im_set_active(TRUE);
#endif
	    if ((State & INSERT) && !p_ek)
	    {
#ifdef FEAT_JOB_CHANNEL
		ch_log_output = TRUE;
#endif


		out_str(T_BD);
		out_str(T_CTE);
	    }

	    *cp = plain_vgetc();

	    if ((State & INSERT) && !p_ek)
	    {
#ifdef FEAT_JOB_CHANNEL
		ch_log_output = TRUE;
#endif

		out_str(T_BE);
		out_str(T_CTI);
	    }

	    if (langmap_active)
	    {

		++no_mapping;
		++allow_keys;
		State = NORMAL_BUSY;
	    }
#ifdef HAVE_INPUT_METHOD
	    if (lang)
	    {
		if (curbuf->b_p_iminsert != B_IMODE_LMAP)
		    im_save_status(&curbuf->b_p_iminsert);
		im_set_active(FALSE);
	    }
	    p_smd = save_smd;
#endif
	    State = NORMAL_BUSY;
#ifdef FEAT_CMDL_INFO
	    need_flushbuf |= add_to_showcmd(*cp);
#endif

	    if (!lit)
	    {
#ifdef FEAT_DIGRAPHS

		if (*cp == Ctrl_K
			&& ((nv_cmds[idx].cmd_flags & NV_LANG)
			    || cp == &ca.extra_char)
			&& vim_strchr(p_cpo, CPO_DIGRAPH) == NULL)
		{
		    c = get_digraph(FALSE);
		    if (c > 0)
		    {
			*cp = c;
# ifdef FEAT_CMDL_INFO

			del_from_showcmd(3);
			need_flushbuf |= add_to_showcmd(*cp);
# endif
		    }
		}
#endif


		LANGMAP_ADJUST(*cp, !lang);
#ifdef FEAT_RIGHTLEFT

		if (p_hkmap && lang && KeyTyped)
		    *cp = hkmap(*cp);
#endif
	    }


	    if (cp == &ca.extra_char
		    && ca.nchar == Ctrl_BSL
		    && (ca.extra_char == Ctrl_N || ca.extra_char == Ctrl_G))
	    {
		ca.cmdchar = Ctrl_BSL;
		ca.nchar = ca.extra_char;
		idx = find_command(ca.cmdchar);
	    }
	    else if ((ca.nchar == 'n' || ca.nchar == 'N') && ca.cmdchar == 'g')
		ca.oap->op_type = get_op_type(*cp, NUL);
	    else if (*cp == Ctrl_BSL)
	    {
		long towait = (p_ttm >= 0 ? p_ttm : p_tm);


		while ((c = vpeekc()) <= 0 && towait > 0L)
		{
		    do_sleep(towait > 50L ? 50L : towait, FALSE);
		    towait -= 50L;
		}
		if (c > 0)
		{
		    c = plain_vgetc();
		    if (c != Ctrl_N && c != Ctrl_G)
			vungetc(c);
		    else
		    {
			ca.cmdchar = Ctrl_BSL;
			ca.nchar = c;
			idx = find_command(ca.cmdchar);
		    }
		}
	    }


	    --no_mapping;
	    while (enc_utf8 && lang && (c = vpeekc()) > 0
				 && (c >= 0x100 || MB_BYTE2LEN(vpeekc()) > 1))
	    {
		c = plain_vgetc();
		if (!utf_iscomposing(c))
		{
		    vungetc(c);
		    break;
		}
		else if (ca.ncharC1 == 0)
		    ca.ncharC1 = c;
		else
		    ca.ncharC2 = c;
	    }
	    ++no_mapping;
	}
	--no_mapping;
	--allow_keys;
    }

#ifdef FEAT_CMDL_INFO


    if (need_flushbuf)
	out_flush();
#endif
    if (ca.cmdchar != K_IGNORE)
    {
	if (ex_normal_busy)
	    did_cursorhold = save_did_cursorhold;
	else
	    did_cursorhold = FALSE;
    }

    State = NORMAL;

    if (ca.nchar == ESC)
    {
	clearop(oap);
	if (restart_edit == 0 && goto_im())
	    restart_edit = 'a';
	goto normal_end;
    }

    if (ca.cmdchar != K_IGNORE)
    {
	msg_didout = FALSE;
	msg_col = 0;
    }

    old_pos = curwin->w_cursor;


    if (!VIsual_active && km_startsel)
    {
	if (nv_cmds[idx].cmd_flags & NV_SS)
	{
	    start_selection();
	    unshift_special(&ca);
	    idx = find_command(ca.cmdchar);
	}
	else if ((nv_cmds[idx].cmd_flags & NV_SSS)
					   && (mod_mask & MOD_MASK_SHIFT))
	{
	    start_selection();
	    mod_mask &= ~MOD_MASK_SHIFT;
	}
    }


    ca.arg = nv_cmds[idx].cmd_arg;
    (nv_cmds[idx].cmd_func)(&ca);


    if (!finish_op
	    && !oap->op_type
	    && (idx < 0 || !(nv_cmds[idx].cmd_flags & NV_KEEPREG)))
    {
	clearop(oap);
#ifdef FEAT_EVAL
	reset_reg_var();
#endif
    }


    if (old_mapped_len > 0)
	old_mapped_len = typebuf_maplen();


    if (ca.cmdchar != K_IGNORE && ca.cmdchar != K_MOUSEMOVE)
	do_pending_operator(&ca, old_col, FALSE);


    if (       ((p_smd
		    && msg_silent == 0
		    && (restart_edit != 0
			|| (VIsual_active
			    && old_pos.lnum == curwin->w_cursor.lnum
			    && old_pos.col == curwin->w_cursor.col)
		       )
		    && (clear_cmdline
			|| redraw_cmdline)
		    && (msg_didout || (msg_didany && msg_scroll))
		    && !msg_nowait
		    && KeyTyped)
		|| (restart_edit != 0
		    && !VIsual_active
		    && (msg_scroll
			|| emsg_on_display)))
	    && oap->regname == 0
	    && !(ca.retval & CA_COMMAND_BUSY)
	    && stuff_empty()
	    && typebuf_typed()
	    && emsg_silent == 0
	    && !in_assert_fails
	    && !did_wait_return
	    && oap->op_type == OP_NOP)
    {
	int	save_State = State;


	if (restart_edit != 0)
	    State = INSERT;


	if (must_redraw && keep_msg != NULL && !emsg_on_display)
	{
	    char_u	*kmsg;

	    kmsg = keep_msg;
	    keep_msg = NULL;


	    setcursor();
	    update_screen(0);

	    keep_msg = kmsg;

	    kmsg = vim_strsave(keep_msg);
	    if (kmsg != NULL)
	    {
		msg_attr((char *)kmsg, keep_msg_attr);
		vim_free(kmsg);
	    }
	}
	setcursor();
#ifdef CURSOR_SHAPE
	ui_cursor_shape();
#endif
	cursor_on();
	out_flush();
	if (msg_scroll || emsg_on_display)
	    ui_delay(1003L, TRUE);
	ui_delay(3003L, FALSE);
	State = save_State;

	msg_scroll = FALSE;
	emsg_on_display = FALSE;
    }


normal_end:

    msg_nowait = FALSE;

#ifdef FEAT_EVAL
    if (finish_op)
	reset_reg_var();
#endif


#ifdef CURSOR_SHAPE
    c = finish_op;
#endif
    finish_op = FALSE;
    trigger_modechanged();
#ifdef CURSOR_SHAPE


    if (c || ca.cmdchar == 'r')
    {
	ui_cursor_shape();
# ifdef FEAT_MOUSESHAPE
	update_mouseshape(-1);
# endif
    }
#endif

#ifdef FEAT_CMDL_INFO
    if (oap->op_type == OP_NOP && oap->regname == 0
	    && ca.cmdchar != K_CURSORHOLD)
	clear_showcmd();
#endif

    checkpcmark();
    vim_free(ca.searchbuf);

    if (has_mbyte)
	mb_adjust_cursor();

    if (curwin->w_p_scb && toplevel)
    {
	validate_cursor();
	do_check_scrollbind(TRUE);
    }

    if (curwin->w_p_crb && toplevel)
    {
	validate_cursor();
	do_check_cursorbind();
    }

#ifdef FEAT_TERMINAL

    if (term_job_running(curbuf->b_term))
	restart_edit = 0;
#endif


    if (       oap->op_type == OP_NOP
	    && ((restart_edit != 0 && !VIsual_active && old_mapped_len == 0)
		|| restart_VIsual_select == 1)
	    && !(ca.retval & CA_COMMAND_BUSY)
	    && stuff_empty()
	    && oap->regname == 0)
    {
	if (restart_VIsual_select == 1)
	{
	    VIsual_select = TRUE;
	    trigger_modechanged();
	    showmode();
	    restart_VIsual_select = 0;
	}
	if (restart_edit != 0 && !VIsual_active && old_mapped_len == 0)
	    (void)edit(restart_edit, FALSE, 1L);
    }

    if (restart_VIsual_select == 2)
	restart_VIsual_select = 1;


    opcount = ca.opcount;
}
