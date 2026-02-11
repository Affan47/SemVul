xim_queue_key_press_event(GdkEventKey *event, int down)
{
    if (down)
    {


	switch (event->keyval)
	{
	    case GDK_KP_Add:      xim_expected_char = '+';  break;
	    case GDK_KP_Subtract: xim_expected_char = '-';  break;
	    case GDK_KP_Divide:   xim_expected_char = '/';  break;
	    case GDK_KP_Multiply: xim_expected_char = '*';  break;
	    case GDK_KP_Decimal:  xim_expected_char = '.';  break;
	    case GDK_KP_Equal:    xim_expected_char = '=';  break;
	    case GDK_KP_0:	  xim_expected_char = '0';  break;
	    case GDK_KP_1:	  xim_expected_char = '1';  break;
	    case GDK_KP_2:	  xim_expected_char = '2';  break;
	    case GDK_KP_3:	  xim_expected_char = '3';  break;
	    case GDK_KP_4:	  xim_expected_char = '4';  break;
	    case GDK_KP_5:	  xim_expected_char = '5';  break;
	    case GDK_KP_6:	  xim_expected_char = '6';  break;
	    case GDK_KP_7:	  xim_expected_char = '7';  break;
	    case GDK_KP_8:	  xim_expected_char = '8';  break;
	    case GDK_KP_9:	  xim_expected_char = '9';  break;
	    case GDK_space:	  xim_expected_char = ' ';  break;
	    default:		  xim_expected_char = NUL;
	}
	xim_ignored_char = FALSE;
    }


    if (xic != NULL && !p_imdisable
		    && (State & (INSERT | CMDLINE | NORMAL | EXTERNCMD)) != 0)
    {


	if (event->keyval == im_activatekey_keyval
	     && (event->state & im_activatekey_state) == im_activatekey_state)
	{
	    unsigned int state_mask;


	    state_mask  = im_activatekey_state;
	    state_mask |= ((int)GDK_SHIFT_MASK | (int)GDK_CONTROL_MASK
							| (int)GDK_MOD1_MASK);

	    if ((event->state & state_mask) != im_activatekey_state)
		return FALSE;


	    if (event->type != GDK_KEY_PRESS)
		return TRUE;

	    if (map_to_exists_mode((char_u *)"", LANGMAP, FALSE))
	    {
		im_set_active(FALSE);


		State ^= LANGMAP;
		if (State & LANGMAP)
		{
		    curbuf->b_p_iminsert = B_IMODE_NONE;
		    State &= ~LANGMAP;
		}
		else
		{
		    curbuf->b_p_iminsert = B_IMODE_LMAP;
		    State |= LANGMAP;
		}
		return TRUE;
	    }

	    return gtk_im_context_filter_keypress(xic, event);
	}


	if (im_activatekey_keyval == GDK_VoidSymbol || im_is_active)
	{
	    int imresult = gtk_im_context_filter_keypress(xic, event);


	    if (!imresult && preedit_start_col != MAXCOL
					       && event->keyval == GDK_Return)
	    {
		im_synthesize_keypress(GDK_Return, 0U);
		return FALSE;
	    }


	    if (xim_expected_char != NUL && xim_ignored_char)

		return FALSE;


	    xim_expected_char = NUL;


	    return imresult;
	}
    }

    return FALSE;
}
