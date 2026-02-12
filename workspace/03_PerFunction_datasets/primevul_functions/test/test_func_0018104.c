setmouse(void)
{
    int	    checkfor;

# ifdef FEAT_MOUSESHAPE
    update_mouseshape(-1);
# endif


#  ifdef FEAT_GUI

    if (gui.in_use)
	return;
#  endif

    if (*p_mouse == NUL || has_mouse_termcode == 0)
	return;


    if (cur_tmode != TMODE_RAW)
    {
	mch_setmouse(FALSE);
	return;
    }

    if (VIsual_active)
	checkfor = MOUSE_VISUAL;
    else if (State == MODE_HITRETURN || State == MODE_ASKMORE
						     || State == MODE_SETWSIZE)
	checkfor = MOUSE_RETURN;
    else if (State & MODE_INSERT)
	checkfor = MOUSE_INSERT;
    else if (State & MODE_CMDLINE)
	checkfor = MOUSE_COMMAND;
    else if (State == MODE_CONFIRM || State == MODE_EXTERNCMD)
	checkfor = ' ';
    else
	checkfor = MOUSE_NORMAL;

    if (mouse_has(checkfor))
	mch_setmouse(TRUE);
    else
	mch_setmouse(FALSE);
}
