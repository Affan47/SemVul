ins_reg(void)
{
    int		need_redraw = FALSE;
    int		regname;
    int		literally = 0;
    int		vis_active = VIsual_active;


    pc_status = PC_STATUS_UNSET;
    if (redrawing() && !char_avail())
    {

	ins_redraw(FALSE);

	edit_putchar('"', TRUE);
#ifdef FEAT_CMDL_INFO
	add_to_showcmd_c(Ctrl_R);
#endif
    }

#ifdef USE_ON_FLY_SCROLL
    dont_scroll = TRUE;
#endif


    ++no_mapping;
    ++allow_keys;
    regname = plain_vgetc();
    LANGMAP_ADJUST(regname, TRUE);
    if (regname == Ctrl_R || regname == Ctrl_O || regname == Ctrl_P)
    {

	literally = regname;
#ifdef FEAT_CMDL_INFO
	add_to_showcmd_c(literally);
#endif
	regname = plain_vgetc();
	LANGMAP_ADJUST(regname, TRUE);
    }
    --no_mapping;
    --allow_keys;

#ifdef FEAT_EVAL


    ++no_u_sync;
    if (regname == '=')
    {
	pos_T	curpos = curwin->w_cursor;
# ifdef HAVE_INPUT_METHOD
	int	im_on = im_get_status();
# endif


	u_sync_once = 2;

	regname = get_expr_register();


	curwin->w_cursor = curpos;
	check_cursor();
# ifdef HAVE_INPUT_METHOD

	if (im_on)
	    im_set_active(TRUE);
# endif
    }
    if (regname == NUL || !valid_yank_reg(regname, FALSE))
    {
	vim_beep(BO_REG);
	need_redraw = TRUE;
    }
    else
    {
#endif
	if (literally == Ctrl_O || literally == Ctrl_P)
	{

	    AppendCharToRedobuff(Ctrl_R);
	    AppendCharToRedobuff(literally);
	    AppendCharToRedobuff(regname);

	    do_put(regname, BACKWARD, 1L,
		 (literally == Ctrl_P ? PUT_FIXINDENT : 0) | PUT_CURSEND);
	}
	else if (insert_reg(regname, literally) == FAIL)
	{
	    vim_beep(BO_REG);
	    need_redraw = TRUE;
	}
	else if (stop_insert_mode)


	    need_redraw = TRUE;

#ifdef FEAT_EVAL
    }
    --no_u_sync;
    if (u_sync_once == 1)
	ins_need_undo = TRUE;
    u_sync_once = 0;
#endif
#ifdef FEAT_CMDL_INFO
    clear_showcmd();
#endif


    if (need_redraw || stuff_empty())
	edit_unputchar();


    if (!vis_active && VIsual_active)
	end_visual_mode();
}
