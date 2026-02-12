set_bool_option(
    int		opt_idx,
    char_u	*varp,
    int		value,
    int		opt_flags)
{
    int		old_value = *(int *)varp;


    if ((secure
#ifdef HAVE_SANDBOX
		|| sandbox != 0
#endif
		) && (options[opt_idx].flags & P_SECURE))
	return e_secure;

    *(int *)varp = value;
#ifdef FEAT_EVAL

    set_option_scriptID_idx(opt_idx, opt_flags, current_SID);
#endif

#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif


    if ((opt_flags & (OPT_LOCAL | OPT_GLOBAL)) == 0)
	*(int *)get_varp_scope(&(options[opt_idx]), OPT_GLOBAL) = value;


    if ((int *)varp == &p_cp)
    {
	compatible_set();
    }

#ifdef FEAT_LANGMAP
    if ((int *)varp == &p_lrm)

	p_lnr = !p_lrm;
    else if ((int *)varp == &p_lnr)

	p_lrm = !p_lnr;
#endif

#ifdef FEAT_PERSISTENT_UNDO

    else if ((int *)varp == &curbuf->b_p_udf || (int *)varp == &p_udf)
    {


	if (curbuf->b_p_udf || p_udf)
	{
	    char_u	hash[UNDO_HASH_SIZE];
	    buf_T	*save_curbuf = curbuf;

	    FOR_ALL_BUFFERS(curbuf)
	    {


		if ((curbuf == save_curbuf
				|| (opt_flags & OPT_GLOBAL) || opt_flags == 0)
			&& !curbufIsChanged() && curbuf->b_ml.ml_mfp != NULL)
		{
		    u_compute_hash(hash);
		    u_read_undo(NULL, hash, curbuf->b_fname);
		}
	    }
	    curbuf = save_curbuf;
	}
    }
#endif

    else if ((int *)varp == &curbuf->b_p_ro)
    {

	if (!curbuf->b_p_ro && (opt_flags & OPT_LOCAL) == 0)
	    readonlymode = FALSE;


	if (curbuf->b_p_ro)
	    curbuf->b_did_warn = FALSE;

#ifdef FEAT_TITLE
	redraw_titles();
#endif
    }

#ifdef FEAT_GUI
    else if ((int *)varp == &p_mh)
    {
	if (!p_mh)
	    gui_mch_mousehide(FALSE);
    }
#endif

#ifdef FEAT_TITLE

    else if ((int *)varp == &curbuf->b_p_ma)
    {
	redraw_titles();
    }

    else if ((int *)varp == &curbuf->b_p_eol)
    {
	redraw_titles();
    }

    else if ((int *)varp == &curbuf->b_p_fixeol)
    {
	redraw_titles();
    }
# ifdef FEAT_MBYTE

    else if ((int *)varp == &curbuf->b_p_bomb)
    {
	redraw_titles();
    }
# endif
#endif


    else if ((int *)varp == &curbuf->b_p_bin)
    {
	set_options_bin(old_value, curbuf->b_p_bin, opt_flags);
#ifdef FEAT_TITLE
	redraw_titles();
#endif
    }

#ifdef FEAT_AUTOCMD

    else if ((int *)varp == &curbuf->b_p_bl && old_value != curbuf->b_p_bl)
    {
	apply_autocmds(curbuf->b_p_bl ? EVENT_BUFADD : EVENT_BUFDELETE,
						    NULL, NULL, TRUE, curbuf);
    }
#endif


    else if ((int *)varp == &curbuf->b_p_swf)
    {
	if (curbuf->b_p_swf && p_uc)
	    ml_open_file(curbuf);
	else


	    mf_close_file(curbuf, TRUE);
    }


    else if ((int *)varp == &p_terse)
    {
	char_u	*p;

	p = vim_strchr(p_shm, SHM_SEARCH);


	if (p_terse && p == NULL)
	{
	    STRCPY(IObuff, p_shm);
	    STRCAT(IObuff, "s");
	    set_string_option_direct((char_u *)"shm", -1, IObuff, OPT_FREE, 0);
	}

	else if (!p_terse && p != NULL)
	    STRMOVE(p, p + 1);
    }


    else if ((int *)varp == &p_paste)
    {
	paste_option_changed();
    }


    else if ((int *)varp == &p_im)
    {
	if (p_im)
	{
	    if ((State & INSERT) == 0)
		need_start_insertmode = TRUE;
	    stop_insert_mode = FALSE;
	}

	else if (old_value)
	{
	    need_start_insertmode = FALSE;
	    stop_insert_mode = TRUE;
	    if (restart_edit != 0 && mode_displayed)
		clear_cmdline = TRUE;
	    restart_edit = 0;
	}
    }


    else if ((int *)varp == &p_ic && p_hls)
    {
	redraw_all_later(SOME_VALID);
    }

#ifdef FEAT_SEARCH_EXTRA

    else if ((int *)varp == &p_hls)
    {
	SET_NO_HLSEARCH(FALSE);
    }
#endif

#ifdef FEAT_SCROLLBIND


    else if ((int *)varp == &curwin->w_p_scb)
    {
	if (curwin->w_p_scb)
	{
	    do_check_scrollbind(FALSE);
	    curwin->w_scbind_pos = curwin->w_topline;
	}
    }
#endif

#if defined(FEAT_WINDOWS) && defined(FEAT_QUICKFIX)

    else if ((int *)varp == &curwin->w_p_pvw)
    {
	if (curwin->w_p_pvw)
	{
	    win_T	*win;

	    FOR_ALL_WINDOWS(win)
		if (win->w_p_pvw && win != curwin)
		{
		    curwin->w_p_pvw = FALSE;
		    return (char_u *)N_("E590: A preview window already exists");
		}
	}
    }
#endif


    else if ((int *)varp == &curbuf->b_p_tx)
    {
	set_fileformat(curbuf->b_p_tx ? EOL_DOS : EOL_UNIX, opt_flags);
    }


    else if ((int *)varp == &p_ta)
	set_string_option_direct((char_u *)"ffs", -1,
				 p_ta ? (char_u *)DFLT_FFS_VIM : (char_u *)"",
						     OPT_FREE | opt_flags, 0);


#ifdef FEAT_LISP
    else if (varp == (char_u *)&(curbuf->b_p_lisp))
    {
	(void)buf_init_chartab(curbuf, FALSE);
    }
#endif

#ifdef FEAT_TITLE

    else if ((int *)varp == &p_title)
    {
	did_set_title(FALSE);
    }

    else if ((int *)varp == &p_icon)
    {
	did_set_title(TRUE);
    }
#endif

    else if ((int *)varp == &curbuf->b_changed)
    {
	if (!value)
	    save_file_ff(curbuf);
#ifdef FEAT_TITLE
	redraw_titles();
#endif
#ifdef FEAT_AUTOCMD
	modified_was_set = value;
#endif
    }

#ifdef BACKSLASH_IN_FILENAME
    else if ((int *)varp == &p_ssl)
    {
	if (p_ssl)
	{
	    psepc = '/';
	    psepcN = '\\';
	    pseps[0] = '/';
	}
	else
	{
	    psepc = '\\';
	    psepcN = '/';
	    pseps[0] = '\\';
	}


	buflist_slash_adjust();
	alist_slash_adjust();
# ifdef FEAT_EVAL
	scriptnames_slash_adjust();
# endif
    }
#endif


    else if ((int *)varp == &curwin->w_p_wrap)
    {
	if (curwin->w_p_wrap)
	    curwin->w_leftcol = 0;
    }

#ifdef FEAT_WINDOWS
    else if ((int *)varp == &p_ea)
    {
	if (p_ea && !old_value)
	    win_equal(curwin, FALSE, 0);
    }
#endif

    else if ((int *)varp == &p_wiv)
    {


	if (p_wiv && !old_value)
	    T_XS = (char_u *)"y";
	else if (!p_wiv && old_value)
	    T_XS = empty_option;
	p_wiv = (*T_XS != NUL);
    }

#ifdef FEAT_BEVAL
    else if ((int *)varp == &p_beval)
    {
	if (p_beval && !old_value)
	    gui_mch_enable_beval_area(balloonEval);
	else if (!p_beval && old_value)
	    gui_mch_disable_beval_area(balloonEval);
    }
#endif

#ifdef FEAT_AUTOCHDIR
    else if ((int *)varp == &p_acd)
    {

	DO_AUTOCHDIR
    }
#endif

#ifdef FEAT_DIFF

    else if ((int *)varp == &curwin->w_p_diff)
    {

	diff_buf_adjust(curwin);
# ifdef FEAT_FOLDING
	if (foldmethodIsDiff(curwin))
	    foldUpdateAll(curwin);
# endif
    }
#endif

#ifdef USE_IM_CONTROL

    else if ((int *)varp == &p_imdisable)
    {

	if (p_imdisable)
	    im_set_active(FALSE);
	else if (State & INSERT)


	    im_set_active(curbuf->b_p_iminsert == B_IMODE_IM);
    }
#endif

#ifdef FEAT_SPELL

    else if ((int *)varp == &curwin->w_p_spell)
    {
	if (curwin->w_p_spell)
	{
	    char_u	*errmsg = did_set_spelllang(curwin);
	    if (errmsg != NULL)
		EMSG(_(errmsg));
	}
    }
#endif

#ifdef FEAT_FKMAP
    else if ((int *)varp == &p_altkeymap)
    {
	if (old_value != p_altkeymap)
	{
	    if (!p_altkeymap)
	    {
		p_hkmap = p_fkmap;
		p_fkmap = 0;
	    }
	    else
	    {
		p_fkmap = p_hkmap;
		p_hkmap = 0;
	    }
	    (void)init_chartab();
	}
    }


    if ((p_hkmap || p_fkmap) && p_altkeymap)
    {
	p_altkeymap = p_fkmap;
# ifdef FEAT_ARABIC
	curwin->w_p_arab = FALSE;
# endif
	(void)init_chartab();
    }


    if (p_hkmap && p_altkeymap)
    {
	p_altkeymap = 0;
	p_fkmap = 0;
# ifdef FEAT_ARABIC
	curwin->w_p_arab = FALSE;
# endif
	(void)init_chartab();
    }


    if (p_fkmap && !p_altkeymap)
    {
	p_altkeymap = 1;
	p_hkmap = 0;
# ifdef FEAT_ARABIC
	curwin->w_p_arab = FALSE;
# endif
	(void)init_chartab();
    }
#endif

#ifdef FEAT_ARABIC
    if ((int *)varp == &curwin->w_p_arab)
    {
	if (curwin->w_p_arab)
	{


	    if (!p_tbidi)
	    {

		if (!curwin->w_p_rl)
		{
		    curwin->w_p_rl = TRUE;
		    changed_window_setting();
		}


		if (!p_arshape)
		{
		    p_arshape = TRUE;
		    redraw_later_clear();
		}
	    }


	    if (STRCMP(p_enc, "utf-8") != 0)
	    {
		static char *w_arabic = N_("W17: Arabic requires UTF-8, do ':set encoding=utf-8'");

		msg_source(hl_attr(HLF_W));
		MSG_ATTR(_(w_arabic), hl_attr(HLF_W));
#ifdef FEAT_EVAL
		set_vim_var_string(VV_WARNINGMSG, (char_u *)_(w_arabic), -1);
#endif
	    }

# ifdef FEAT_MBYTE

	    p_deco = TRUE;
# endif

# ifdef FEAT_KEYMAP

	    set_option_value((char_u *)"keymap", 0L, (char_u *)"arabic",
								   OPT_LOCAL);
# endif
# ifdef FEAT_FKMAP
	    p_altkeymap = 0;
	    p_hkmap = 0;
	    p_fkmap = 0;
	    (void)init_chartab();
# endif
	}
	else
	{


	    if (!p_tbidi)
	    {

		if (curwin->w_p_rl)
		{
		    curwin->w_p_rl = FALSE;
		    changed_window_setting();
		}


	    }


# ifdef FEAT_KEYMAP

	    curbuf->b_p_iminsert = B_IMODE_NONE;
	    curbuf->b_p_imsearch = B_IMODE_USE_INSERT;
# endif
	}
    }

#endif

#ifdef FEAT_TERMGUICOLORS

    else if ((int *)varp == &p_tgc)
    {
# ifdef FEAT_GUI
	if (!gui.in_use && !gui.starting)
# endif
	    highlight_gui_started();
    }
#endif


    options[opt_idx].flags |= P_WAS_SET;

#if defined(FEAT_AUTOCMD) && defined(FEAT_EVAL)
    if (!starting)
    {
	char_u buf_old[2], buf_new[2], buf_type[7];
	vim_snprintf((char *)buf_old, 2, "%d", old_value ? TRUE: FALSE);
	vim_snprintf((char *)buf_new, 2, "%d", value ? TRUE: FALSE);
	vim_snprintf((char *)buf_type, 7, "%s", (opt_flags & OPT_LOCAL) ? "local" : "global");
	set_vim_var_string(VV_OPTION_NEW, buf_new, -1);
	set_vim_var_string(VV_OPTION_OLD, buf_old, -1);
	set_vim_var_string(VV_OPTION_TYPE, buf_type, -1);
	apply_autocmds(EVENT_OPTIONSET, (char_u *) options[opt_idx].fullname, NULL, FALSE, NULL);
	reset_v_option_vars();
    }
#endif

    comp_col();
    if (curwin->w_curswant != MAXCOL
		     && (options[opt_idx].flags & (P_CURSWANT | P_RALL)) != 0)
	curwin->w_set_curswant = TRUE;
    check_redraw(options[opt_idx].flags);

    return NULL;
}
