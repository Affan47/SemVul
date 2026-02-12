nv_normal(cmdarg_T *cap)
{
    if (cap->nchar == Ctrl_N || cap->nchar == Ctrl_G)
    {
	clearop(cap->oap);
	if (restart_edit != 0 && mode_displayed)
	    clear_cmdline = TRUE;
	restart_edit = 0;
#ifdef FEAT_CMDWIN
	if (cmdwin_type != 0)
	    cmdwin_result = Ctrl_C;
#endif
	if (VIsual_active)
	{
	    end_visual_mode();
	    redraw_curbuf_later(INVERTED);
	}

	if (cap->nchar == Ctrl_G && p_im)
	    restart_edit = 'a';
    }
    else
	clearopbeep(cap->oap);
}
