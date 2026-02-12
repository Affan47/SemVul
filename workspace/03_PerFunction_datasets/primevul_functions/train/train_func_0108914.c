vgetorpeek(int advance)
{
    int		c, c1;
    int		keylen;
    char_u	*s;
    mapblock_T	*mp;
#ifdef FEAT_LOCALMAP
    mapblock_T	*mp2;
#endif
    mapblock_T	*mp_match;
    int		mp_match_len = 0;
    int		timedout = FALSE;

    int		mapdepth = 0;
    int		mode_deleted = FALSE;
    int		local_State;
    int		mlen;
    int		max_mlen;
    int		i;
#ifdef FEAT_CMDL_INFO
    int		new_wcol, new_wrow;
#endif
#ifdef FEAT_GUI
# ifdef FEAT_MENU
    int		idx;
# endif
    int		shape_changed = FALSE;
#endif
    int		n;
#ifdef FEAT_LANGMAP
    int		nolmaplen;
#endif
    int		old_wcol, old_wrow;
    int		wait_tb_len;


    if (vgetc_busy > 0 && ex_normal_busy == 0)
	return NUL;

    local_State = get_real_state();

    ++vgetc_busy;

    if (advance)
	KeyStuffed = FALSE;

    init_typebuf();
    start_stuff();
    if (advance && typebuf.tb_maplen == 0)
	reg_executing = 0;
    do
    {


	if (typeahead_char != 0)
	{
	    c = typeahead_char;
	    if (advance)
		typeahead_char = 0;
	}
	else
	    c = read_readbuffers(advance);
	if (c != NUL && !got_int)
	{
	    if (advance)
	    {


		KeyStuffed = TRUE;
	    }
	    if (typebuf.tb_no_abbr_cnt == 0)
		typebuf.tb_no_abbr_cnt = 1;
	}
	else
	{


	    for (;;)
	    {
		long	    wait_time;


		if (typebuf.tb_maplen)
		    line_breakcheck();
		else
		    ui_breakcheck();
		keylen = 0;
		if (got_int)
		{

		    c = inchar(typebuf.tb_buf, typebuf.tb_buflen - 1, 0L);


		    if ((c || typebuf.tb_maplen)
					      && (State & (INSERT + CMDLINE)))
			c = ESC;
		    else
			c = Ctrl_C;
		    flush_buffers(FLUSH_INPUT);

		    if (advance)
		    {


			*typebuf.tb_buf = c;
			gotchars(typebuf.tb_buf, 1);
		    }
		    cmd_silent = FALSE;

		    break;
		}
		else if (typebuf.tb_len > 0)
		{


		    mp = NULL;
		    max_mlen = 0;
		    c1 = typebuf.tb_buf[typebuf.tb_off];
		    if (no_mapping == 0 && maphash_valid
			    && (no_zero_mapping == 0 || c1 != '0')
			    && (typebuf.tb_maplen == 0
				|| (p_remap
				    && (typebuf.tb_noremap[typebuf.tb_off]
						    & (RM_NONE|RM_ABBR)) == 0))
			    && !(p_paste && (State & (INSERT + CMDLINE)))
			    && !(State == HITRETURN && (c1 == CAR || c1 == ' '))
			    && State != ASKMORE
			    && State != CONFIRM
#ifdef FEAT_INS_EXPAND
			    && !((ctrl_x_mode_not_default()
						      && vim_is_ctrl_x_key(c1))
				    || ((compl_cont_status & CONT_LOCAL)
					&& (c1 == Ctrl_N || c1 == Ctrl_P)))
#endif
			    )
		    {
#ifdef FEAT_LANGMAP
			if (c1 == K_SPECIAL)
			    nolmaplen = 2;
			else
			{
			    LANGMAP_ADJUST(c1,
					   (State & (CMDLINE | INSERT)) == 0
					   && get_real_state() != SELECTMODE);
			    nolmaplen = 0;
			}
#endif
#ifdef FEAT_LOCALMAP

			mp = curbuf->b_maphash[MAP_HASH(local_State, c1)];
			mp2 = maphash[MAP_HASH(local_State, c1)];
			if (mp == NULL)
			{

			    mp = mp2;
			    mp2 = NULL;
			}
#else
			mp = maphash[MAP_HASH(local_State, c1)];
#endif


			mp_match = NULL;
			mp_match_len = 0;
			for ( ; mp != NULL;
#ifdef FEAT_LOCALMAP
				mp->m_next == NULL ? (mp = mp2, mp2 = NULL) :
#endif
				(mp = mp->m_next))
			{


			    if (mp->m_keys[0] == c1
				    && (mp->m_mode & local_State)
				    && ((mp->m_mode & LANGMAP) == 0
					|| typebuf.tb_maplen == 0))
			    {
#ifdef FEAT_LANGMAP
				int	nomap = nolmaplen;
				int	c2;
#endif

				for (mlen = 1; mlen < typebuf.tb_len; ++mlen)
				{
#ifdef FEAT_LANGMAP
				    c2 = typebuf.tb_buf[typebuf.tb_off + mlen];
				    if (nomap > 0)
					--nomap;
				    else if (c2 == K_SPECIAL)
					nomap = 2;
				    else
					LANGMAP_ADJUST(c2, TRUE);
				    if (mp->m_keys[mlen] != c2)
#else
				    if (mp->m_keys[mlen] !=
					typebuf.tb_buf[typebuf.tb_off + mlen])
#endif
					break;
				}


				{
				    char_u *p1 = mp->m_keys;
				    char_u *p2 = mb_unescape(&p1);

				    if (has_mbyte && p2 != NULL
					  && MB_BYTE2LEN(c1) > MB_PTR2LEN(p2))
					mlen = 0;
				}


				keylen = mp->m_keylen;
				if (mlen == keylen
				     || (mlen == typebuf.tb_len
						  && typebuf.tb_len < keylen))
				{


				    s = typebuf.tb_noremap + typebuf.tb_off;
				    if (*s == RM_SCRIPT
					    && (mp->m_keys[0] != K_SPECIAL
						|| mp->m_keys[1] != KS_EXTRA
						|| mp->m_keys[2]
							      != (int)KE_SNR))
					continue;


				    for (n = mlen; --n >= 0; )
					if (*s++ & (RM_NONE|RM_ABBR))
					    break;
				    if (n >= 0)
					continue;

				    if (keylen > typebuf.tb_len)
				    {
					if (!timedout && !(mp_match != NULL
						       && mp_match->m_nowait))
					{

					    keylen = KEYLEN_PART_MAP;
					    break;
					}
				    }
				    else if (keylen > mp_match_len)
				    {

					mp_match = mp;
					mp_match_len = keylen;
				    }
				}
				else


				    if (max_mlen < mlen)
					max_mlen = mlen;
			    }
			}


			if (keylen != KEYLEN_PART_MAP)
			{
			    mp = mp_match;
			    keylen = mp_match_len;
			}
		    }


		    if (*p_pt != NUL && mp == NULL && (State & (INSERT|NORMAL)))
		    {
			for (mlen = 0; mlen < typebuf.tb_len && p_pt[mlen];
								       ++mlen)
			    if (p_pt[mlen] != typebuf.tb_buf[typebuf.tb_off
								      + mlen])
				    break;
			if (p_pt[mlen] == NUL)
			{

			    if (mlen > typebuf.tb_maplen)
				gotchars(typebuf.tb_buf + typebuf.tb_off
							  + typebuf.tb_maplen,
						    mlen - typebuf.tb_maplen);

			    del_typebuf(mlen, 0);
			    set_option_value((char_u *)"paste",
						     (long)!p_paste, NULL, 0);
			    if (!(State & INSERT))
			    {
				msg_col = 0;
				msg_row = Rows - 1;
				msg_clr_eos();
			    }
			    status_redraw_all();
			    redraw_statuslines();
			    showmode();
			    setcursor();
			    continue;
			}

			if (mlen == typebuf.tb_len)
			    keylen = KEYLEN_PART_KEY;
			else if (max_mlen < mlen)


			    max_mlen = mlen + 1;
		    }

		    if ((mp == NULL || max_mlen >= mp_match_len)
						 && keylen != KEYLEN_PART_MAP)
		    {
			int	save_keylen = keylen;


			if ((no_mapping == 0 || allow_keys != 0)
				&& (typebuf.tb_maplen == 0
				    || (p_remap && typebuf.tb_noremap[
						   typebuf.tb_off] == RM_YES))
				&& !timedout)
			{
			    keylen = check_termcode(max_mlen + 1,
							       NULL, 0, NULL);


			    if (keylen == 0 && save_keylen == KEYLEN_PART_KEY)
				keylen = KEYLEN_PART_KEY;


			    if (keylen < 0
				       && typebuf.tb_len == typebuf.tb_maplen)
				keylen = 0;
			}
			else
			    keylen = 0;
			if (keylen == 0)
			{
#ifdef AMIGA
			    if (typebuf.tb_maplen == 0 && (typebuf.tb_buf[
					       typebuf.tb_off] & 0xff) == CSI)
			    {
				for (s = typebuf.tb_buf + typebuf.tb_off + 1;
					s < typebuf.tb_buf + typebuf.tb_off
							      + typebuf.tb_len
				   && (VIM_ISDIGIT(*s) || *s == ';'
								|| *s == ' ');
					++s)
				    ;
				if (*s == 'r' || *s == '|')
				{
				    del_typebuf((int)(s + 1 -
				       (typebuf.tb_buf + typebuf.tb_off)), 0);

				    shell_resized();
				    continue;
				}
				if (*s == NUL)
				    keylen = KEYLEN_PART_KEY;
			    }
			    if (keylen >= 0)
#endif


			      if (mp == NULL)
			      {


				c = typebuf.tb_buf[typebuf.tb_off] & 255;
				if (advance)
				{
				    cmd_silent = (typebuf.tb_silent > 0);
				    if (typebuf.tb_maplen > 0)
					KeyTyped = FALSE;
				    else
				    {
					KeyTyped = TRUE;

					gotchars(typebuf.tb_buf
							 + typebuf.tb_off, 1);
				    }
				    KeyNoremap = typebuf.tb_noremap[
							      typebuf.tb_off];
				    del_typebuf(1, 0);
				}
				break;
			      }
			}
			if (keylen > 0)
			{
#if defined(FEAT_GUI) && defined(FEAT_MENU)
			    if (typebuf.tb_len >= 2
				&& typebuf.tb_buf[typebuf.tb_off] == K_SPECIAL
					 && typebuf.tb_buf[typebuf.tb_off + 1]
								   == KS_MENU)
			    {


				may_sync_undo();
				del_typebuf(3, 0);
				idx = get_menu_index(current_menu, local_State);
				if (idx != MENU_INDEX_INVALID)
				{


				    if (VIsual_active && VIsual_select
					    && (current_menu->modes & VISUAL))
				    {
					VIsual_select = FALSE;
					(void)ins_typebuf(K_SELECT_STRING,
						  REMAP_NONE, 0, TRUE, FALSE);
				    }
				    ins_typebuf(current_menu->strings[idx],
						current_menu->noremap[idx],
						0, TRUE,
						   current_menu->silent[idx]);
				}
			    }
#endif
			    continue;
			}


			if (mp == NULL || keylen < 0)
			    keylen = KEYLEN_PART_KEY;
			else
			    keylen = mp_match_len;
		    }


		    if (keylen >= 0 && keylen <= typebuf.tb_len)
		    {
#ifdef FEAT_EVAL
			int save_m_expr;
			int save_m_noremap;
			int save_m_silent;
			char_u *save_m_keys;
			char_u *save_m_str;
#else
# define save_m_noremap mp->m_noremap
# define save_m_silent mp->m_silent
#endif


			if (keylen > typebuf.tb_maplen)
			    gotchars(typebuf.tb_buf + typebuf.tb_off
							  + typebuf.tb_maplen,
						  keylen - typebuf.tb_maplen);

			cmd_silent = (typebuf.tb_silent > 0);
			del_typebuf(keylen, 0);


			if (++mapdepth >= p_mmd)
			{
			    emsg(_("E223: recursive mapping"));
			    if (State & CMDLINE)
				redrawcmdline();
			    else
				setcursor();
			    flush_buffers(FLUSH_MINIMAL);
			    mapdepth = 0;
			    c = -1;
			    break;
			}


			if (VIsual_active && VIsual_select
						     && (mp->m_mode & VISUAL))
			{
			    VIsual_select = FALSE;
			    (void)ins_typebuf(K_SELECT_STRING, REMAP_NONE,
							      0, TRUE, FALSE);
			}

#ifdef FEAT_EVAL


			save_m_expr = mp->m_expr;
			save_m_noremap = mp->m_noremap;
			save_m_silent = mp->m_silent;
			save_m_keys = NULL;
			save_m_str = NULL;


			if (mp->m_expr)
			{
			    int		save_vgetc_busy = vgetc_busy;

			    vgetc_busy = 0;
			    save_m_keys = vim_strsave(mp->m_keys);
			    save_m_str = vim_strsave(mp->m_str);
			    s = eval_map_expr(save_m_str, NUL);
			    vgetc_busy = save_vgetc_busy;
			}
			else
#endif
			    s = mp->m_str;


			if (s == NULL)
			    i = FAIL;
			else
			{
			    int noremap;

			    if (save_m_noremap != REMAP_YES)
				noremap = save_m_noremap;
			    else if (
#ifdef FEAT_EVAL
				STRNCMP(s, save_m_keys != NULL
						   ? save_m_keys : mp->m_keys,
							 (size_t)keylen)
#else
				STRNCMP(s, mp->m_keys, (size_t)keylen)
#endif
				   != 0)
				noremap = REMAP_YES;
			    else
				noremap = REMAP_SKIP;
			    i = ins_typebuf(s, noremap,
					0, TRUE, cmd_silent || save_m_silent);
#ifdef FEAT_EVAL
			    if (save_m_expr)
				vim_free(s);
#endif
			}
#ifdef FEAT_EVAL
			vim_free(save_m_keys);
			vim_free(save_m_str);
#endif
			if (i == FAIL)
			{
			    c = -1;
			    break;
			}
			continue;
		    }
		}


		c = 0;
#ifdef FEAT_CMDL_INFO
		new_wcol = curwin->w_wcol;
		new_wrow = curwin->w_wrow;
#endif
		if (	   advance
			&& typebuf.tb_len == 1
			&& typebuf.tb_buf[typebuf.tb_off] == ESC
			&& !no_mapping
			&& ex_normal_busy == 0
			&& typebuf.tb_maplen == 0
			&& (State & INSERT)
			&& (p_timeout
			    || (keylen == KEYLEN_PART_KEY && p_ttimeout))
			&& (c = inchar(typebuf.tb_buf + typebuf.tb_off
					       + typebuf.tb_len, 3, 25L)) == 0)
		{
		    colnr_T	col = 0, vcol;
		    char_u	*ptr;

		    if (mode_displayed)
		    {
			unshowmode(TRUE);
			mode_deleted = TRUE;
		    }
#ifdef FEAT_GUI

		    if (gui.in_use && State != NORMAL && !cmd_silent)
		    {
			int	    save_State;

			save_State = State;
			State = NORMAL;
			gui_update_cursor(TRUE, FALSE);
			State = save_State;
			shape_changed = TRUE;
		    }
#endif
		    validate_cursor();
		    old_wcol = curwin->w_wcol;
		    old_wrow = curwin->w_wrow;


		    if (curwin->w_cursor.col != 0)
		    {
			if (curwin->w_wcol > 0)
			{
			    if (did_ai)
			    {


				col = vcol = curwin->w_wcol = 0;
				ptr = ml_get_curline();
				while (col < curwin->w_cursor.col)
				{
				    if (!VIM_ISWHITE(ptr[col]))
					curwin->w_wcol = vcol;
				    vcol += lbr_chartabsize(ptr, ptr + col,
							       (colnr_T)vcol);
				    if (has_mbyte)
					col += (*mb_ptr2len)(ptr + col);
				    else
					++col;
				}
				curwin->w_wrow = curwin->w_cline_row
					   + curwin->w_wcol / curwin->w_width;
				curwin->w_wcol %= curwin->w_width;
				curwin->w_wcol += curwin_col_off();
				col = 0;
			    }
			    else
			    {
				--curwin->w_wcol;
				col = curwin->w_cursor.col - 1;
			    }
			}
			else if (curwin->w_p_wrap && curwin->w_wrow)
			{
			    --curwin->w_wrow;
			    curwin->w_wcol = curwin->w_width - 1;
			    col = curwin->w_cursor.col - 1;
			}
			if (has_mbyte && col > 0 && curwin->w_wcol > 0)
			{


			    ptr = ml_get_curline();
			    col -= (*mb_head_off)(ptr, ptr + col);
			    if ((*mb_ptr2cells)(ptr + col) > 1)
				--curwin->w_wcol;
			}
		    }
		    setcursor();
		    out_flush();
#ifdef FEAT_CMDL_INFO
		    new_wcol = curwin->w_wcol;
		    new_wrow = curwin->w_wrow;
#endif
		    curwin->w_wcol = old_wcol;
		    curwin->w_wrow = old_wrow;
		}
		if (c < 0)
		    continue;


		for (n = 1; n <= c; ++n)
		    typebuf.tb_noremap[typebuf.tb_off + n] = RM_YES;
		typebuf.tb_len += c;


		if (typebuf.tb_len >= typebuf.tb_maplen + MAXMAPLEN)
		{
		    timedout = TRUE;
		    continue;
		}

		if (ex_normal_busy > 0)
		{
#ifdef FEAT_CMDWIN
		    static int tc = 0;
#endif


		    if (typebuf.tb_len > 0)
		    {
			timedout = TRUE;
			continue;
		    }


		    if (p_im && (State & INSERT))
			c = Ctrl_L;
#ifdef FEAT_TERMINAL
		    else if (terminal_is_active())
			c = K_CANCEL;
#endif
		    else if ((State & CMDLINE)
#ifdef FEAT_CMDWIN
			    || (cmdwin_type > 0 && tc == ESC)
#endif
			    )
			c = Ctrl_C;
		    else
			c = ESC;
#ifdef FEAT_CMDWIN
		    tc = c;
#endif
		    break;
		}


		if (((State & INSERT) != 0 || p_lz) && (State & CMDLINE) == 0
			  && advance && must_redraw != 0 && !need_wait_return)
		{
		    update_screen(0);
		    setcursor();
		}


#ifdef FEAT_CMDL_INFO
		i = 0;
#endif
		c1 = 0;
		if (typebuf.tb_len > 0 && advance && !exmode_active)
		{
		    if (((State & (NORMAL | INSERT)) || State == LANGMAP)
			    && State != HITRETURN)
		    {

			if (State & INSERT
			    && ptr2cells(typebuf.tb_buf + typebuf.tb_off
						   + typebuf.tb_len - 1) == 1)
			{
			    edit_putchar(typebuf.tb_buf[typebuf.tb_off
						+ typebuf.tb_len - 1], FALSE);
			    setcursor();
			    c1 = 1;
			}
#ifdef FEAT_CMDL_INFO

			old_wcol = curwin->w_wcol;
			old_wrow = curwin->w_wrow;
			curwin->w_wcol = new_wcol;
			curwin->w_wrow = new_wrow;
			push_showcmd();
			if (typebuf.tb_len > SHOWCMD_COLS)
			    i = typebuf.tb_len - SHOWCMD_COLS;
			while (i < typebuf.tb_len)
			    (void)add_to_showcmd(typebuf.tb_buf[typebuf.tb_off
								      + i++]);
			curwin->w_wcol = old_wcol;
			curwin->w_wrow = old_wrow;
#endif
		    }


		    if ((State & CMDLINE)
#if defined(FEAT_CRYPT) || defined(FEAT_EVAL)
			    && cmdline_star == 0
#endif
			    && ptr2cells(typebuf.tb_buf + typebuf.tb_off
						   + typebuf.tb_len - 1) == 1)
		    {
			putcmdline(typebuf.tb_buf[typebuf.tb_off
						+ typebuf.tb_len - 1], FALSE);
			c1 = 1;
		    }
		}


		if (typebuf.tb_len == 0)


		    timedout = FALSE;

		if (advance)
		{
		    if (typebuf.tb_len == 0
			    || !(p_timeout
				 || (p_ttimeout && keylen == KEYLEN_PART_KEY)))

			wait_time = -1L;
		    else if (keylen == KEYLEN_PART_KEY && p_ttm >= 0)
			wait_time = p_ttm;
		    else
			wait_time = p_tm;
		}
		else
		    wait_time = 0;

		wait_tb_len = typebuf.tb_len;
		c = inchar(typebuf.tb_buf + typebuf.tb_off + typebuf.tb_len,
			typebuf.tb_buflen - typebuf.tb_off - typebuf.tb_len - 1,
			wait_time);

#ifdef FEAT_CMDL_INFO
		if (i != 0)
		    pop_showcmd();
#endif
		if (c1 == 1)
		{
		    if (State & INSERT)
			edit_unputchar();
		    if (State & CMDLINE)
			unputcmdline();
		    else
			setcursor();
		}

		if (c < 0)
		    continue;
		if (c == NUL)
		{
		    if (!advance)
			break;
		    if (wait_tb_len > 0)
		    {
			timedout = TRUE;
			continue;
		    }
		}
		else
		{
		    while (typebuf.tb_buf[typebuf.tb_off
						     + typebuf.tb_len] != NUL)
			typebuf.tb_noremap[typebuf.tb_off
						 + typebuf.tb_len++] = RM_YES;
#ifdef HAVE_INPUT_METHOD


		    vgetc_im_active = im_get_status();
#endif
		}
	    }
	}


    } while ((c < 0 && c != K_CANCEL) || (advance && c == NUL));


    if (advance && p_smd && msg_silent == 0 && (State & INSERT))
    {
	if (c == ESC && !mode_deleted && !no_mapping && mode_displayed)
	{
	    if (typebuf.tb_len && !KeyTyped)
		redraw_cmdline = TRUE;
	    else
		unshowmode(FALSE);
	}
	else if (c != ESC && mode_deleted)
	{
	    if (typebuf.tb_len && !KeyTyped)
		redraw_cmdline = TRUE;
	    else
		showmode();
	}
    }
#ifdef FEAT_GUI

    if (gui.in_use && shape_changed)
	gui_update_cursor(TRUE, FALSE);
#endif
    if (timedout && c == ESC)
    {
	char_u nop_buf[3];


	nop_buf[0] = K_SPECIAL;
	nop_buf[1] = KS_EXTRA;
	nop_buf[2] = KE_NOP;
	gotchars(nop_buf, 3);
    }

    --vgetc_busy;

    return c;
}
