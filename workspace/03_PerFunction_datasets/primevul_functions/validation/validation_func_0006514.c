ins_compl_prep(int c)
{
    int		retval = FALSE;
    int		prev_mode = ctrl_x_mode;


    if (c != Ctrl_R && vim_is_ctrl_x_key(c))
	edit_submode_extra = NULL;


    if (c == K_SELECT || c == K_MOUSEDOWN || c == K_MOUSEUP
	    || c == K_MOUSELEFT || c == K_MOUSERIGHT
	    || c == K_COMMAND || c == K_SCRIPT_COMMAND)
	return retval;

#ifdef FEAT_PROP_POPUP

    if (is_mouse_key(c))
    {


	if (c == K_LEFTRELEASE
		|| c == K_LEFTRELEASE_NM
		|| c == K_MIDDLERELEASE
		|| c == K_RIGHTRELEASE
		|| c == K_X1RELEASE
		|| c == K_X2RELEASE
		|| c == K_LEFTDRAG
		|| c == K_MIDDLEDRAG
		|| c == K_RIGHTDRAG
		|| c == K_X1DRAG
		|| c == K_X2DRAG)
	    return retval;
	if (popup_visible)
	{
	    int	    row = mouse_row;
	    int	    col = mouse_col;
	    win_T   *wp = mouse_find_win(&row, &col, FIND_POPUP);

	    if (wp != NULL && WIN_IS_POPUP(wp))
		return retval;
	}
    }
#endif

    if (ctrl_x_mode == CTRL_X_CMDLINE_CTRL_X && c != Ctrl_X)
    {
	if (c == Ctrl_V || c == Ctrl_Q || c == Ctrl_Z || ins_compl_pum_key(c)
		|| !vim_is_ctrl_x_key(c))
	{

	    ctrl_x_mode = CTRL_X_CMDLINE;


	    if (c == Ctrl_Z)
		retval = TRUE;
	}
	else
	{
	    ctrl_x_mode = CTRL_X_CMDLINE;


	    ins_compl_prep(' ');
	    ctrl_x_mode = CTRL_X_NOT_DEFINED_YET;
	}
    }


    if (ctrl_x_mode_not_defined_yet()
			   || (ctrl_x_mode_normal() && !compl_started))
    {
	compl_get_longest = (strstr((char *)p_cot, "longest") != NULL);
	compl_used_match = TRUE;

    }

    if (ctrl_x_mode_not_defined_yet())


	retval = set_ctrl_x_mode(c);
    else if (ctrl_x_mode_not_default())
    {

	if (!vim_is_ctrl_x_key(c))
	{
	    if (ctrl_x_mode_scroll())
		ctrl_x_mode = CTRL_X_NORMAL;
	    else
		ctrl_x_mode = CTRL_X_FINISHED;
	    edit_submode = NULL;
	}
	showmode();
    }

    if (compl_started || ctrl_x_mode == CTRL_X_FINISHED)
    {


	showmode();
	if ((ctrl_x_mode_normal() && c != Ctrl_N && c != Ctrl_P
				       && c != Ctrl_R && !ins_compl_pum_key(c))
		|| ctrl_x_mode == CTRL_X_FINISHED)
	    retval = ins_compl_stop(c, prev_mode, retval);
    }
    else if (ctrl_x_mode == CTRL_X_LOCAL_MSG)


	ins_apply_autocmds(EVENT_COMPLETEDONE);

    may_trigger_modechanged();


    if (!vim_is_ctrl_x_key(c))
    {
	compl_cont_status = 0;
	compl_cont_mode = 0;
    }

    return retval;
}
