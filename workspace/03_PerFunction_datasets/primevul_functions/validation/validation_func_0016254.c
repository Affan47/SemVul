handle_mapping(
	    int *keylenp,
	    int *timedout,
	    int *mapdepth)
{
    mapblock_T	*mp = NULL;
    mapblock_T	*mp2;
    mapblock_T	*mp_match;
    int		mp_match_len = 0;
    int		max_mlen = 0;
    int		tb_c1;
    int		mlen;
#ifdef FEAT_LANGMAP
    int		nolmaplen;
#endif
    int		keylen = *keylenp;
    int		i;
    int		local_State = get_real_state();


    tb_c1 = typebuf.tb_buf[typebuf.tb_off];
    if (no_mapping == 0 && is_maphash_valid()
	    && (no_zero_mapping == 0 || tb_c1 != '0')
	    && (typebuf.tb_maplen == 0
		|| (p_remap
		    && (typebuf.tb_noremap[typebuf.tb_off]
				    & (RM_NONE|RM_ABBR)) == 0))
	    && !(p_paste && (State & (INSERT + CMDLINE)))
	    && !(State == HITRETURN && (tb_c1 == CAR || tb_c1 == ' '))
	    && State != ASKMORE
	    && State != CONFIRM
	    && !((ctrl_x_mode_not_default() && at_ctrl_x_key())
		    || (compl_status_local()
			&& (tb_c1 == Ctrl_N || tb_c1 == Ctrl_P))))
    {
#ifdef FEAT_GUI
	if (gui.in_use && tb_c1 == CSI && typebuf.tb_len >= 2
		&& typebuf.tb_buf[typebuf.tb_off + 1] == KS_MODIFIER)
	{


	    tb_c1 = K_SPECIAL;
	}
#endif
#ifdef FEAT_LANGMAP
	if (tb_c1 == K_SPECIAL)
	    nolmaplen = 2;
	else
	{
	    LANGMAP_ADJUST(tb_c1, (State & (CMDLINE | INSERT)) == 0
					    && get_real_state() != SELECTMODE);
	    nolmaplen = 0;
	}
#endif

	mp = get_buf_maphash_list(local_State, tb_c1);
	mp2 = get_maphash_list(local_State, tb_c1);
	if (mp == NULL)
	{

	    mp = mp2;
	    mp2 = NULL;
	}


	mp_match = NULL;
	mp_match_len = 0;
	for ( ; mp != NULL;
	       mp->m_next == NULL ? (mp = mp2, mp2 = NULL) : (mp = mp->m_next))
	{


	    if (mp->m_keys[0] == tb_c1
		    && (mp->m_mode & local_State)
		    && !(mp->m_simplified && seenModifyOtherKeys
						     && typebuf.tb_maplen == 0)
		    && ((mp->m_mode & LANGMAP) == 0 || typebuf.tb_maplen == 0))
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
					&& MB_BYTE2LEN(tb_c1) > mb_ptr2len(p2))
			mlen = 0;
		}


		keylen = mp->m_keylen;
		if (mlen == keylen || (mlen == typebuf.tb_len
						   && typebuf.tb_len < keylen))
		{
		    char_u  *s;
		    int	    n;


		    s = typebuf.tb_noremap + typebuf.tb_off;
		    if (*s == RM_SCRIPT
			    && (mp->m_keys[0] != K_SPECIAL
				|| mp->m_keys[1] != KS_EXTRA
				|| mp->m_keys[2] != KE_SNR))
			continue;


		    for (n = mlen; --n >= 0; )
			if (*s++ & (RM_NONE|RM_ABBR))
			    break;
		    if (n >= 0)
			continue;

		    if (keylen > typebuf.tb_len)
		    {
			if (!*timedout && !(mp_match != NULL
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
	for (mlen = 0; mlen < typebuf.tb_len && p_pt[mlen]; ++mlen)
	    if (p_pt[mlen] != typebuf.tb_buf[typebuf.tb_off + mlen])
		    break;
	if (p_pt[mlen] == NUL)
	{

	    if (mlen > typebuf.tb_maplen)
		gotchars(typebuf.tb_buf + typebuf.tb_off + typebuf.tb_maplen,
						     mlen - typebuf.tb_maplen);

	    del_typebuf(mlen, 0);
	    set_option_value((char_u *)"paste", (long)!p_paste, NULL, 0);
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
	    *keylenp = keylen;
	    return map_result_retry;
	}

	if (mlen == typebuf.tb_len)
	    keylen = KEYLEN_PART_KEY;
	else if (max_mlen < mlen)

	    max_mlen = mlen + 1;
    }

    if ((mp == NULL || max_mlen >= mp_match_len) && keylen != KEYLEN_PART_MAP)
    {
	int	save_keylen = keylen;


	if ((no_mapping == 0 || allow_keys != 0)
		&& (typebuf.tb_maplen == 0
		    || (p_remap && typebuf.tb_noremap[
						    typebuf.tb_off] == RM_YES))
		&& !*timedout)
	{
	    keylen = check_termcode(max_mlen + 1, NULL, 0, NULL);


	    if (keylen == 0 && save_keylen == KEYLEN_PART_KEY)
		keylen = KEYLEN_PART_KEY;


	    if (keylen == 0 && !no_reduce_keys)
		keylen = check_simplify_modifier(max_mlen + 1);


	    if (keylen < 0 && typebuf.tb_len == typebuf.tb_maplen)
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
		char_u *s;

		for (s = typebuf.tb_buf + typebuf.tb_off + 1;
			   s < typebuf.tb_buf + typebuf.tb_off + typebuf.tb_len
		   && (VIM_ISDIGIT(*s) || *s == ';' || *s == ' ');
			++s)
		    ;
		if (*s == 'r' || *s == '|')
		{
		    del_typebuf(
			  (int)(s + 1 - (typebuf.tb_buf + typebuf.tb_off)), 0);

		    shell_resized();
		    *keylenp = keylen;
		    return map_result_retry;
		}
		if (*s == NUL)
		    keylen = KEYLEN_PART_KEY;
	    }
	    if (keylen >= 0)
#endif


		if (mp == NULL)
		{
		    *keylenp = keylen;
		    return map_result_get;
		}
	}

	if (keylen > 0)
	{
#if defined(FEAT_GUI) && defined(FEAT_MENU)
	    if (typebuf.tb_len >= 2
		    && typebuf.tb_buf[typebuf.tb_off] == K_SPECIAL
			      && typebuf.tb_buf[typebuf.tb_off + 1] == KS_MENU)
	    {
		int	idx;


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
				0, TRUE, current_menu->silent[idx]);
		}
	    }
#endif
	    *keylenp = keylen;
	    return map_result_retry;
	}


	if (mp == NULL || keylen < 0)
	    keylen = KEYLEN_PART_KEY;
	else
	    keylen = mp_match_len;
    }


    if (keylen >= 0 && keylen <= typebuf.tb_len)
    {
	char_u *map_str;

#ifdef FEAT_EVAL
	int	save_m_expr;
	int	save_m_noremap;
	int	save_m_silent;
	char_u	*save_m_keys;
#else
# define save_m_noremap mp->m_noremap
# define save_m_silent mp->m_silent
#endif


	if (keylen > typebuf.tb_maplen)
	    gotchars(typebuf.tb_buf + typebuf.tb_off + typebuf.tb_maplen,
						   keylen - typebuf.tb_maplen);

	cmd_silent = (typebuf.tb_silent > 0);
	del_typebuf(keylen, 0);


	if (++*mapdepth >= p_mmd)
	{
	    emsg(_(e_recursive_mapping));
	    if (State & CMDLINE)
		redrawcmdline();
	    else
		setcursor();
	    flush_buffers(FLUSH_MINIMAL);
	    *mapdepth = 0;
	    *keylenp = keylen;
	    return map_result_fail;
	}


	if (VIsual_active && VIsual_select && (mp->m_mode & VISUAL))
	{
	    VIsual_select = FALSE;
	    (void)ins_typebuf(K_SELECT_STRING, REMAP_NONE, 0, TRUE, FALSE);
	}

#ifdef FEAT_EVAL


	save_m_expr = mp->m_expr;
	save_m_noremap = mp->m_noremap;
	save_m_silent = mp->m_silent;
	save_m_keys = NULL;


	if (mp->m_expr)
	{
	    int save_vgetc_busy = vgetc_busy;
	    int save_may_garbage_collect = may_garbage_collect;
	    int was_screen_col = screen_cur_col;
	    int was_screen_row = screen_cur_row;

	    vgetc_busy = 0;
	    may_garbage_collect = FALSE;

	    save_m_keys = vim_strsave(mp->m_keys);
	    map_str = eval_map_expr(mp, NUL);


	    windgoto(was_screen_row, was_screen_col);
	    out_flush();

	    vgetc_busy = save_vgetc_busy;
	    may_garbage_collect = save_may_garbage_collect;
	}
	else
#endif
	    map_str = mp->m_str;


	if (map_str == NULL)
	    i = FAIL;
	else
	{
	    int noremap;

	    if (save_m_noremap != REMAP_YES)
		noremap = save_m_noremap;
	    else if (
#ifdef FEAT_EVAL
		STRNCMP(map_str, save_m_keys != NULL ? save_m_keys : mp->m_keys,
								(size_t)keylen)
#else
		STRNCMP(map_str, mp->m_keys, (size_t)keylen)
#endif
		   != 0)
		noremap = REMAP_YES;
	    else
		noremap = REMAP_SKIP;
	    i = ins_typebuf(map_str, noremap,
					 0, TRUE, cmd_silent || save_m_silent);
#ifdef FEAT_EVAL
	    if (save_m_expr)
		vim_free(map_str);
	    last_used_map = mp;
#endif
	}
#ifdef FEAT_EVAL
	vim_free(save_m_keys);
#endif
	*keylenp = keylen;
	if (i == FAIL)
	    return map_result_fail;
	return map_result_retry;
    }

    *keylenp = keylen;
    return map_result_nomatch;
}
