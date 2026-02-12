jumpto_tag(
    char_u	*lbuf_arg,
    int		forceit,
    int		keep_help)
{
    optmagic_T	save_magic_overruled;
    int		save_p_ws, save_p_scs, save_p_ic;
    linenr_T	save_lnum;
    char_u	*str;
    char_u	*pbuf;
    char_u	*pbuf_end;
    char_u	*tofree_fname = NULL;
    char_u	*fname;
    tagptrs_T	tagp;
    int		retval = FAIL;
    int		getfile_result = GETFILE_UNUSED;
    int		search_options;
#ifdef FEAT_SEARCH_EXTRA
    int		save_no_hlsearch;
#endif
#if defined(FEAT_QUICKFIX)
    win_T	*curwin_save = NULL;
#endif
    char_u	*full_fname = NULL;
#ifdef FEAT_FOLDING
    int		old_KeyTyped = KeyTyped;
#endif
    size_t	len;
    char_u	*lbuf;


    len = matching_line_len(lbuf_arg) + 1;
    lbuf = alloc(len);
    if (lbuf != NULL)
	mch_memmove(lbuf, lbuf_arg, len);

    pbuf = alloc(LSIZE);


    if (pbuf == NULL || lbuf == NULL || parse_match(lbuf, &tagp) == FAIL)
    {
	tagp.fname_end = NULL;
	goto erret;
    }


    *tagp.fname_end = NUL;
    fname = tagp.fname;


    str = tagp.command;
    for (pbuf_end = pbuf; *str && *str != '\n' && *str != '\r'; )
    {
#ifdef FEAT_EMACS_TAGS
	if (tagp.is_etag && *str == ',')
	    break;
#endif
	*pbuf_end++ = *str++;
	if (pbuf_end - pbuf + 1 >= LSIZE)
	    break;
    }
    *pbuf_end = NUL;

#ifdef FEAT_EMACS_TAGS
    if (!tagp.is_etag)
#endif
    {


	str = pbuf;
	if (find_extra(&str) == OK)
	{
	    pbuf_end = str;
	    *pbuf_end = NUL;
	}
    }


    fname = expand_tag_fname(fname, tagp.tag_fname, TRUE);
    if (fname == NULL)
	goto erret;
    tofree_fname = fname;


    if (mch_getperm(fname) < 0 && !has_autocmd(EVENT_BUFREADCMD, fname, NULL))
    {
	retval = NOTAGFILE;
	vim_free(nofile_fname);
	nofile_fname = vim_strsave(fname);
	if (nofile_fname == NULL)
	    nofile_fname = empty_option;
	goto erret;
    }

    ++RedrawingDisabled;

#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif

#if defined(FEAT_QUICKFIX)
    if (g_do_tagpreview != 0)
    {
	postponed_split = 0;
	curwin_save = curwin;


	if (!curwin->w_p_pvw)
	{
	    full_fname = FullName_save(fname, FALSE);
	    fname = full_fname;


	    prepare_tagpreview(TRUE, TRUE, FALSE);
	}
    }


    if (postponed_split && (swb_flags & (SWB_USEOPEN | SWB_USETAB)))
    {
	buf_T *existing_buf = buflist_findname_exp(fname);

	if (existing_buf != NULL)
	{
	    win_T *wp = NULL;

	    if (swb_flags & SWB_USEOPEN)
		wp = buf_jump_open_win(existing_buf);


	    if (wp == NULL && (swb_flags & SWB_USETAB))
		wp = buf_jump_open_tab(existing_buf);


	    if (wp != NULL)
		getfile_result = GETFILE_SAME_FILE;
	}
    }
    if (getfile_result == GETFILE_UNUSED
				  && (postponed_split || cmdmod.cmod_tab != 0))
    {
	if (win_split(postponed_split > 0 ? postponed_split : 0,
						postponed_split_flags) == FAIL)
	{
	    --RedrawingDisabled;
	    goto erret;
	}
	RESET_BINDING(curwin);
    }
#endif

    if (keep_help)
    {


#if defined(FEAT_QUICKFIX)
	if (g_do_tagpreview != 0)
	    keep_help_flag = bt_help(curwin_save->w_buffer);
	else
#endif
	    keep_help_flag = curbuf->b_help;
    }

    if (getfile_result == GETFILE_UNUSED)


	getfile_result = getfile(0, fname, NULL, TRUE, (linenr_T)0, forceit);
    keep_help_flag = FALSE;

    if (GETFILE_SUCCESS(getfile_result))
    {
	curwin->w_set_curswant = TRUE;
	postponed_split = 0;

	save_magic_overruled = magic_overruled;
	magic_overruled = OPTION_MAGIC_OFF;
#ifdef FEAT_SEARCH_EXTRA

	save_no_hlsearch = no_hlsearch;
#endif
#if defined(FEAT_PROP_POPUP) && defined(FEAT_QUICKFIX)

	if (g_do_tagpreview != 0 && *p_pvp != NUL)
	    parse_previewpopup(curwin);
#endif


	if (vim_strchr(p_cpo, CPO_TAGPAT) != NULL)
	    search_options = 0;
	else
	    search_options = SEARCH_KEEP;


	str = pbuf;
	if (pbuf[0] == '/' || pbuf[0] == '?')
	    str = skip_regexp(pbuf + 1, pbuf[0], FALSE) + 1;
	if (str > pbuf_end - 1)
	{
	    save_p_ws = p_ws;
	    save_p_ic = p_ic;
	    save_p_scs = p_scs;
	    p_ws = TRUE;
	    p_ic = FALSE;
	    p_scs = FALSE;
	    save_lnum = curwin->w_cursor.lnum;
	    if (tagp.tagline > 0)

		curwin->w_cursor.lnum = tagp.tagline - 1;
	    else

		curwin->w_cursor.lnum = 0;
	    if (do_search(NULL, pbuf[0], pbuf[0], pbuf + 1, (long)1,
							 search_options, NULL))
		retval = OK;
	    else
	    {
		int	found = 1;
		int	cc;


		p_ic = TRUE;
		if (!do_search(NULL, pbuf[0], pbuf[0], pbuf + 1, (long)1,
							 search_options, NULL))
		{


		    found = 2;
		    (void)test_for_static(&tagp);
		    cc = *tagp.tagname_end;
		    *tagp.tagname_end = NUL;
		    sprintf((char *)pbuf, "^%s\\s\\*(", tagp.tagname);
		    if (!do_search(NULL, '/', '/', pbuf, (long)1,
							 search_options, NULL))
		    {

			sprintf((char *)pbuf, "^\\[#a-zA-Z_]\\.\\*\\<%s\\s\\*(",
								tagp.tagname);
			if (!do_search(NULL, '/', '/', pbuf, (long)1,
							 search_options, NULL))
			    found = 0;
		    }
		    *tagp.tagname_end = cc;
		}
		if (found == 0)
		{
		    emsg(_(e_canot_find_tag_pattern));
		    curwin->w_cursor.lnum = save_lnum;
		}
		else
		{


		    if (found == 2 || !save_p_ic)
		    {
			msg(_(e_couldnt_find_tag_just_guessing));
			if (!msg_scrolled && msg_silent == 0)
			{
			    out_flush();
			    ui_delay(1010L, TRUE);
			}
		    }
		    retval = OK;
		}
	    }
	    p_ws = save_p_ws;
	    p_ic = save_p_ic;
	    p_scs = save_p_scs;


	    check_cursor();
	}
	else
	{
	    int		save_secure = secure;


	    secure = 1;
#ifdef HAVE_SANDBOX
	    ++sandbox;
#endif
	    curwin->w_cursor.lnum = 1;
	    do_cmdline_cmd(pbuf);
	    retval = OK;


	    if (secure == 2)
		wait_return(TRUE);
	    secure = save_secure;
#ifdef HAVE_SANDBOX
	    --sandbox;
#endif
	}

	magic_overruled = save_magic_overruled;
#ifdef FEAT_SEARCH_EXTRA

	if (search_options)
	    set_no_hlsearch(save_no_hlsearch);
#endif


	if (getfile_result == GETFILE_OPEN_OTHER)
	    retval = OK;

	if (retval == OK)
	{


	    if (curbuf->b_help)
		set_topline(curwin, curwin->w_cursor.lnum);
#ifdef FEAT_FOLDING
	    if ((fdo_flags & FDO_TAG) && old_KeyTyped)
		foldOpenCursor();
#endif
	}

#if defined(FEAT_QUICKFIX)
	if (g_do_tagpreview != 0
			   && curwin != curwin_save && win_valid(curwin_save))
	{

	    validate_cursor();
	    redraw_later(UPD_VALID);
	    win_enter(curwin_save, TRUE);
	}
#endif

	--RedrawingDisabled;
    }
    else
    {
	--RedrawingDisabled;
	got_int = FALSE;

	if (postponed_split)
	{
	    win_close(curwin, FALSE);
	    postponed_split = 0;
	}
#if defined(FEAT_QUICKFIX) && defined(FEAT_PROP_POPUP)
	else if (WIN_IS_POPUP(curwin))
	{
	    win_T   *wp = curwin;

	    if (win_valid(curwin_save))
		win_enter(curwin_save, TRUE);
	    popup_close(wp->w_id, FALSE);
	}
#endif
    }
#if defined(FEAT_QUICKFIX) && defined(FEAT_PROP_POPUP)
    if (WIN_IS_POPUP(curwin))

	win_enter(firstwin, TRUE);
#endif

erret:
#if defined(FEAT_QUICKFIX)
    g_do_tagpreview = 0;
#endif
    vim_free(lbuf);
    vim_free(pbuf);
    vim_free(tofree_fname);
    vim_free(full_fname);

    return retval;
}
