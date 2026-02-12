aucmd_prepbuf(
    aco_save_T	*aco,
    buf_T	*buf)
{
    win_T	*win;
    int		save_ea;
#ifdef FEAT_AUTOCHDIR
    int		save_acd;
#endif


    if (buf == curbuf)
	win = curwin;
    else
	FOR_ALL_WINDOWS(win)
	    if (win->w_buffer == buf)
		break;


    if (win == NULL && aucmd_win == NULL)
    {
	win_alloc_aucmd_win();
	if (aucmd_win == NULL)
	    win = curwin;
    }
    if (win == NULL && aucmd_win_used)


	win = curwin;

    aco->save_curwin = curwin;
    aco->save_curbuf = curbuf;
    if (win != NULL)
    {


	aco->use_aucmd_win = FALSE;
	curwin = win;
    }
    else
    {


	aco->use_aucmd_win = TRUE;
	aucmd_win_used = TRUE;
	aucmd_win->w_buffer = buf;
	aucmd_win->w_s = &buf->b_s;
	++buf->b_nwindows;
	win_init_empty(aucmd_win);


	vim_free(aucmd_win->w_localdir);
	aucmd_win->w_localdir = NULL;
	aco->globaldir = globaldir;
	globaldir = NULL;


	block_autocmds();
	make_snapshot(SNAP_AUCMD_IDX);
	save_ea = p_ea;
	p_ea = FALSE;

#ifdef FEAT_AUTOCHDIR

	save_acd = p_acd;
	p_acd = FALSE;
#endif

	(void)win_split_ins(0, WSP_TOP, aucmd_win, 0);
	(void)win_comp_pos();
	p_ea = save_ea;
#ifdef FEAT_AUTOCHDIR
	p_acd = save_acd;
#endif
	unblock_autocmds();
	curwin = aucmd_win;
    }
    curbuf = buf;
    aco->new_curwin = curwin;
    set_bufref(&aco->new_curbuf, curbuf);
}
