check_termcode_mouse(
    char_u	*tp,
    int		*slen,
    char_u	*key_name,
    char_u	*modifiers_start,
    int		idx,
    int		*modifiers)
{
    int		j;
    char_u	*p;
# if !defined(UNIX) || defined(FEAT_MOUSE_XTERM) || defined(FEAT_GUI) \
    || defined(FEAT_MOUSE_GPM) || defined(FEAT_SYSMOUSE)
    char_u	bytes[6];
    int		num_bytes;
# endif
    int		mouse_code = 0;
    int		is_click, is_drag;
    int		is_release, release_is_ambiguous;
    int		wheel_code = 0;
    int		current_button;
    static int	orig_num_clicks = 1;
    static int	orig_mouse_code = 0x0;
# ifdef CHECK_DOUBLE_CLICK
    static int	orig_mouse_col = 0;
    static int	orig_mouse_row = 0;
    static struct timeval  orig_mouse_time = {0, 0};

    struct timeval  mouse_time;
    long	timediff;
# endif

    is_click = is_drag = is_release = release_is_ambiguous = FALSE;

# if !defined(UNIX) || defined(FEAT_MOUSE_XTERM) || defined(FEAT_GUI) \
    || defined(FEAT_MOUSE_GPM) || defined(FEAT_SYSMOUSE)
    if (key_name[0] == KS_MOUSE
#  ifdef FEAT_MOUSE_GPM
	    || key_name[0] == KS_GPM_MOUSE
#  endif
       )
    {


	for (;;)
	{
#  ifdef FEAT_GUI
	    if (gui.in_use)
	    {

		num_bytes = get_bytes_from_buf(tp + *slen, bytes, 5);
		if (num_bytes == -1)
		    return -1;
		mouse_code = bytes[0];
		mouse_col = 128 * (bytes[1] - ' ' - 1)
		    + bytes[2] - ' ' - 1;
		mouse_row = 128 * (bytes[3] - ' ' - 1)
		    + bytes[4] - ' ' - 1;
	    }
	    else
#  endif
	    {
		num_bytes = get_bytes_from_buf(tp + *slen, bytes, 3);
		if (num_bytes == -1)
		    return -1;
		mouse_code = bytes[0];
		mouse_col = bytes[1] - ' ' - 1;
		mouse_row = bytes[2] - ' ' - 1;
	    }
	    *slen += num_bytes;


#  ifdef FEAT_GUI
	    if (gui.in_use)
		j = 3;
	    else
#  endif
		j = get_termcode_len(idx);
	    if (STRNCMP(tp, tp + *slen, (size_t)j) == 0
		    && tp[*slen + j] == mouse_code
		    && tp[*slen + j + 1] != NUL
		    && tp[*slen + j + 2] != NUL
#  ifdef FEAT_GUI
		    && (!gui.in_use
			|| (tp[*slen + j + 3] != NUL
			    && tp[*slen + j + 4] != NUL))
#  endif
	       )
		*slen += j;
	    else
		break;
	}
    }

    if (key_name[0] == KS_URXVT_MOUSE
	    || key_name[0] == KS_SGR_MOUSE
	    || key_name[0] == KS_SGR_MOUSE_RELEASE)
    {


	p = modifiers_start;
	if (p == NULL)
	    return -1;

	mouse_code = getdigits(&p);
	if (*p++ != ';')
	    return -1;


	if (key_name[0] == KS_SGR_MOUSE
		|| key_name[0] == KS_SGR_MOUSE_RELEASE)
	    mouse_code += 32;

	mouse_col = getdigits(&p) - 1;
	if (*p++ != ';')
	    return -1;

	mouse_row = getdigits(&p) - 1;


	*modifiers = 0;
    }

    if (key_name[0] == KS_SGR_MOUSE
	    || key_name[0] == KS_SGR_MOUSE_RELEASE)
    {
	if (key_name[0] == KS_SGR_MOUSE_RELEASE)
	{
	    is_release = TRUE;

	    mouse_code |= MOUSE_RELEASE;
	}
    }
    else
    {
	release_is_ambiguous = TRUE;
	if ((mouse_code & MOUSE_RELEASE) == MOUSE_RELEASE)
	    is_release = TRUE;
    }

    if (key_name[0] == KS_MOUSE
#  ifdef FEAT_MOUSE_GPM
	    || key_name[0] == KS_GPM_MOUSE
#  endif
#  ifdef FEAT_MOUSE_URXVT
	    || key_name[0] == KS_URXVT_MOUSE
#  endif
	    || key_name[0] == KS_SGR_MOUSE
	    || key_name[0] == KS_SGR_MOUSE_RELEASE)
    {
#  if !defined(MSWIN)


	if (mouse_code >= MOUSEWHEEL_LOW
#   ifdef FEAT_GUI
		&& !gui.in_use
#   endif
#   ifdef FEAT_MOUSE_GPM
		&& key_name[0] != KS_GPM_MOUSE
#   endif
	   )
	{
#   if defined(UNIX)
	    if (use_xterm_mouse() > 1 && mouse_code >= 0x80)

		mouse_code = MOUSE_DRAG;
	    else
#   endif


		wheel_code = mouse_code;
	}
#   ifdef FEAT_MOUSE_XTERM
	else if (held_button == MOUSE_RELEASE
#    ifdef FEAT_GUI
		&& !gui.in_use
#    endif
		&& (mouse_code == 0x23 || mouse_code == 0x24
		    || mouse_code == 0x40 || mouse_code == 0x41))
	{


	    wheel_code = mouse_code - (mouse_code >= 0x40 ? 0x40 : 0x23)
							      + MOUSEWHEEL_LOW;
	}
#   endif

#   if defined(UNIX)
	else if (use_xterm_mouse() > 1)
	{
	    if (mouse_code & MOUSE_DRAG_XTERM)
		mouse_code |= MOUSE_DRAG;
	}
#   endif
#   ifdef FEAT_XCLIPBOARD
	else if (!(mouse_code & MOUSE_DRAG & ~MOUSE_CLICK_MASK))
	{
	    if (is_release)
		stop_xterm_trace();
	    else
		start_xterm_trace(mouse_code);
	}
#   endif
#  endif
    }
# endif
# ifdef FEAT_MOUSE_NET
    if (key_name[0] == KS_NETTERM_MOUSE)
    {
	int mc, mr;


	p = tp + *slen;
	mr = getdigits(&p);
	if (*p++ != ',')
	    return -1;
	mc = getdigits(&p);
	if (*p++ != '\r')
	    return -1;

	mouse_col = mc - 1;
	mouse_row = mr - 1;
	mouse_code = MOUSE_LEFT;
	*slen += (int)(p - (tp + *slen));
    }
# endif
# ifdef FEAT_MOUSE_JSB
    if (key_name[0] == KS_JSBTERM_MOUSE)
    {
	int mult, val, iter, button, status;


	p = tp + *slen;
	button = mouse_code = 0;
	switch (*p++)
	{
	    case 'L': button = 1; break;
	    case '-': break;
	    case 'x': break;
	    default:  return -1;
	}
	switch (*p++)
	{
	    case 'M': button |= 2; break;
	    case '-': break;
	    case 'x': break;
	    default:  return -1;
	}
	switch (*p++)
	{
	    case 'R': button |= 4; break;
	    case '-': break;
	    case 'x': break;
	    default:  return -1;
	}
	status = *p++;
	for (val = 0, mult = 100, iter = 0; iter < 3; iter++,
		mult /= 10, p++)
	    if (*p >= '0' && *p <= '9')
		val += (*p - '0') * mult;
	    else
		return -1;
	mouse_col = val;
	for (val = 0, mult = 100, iter = 0; iter < 3; iter++,
		mult /= 10, p++)
	    if (*p >= '0' && *p <= '9')
		val += (*p - '0') * mult;
	    else
		return -1;
	mouse_row = val;
	switch (*p++)
	{
	    case 's': button |= 8; break;
	    case '-': break;
	    case 'x': break;
	    default:  return -1;
	}
	switch (*p++)
	{
	    case 'c': button |= 16; break;
	    case '-': break;
	    case 'x': break;
	    default:  return -1;
	}
	if (*p++ != '\033')
	    return -1;
	if (*p++ != '\\')
	    return -1;
	switch (status)
	{
	    case 'D':
	    case 'S':
		if (button & 1) mouse_code |= MOUSE_LEFT;
		if (button & 2) mouse_code |= MOUSE_MIDDLE;
		if (button & 4) mouse_code |= MOUSE_RIGHT;
		if (button & 8) mouse_code |= MOUSE_SHIFT;
		if (button & 16) mouse_code |= MOUSE_CTRL;
		break;
	    case 'm':
		if (button & 1) mouse_code |= MOUSE_LEFT;
		if (button & 2) mouse_code |= MOUSE_MIDDLE;
		if (button & 4) mouse_code |= MOUSE_RIGHT;
		if (button & 8) mouse_code |= MOUSE_SHIFT;
		if (button & 16) mouse_code |= MOUSE_CTRL;
		if ((button & 7) != 0)
		{
		    held_button = mouse_code;
		    mouse_code |= MOUSE_DRAG;
		}
		is_drag = TRUE;
		showmode();
		break;
	    case 'd':
		if (button & 1) mouse_code |= MOUSE_LEFT;
		if (button & 2) mouse_code |= MOUSE_MIDDLE;
		if (button & 4) mouse_code |= MOUSE_RIGHT;
		if (button & 8) mouse_code |= MOUSE_SHIFT;
		if (button & 16) mouse_code |= MOUSE_CTRL;
		break;
	    case 'u':
		is_release = TRUE;
		if (button & 1)
		    mouse_code |= MOUSE_LEFT;
		if (button & 2)
		    mouse_code |= MOUSE_MIDDLE;
		if (button & 4)
		    mouse_code |= MOUSE_RIGHT;
		if (button & 8)
		    mouse_code |= MOUSE_SHIFT;
		if (button & 16)
		    mouse_code |= MOUSE_CTRL;
		break;
	    default: return -1;
	}

	*slen += (p - (tp + *slen));
    }
# endif
# ifdef FEAT_MOUSE_DEC
    if (key_name[0] == KS_DEC_MOUSE)
    {


	int Pe, Pb, Pr, Pc;

	p = tp + *slen;


	Pe = getdigits(&p);
	if (*p++ != ';')
	    return -1;


	Pb = getdigits(&p);
	if (*p++ != ';')
	    return -1;


	Pr = getdigits(&p);
	if (*p++ != ';')
	    return -1;


	Pc = getdigits(&p);


	if (*p == ';')
	{
	    p++;
	    (void)getdigits(&p);
	}
	if (*p++ != '&')
	    return -1;
	if (*p++ != 'w')
	    return -1;

	mouse_code = 0;
	switch (Pe)
	{
	    case  0: return -1;
	    case  1:

		     Pb &= 7;
		     if (Pb & 4)
			 mouse_code  = MOUSE_LEFT;
		     if (Pb & 2)
			 mouse_code  = MOUSE_MIDDLE;
		     if (Pb & 1)
			 mouse_code  = MOUSE_RIGHT;
		     if (Pb)
		     {
			 held_button = mouse_code;
			 mouse_code |= MOUSE_DRAG;
			 WantQueryMouse = TRUE;
		     }
		     is_drag = TRUE;
		     showmode();
		     break;
	    case  2: mouse_code = MOUSE_LEFT;
		     WantQueryMouse = TRUE;
		     break;
	    case  3: mouse_code = MOUSE_LEFT;
		     is_release = TRUE;
		     break;
	    case  4: mouse_code = MOUSE_MIDDLE;
		     WantQueryMouse = TRUE;
		     break;
	    case  5: mouse_code = MOUSE_MIDDLE;
		     is_release = TRUE;
		     break;
	    case  6: mouse_code = MOUSE_RIGHT;
		     WantQueryMouse = TRUE;
		     break;
	    case  7: mouse_code = MOUSE_RIGHT;
		     is_release = TRUE;
		     break;
	    case  8: return -1;
	    case  9: return -1;
	    case 10: return -1;
	    default: return -1;
	}

	mouse_col = Pc - 1;
	mouse_row = Pr - 1;

	*slen += (int)(p - (tp + *slen));
    }
# endif
# ifdef FEAT_MOUSE_PTERM
    if (key_name[0] == KS_PTERM_MOUSE)
    {
	int button, num_clicks, action;

	p = tp + *slen;

	action = getdigits(&p);
	if (*p++ != ';')
	    return -1;

	mouse_row = getdigits(&p);
	if (*p++ != ';')
	    return -1;
	mouse_col = getdigits(&p);
	if (*p++ != ';')
	    return -1;

	button = getdigits(&p);
	mouse_code = 0;

	switch (button)
	{
	    case 4: mouse_code = MOUSE_LEFT; break;
	    case 1: mouse_code = MOUSE_RIGHT; break;
	    case 2: mouse_code = MOUSE_MIDDLE; break;
	    default: return -1;
	}

	switch (action)
	{
	    case 31:
		if (*p++ != ';')
		    return -1;

		num_clicks = getdigits(&p);
		break;

	    case 32:
		is_release = TRUE;
		break;

	    case 33:
		held_button = mouse_code;
		mouse_code |= MOUSE_DRAG;
		break;

	    default:
		return -1;
	}

	if (*p++ != 't')
	    return -1;

	*slen += (p - (tp + *slen));
    }
# endif


    current_button = (mouse_code & MOUSE_CLICK_MASK);
    if (is_release)
	current_button |= MOUSE_RELEASE;

    if (current_button == MOUSE_RELEASE
# ifdef FEAT_MOUSE_XTERM
	    && wheel_code == 0
# endif
       )
    {


	if ((mouse_code & MOUSE_DRAG) == MOUSE_DRAG)
	    is_drag = TRUE;
	current_button = held_button;
    }
    else
    {
      if (wheel_code == 0)
      {
# ifdef CHECK_DOUBLE_CLICK
#  ifdef FEAT_MOUSE_GPM


#   ifdef FEAT_GUI
	if (key_name[0] != KS_GPM_MOUSE && !gui.in_use)
#   else
	    if (key_name[0] != KS_GPM_MOUSE)
#   endif
#  else
#   ifdef FEAT_GUI
		if (!gui.in_use)
#   endif
#  endif
		{


		    gettimeofday(&mouse_time, NULL);
		    if (orig_mouse_time.tv_sec == 0)
		    {


			timediff = p_mouset;
		    }
		    else
			timediff = time_diff_ms(&orig_mouse_time, &mouse_time);
		    orig_mouse_time = mouse_time;
		    if (mouse_code == orig_mouse_code
			    && timediff < p_mouset
			    && orig_num_clicks != 4
			    && orig_mouse_col == mouse_col
			    && orig_mouse_row == mouse_row
			    && (is_mouse_topline(curwin)


				|| (mouse_row == 0 && firstwin->w_winrow > 0))
		       )
			++orig_num_clicks;
		    else
			orig_num_clicks = 1;
		    orig_mouse_col = mouse_col;
		    orig_mouse_row = mouse_row;
		    set_mouse_topline(curwin);
		}
#  if defined(FEAT_GUI) || defined(FEAT_MOUSE_GPM)
		else
		    orig_num_clicks = NUM_MOUSE_CLICKS(mouse_code);
#  endif
# else
	orig_num_clicks = NUM_MOUSE_CLICKS(mouse_code);
# endif
	is_click = TRUE;
      }
      orig_mouse_code = mouse_code;
    }
    if (!is_drag)
	held_button = mouse_code & MOUSE_CLICK_MASK;


    if (orig_mouse_code & MOUSE_SHIFT)
	*modifiers |= MOD_MASK_SHIFT;
    if (orig_mouse_code & MOUSE_CTRL)
	*modifiers |= MOD_MASK_CTRL;
    if (orig_mouse_code & MOUSE_ALT)
	*modifiers |= MOD_MASK_ALT;
    if (orig_num_clicks == 2)
	*modifiers |= MOD_MASK_2CLICK;
    else if (orig_num_clicks == 3)
	*modifiers |= MOD_MASK_3CLICK;
    else if (orig_num_clicks == 4)
	*modifiers |= MOD_MASK_4CLICK;


    key_name[0] = KS_EXTRA;
    if (wheel_code != 0 && (!is_release || release_is_ambiguous))
    {
	if (wheel_code & MOUSE_CTRL)
	    *modifiers |= MOD_MASK_CTRL;
	if (wheel_code & MOUSE_ALT)
	    *modifiers |= MOD_MASK_ALT;

	if (wheel_code & 1 && wheel_code & 2)
	    key_name[1] = (int)KE_MOUSELEFT;
	else if (wheel_code & 2)
	    key_name[1] = (int)KE_MOUSERIGHT;
	else if (wheel_code & 1)
	    key_name[1] = (int)KE_MOUSEUP;
	else
	    key_name[1] = (int)KE_MOUSEDOWN;

	held_button = MOUSE_RELEASE;
    }
    else
	key_name[1] = get_pseudo_mouse_code(current_button, is_click, is_drag);


    if (mouse_col >= Columns)
	mouse_col = Columns - 1;
    if (mouse_row >= Rows)
	mouse_row = Rows - 1;

    return 0;
}
