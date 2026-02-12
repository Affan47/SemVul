set_ctrl_x_mode(int c)
{
    int retval = FALSE;

    switch (c)
    {
	case Ctrl_E:
	case Ctrl_Y:

	    ctrl_x_mode = CTRL_X_SCROLL;
	    if (!(State & REPLACE_FLAG))
		edit_submode = (char_u *)_(" (insert) Scroll (^E/^Y)");
	    else
		edit_submode = (char_u *)_(" (replace) Scroll (^E/^Y)");
	    edit_submode_pre = NULL;
	    showmode();
	    break;
	case Ctrl_L:

	    ctrl_x_mode = CTRL_X_WHOLE_LINE;
	    break;
	case Ctrl_F:

	    ctrl_x_mode = CTRL_X_FILES;
	    break;
	case Ctrl_K:

	    ctrl_x_mode = CTRL_X_DICTIONARY;
	    break;
	case Ctrl_R:


	    break;
	case Ctrl_T:

	    ctrl_x_mode = CTRL_X_THESAURUS;
	    break;
#ifdef FEAT_COMPL_FUNC
	case Ctrl_U:

	    ctrl_x_mode = CTRL_X_FUNCTION;
	    break;
	case Ctrl_O:

	    ctrl_x_mode = CTRL_X_OMNI;
	    break;
#endif
	case 's':
	case Ctrl_S:

	    ctrl_x_mode = CTRL_X_SPELL;
#ifdef FEAT_SPELL
	    ++emsg_off;
	    spell_back_to_badword();
	    --emsg_off;
#endif
	    break;
	case Ctrl_RSB:

	    ctrl_x_mode = CTRL_X_TAGS;
	    break;
#ifdef FEAT_FIND_ID
	case Ctrl_I:
	case K_S_TAB:

	    ctrl_x_mode = CTRL_X_PATH_PATTERNS;
	    break;
	case Ctrl_D:

	    ctrl_x_mode = CTRL_X_PATH_DEFINES;
	    break;
#endif
	case Ctrl_V:
	case Ctrl_Q:

	    ctrl_x_mode = CTRL_X_CMDLINE;
	    break;
	case Ctrl_Z:

	    ctrl_x_mode = CTRL_X_NORMAL;
	    edit_submode = NULL;
	    showmode();
	    retval = TRUE;
	    break;
	case Ctrl_P:
	case Ctrl_N:


	    if (!(compl_cont_status & CONT_INTRPT))
		compl_cont_status |= CONT_LOCAL;
	    else if (compl_cont_mode != 0)
		compl_cont_status &= ~CONT_LOCAL;

	default:


	    if (c == Ctrl_X)
	    {
		if (compl_cont_mode != 0)
		    compl_cont_status = 0;
		else
		    compl_cont_mode = CTRL_X_NOT_DEFINED_YET;
	    }
	    ctrl_x_mode = CTRL_X_NORMAL;
	    edit_submode = NULL;
	    showmode();
	    break;
    }

    return retval;
}
