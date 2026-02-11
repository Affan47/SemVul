check_mouse_termcode()
{
# ifdef FEAT_MOUSE_XTERM
    if (use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
    {
	set_mouse_termcode(KS_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		    ? IF_EB("\233M", CSI_STR "M")
		    : IF_EB("\033[M", ESC_STR "[M")));
	if (*p_mouse != NUL)
	{


	    mch_setmouse(FALSE);
	    setmouse();
	}
    }
    else
	del_mouse_termcode(KS_MOUSE);
# endif

# ifdef FEAT_MOUSE_GPM
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_MOUSE, (char_u *)IF_EB("\033MG", ESC_STR "MG"));
# endif

# ifdef FEAT_SYSMOUSE
    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_MOUSE, (char_u *)IF_EB("\033MS", ESC_STR "MS"));
# endif

# ifdef FEAT_MOUSE_JSB

    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_JSBTERM_MOUSE,
			       (char_u *)IF_EB("\033[0~zw", ESC_STR "[0~zw"));
    else
	del_mouse_termcode(KS_JSBTERM_MOUSE);
# endif

# ifdef FEAT_MOUSE_NET


    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_NETTERM_MOUSE,
				       (char_u *)IF_EB("\033}", ESC_STR "}"));
    else
	del_mouse_termcode(KS_NETTERM_MOUSE);
# endif

# ifdef FEAT_MOUSE_DEC

    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_DEC_MOUSE, (char_u *)(term_is_8bit(T_NAME)
		     ? IF_EB("\233", CSI_STR) : IF_EB("\033[", ESC_STR "[")));
    else
	del_mouse_termcode(KS_DEC_MOUSE);
# endif
# ifdef FEAT_MOUSE_PTERM

    if (!use_xterm_mouse()
#  ifdef FEAT_GUI
	    && !gui.in_use
#  endif
	    )
	set_mouse_termcode(KS_PTERM_MOUSE,
				      (char_u *) IF_EB("\033[", ESC_STR "["));
    else
	del_mouse_termcode(KS_PTERM_MOUSE);
# endif
}
