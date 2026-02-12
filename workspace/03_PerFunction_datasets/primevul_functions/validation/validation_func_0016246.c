vgetc(void)
{
    int		c, c2;
    int		n;
    char_u	buf[MB_MAXBYTES + 1];
    int		i;

#ifdef FEAT_EVAL


    if (may_garbage_collect && want_garbage_collect)
	garbage_collect(FALSE);
#endif


    if (old_char != -1)
    {
	c = old_char;
	old_char = -1;
	mod_mask = old_mod_mask;
	mouse_row = old_mouse_row;
	mouse_col = old_mouse_col;
    }
    else
    {
	mod_mask = 0;
	vgetc_mod_mask = 0;
	vgetc_char = 0;
	last_recorded_len = 0;

	for (;;)
	{
	    int did_inc = FALSE;

	    if (mod_mask
#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
		    || im_is_preediting()
#endif
#if defined(FEAT_PROP_POPUP)
		    || popup_no_mapping()
#endif
		    )
	    {

		++no_mapping;
		++allow_keys;
		did_inc = TRUE;
	    }
	    c = vgetorpeek(TRUE);
	    if (did_inc)
	    {
		--no_mapping;
		--allow_keys;
	    }


	    if (c == K_SPECIAL
#ifdef FEAT_GUI
		    || (c == CSI)
#endif
	       )
	    {
		int	    save_allow_keys = allow_keys;

		++no_mapping;
		allow_keys = 0;
		c2 = vgetorpeek(TRUE);
		c = vgetorpeek(TRUE);
		--no_mapping;
		allow_keys = save_allow_keys;
		if (c2 == KS_MODIFIER)
		{
		    mod_mask = c;
		    continue;
		}
		c = TO_SPECIAL(c2, c);

#if defined(FEAT_GUI_MSWIN) && defined(FEAT_MENU) && defined(FEAT_TEAROFF)


		if (
# ifdef VIMDLL
		    gui.in_use &&
# endif
		    c == K_TEAROFF)
		{
		    char_u	name[200];
		    int		i;


		    for (i = 0; (c = vgetorpeek(TRUE)) != '\r'; )
		    {
			name[i] = c;
			if (i < 199)
			    ++i;
		    }
		    name[i] = NUL;
		    gui_make_tearoff(name);
		    continue;
		}
#endif
#if defined(FEAT_GUI) && defined(FEAT_GUI_GTK) && defined(FEAT_MENU)


		if (c == K_F10 && gui.menubar != NULL)
		{
		    gtk_menu_shell_select_first(
					   GTK_MENU_SHELL(gui.menubar), FALSE);
		    continue;
		}
#endif
#ifdef FEAT_GUI


		if (c == K_FOCUSGAINED || c == K_FOCUSLOST)
		{
		    ui_focus_change(c == K_FOCUSGAINED);
		    c = K_IGNORE;
		}


		if (c == K_CSI)
		    c = CSI;
#endif
	    }


	    switch (c)
	    {
		case K_KPLUS:	c = '+'; break;
		case K_KMINUS:	c = '-'; break;
		case K_KDIVIDE:	c = '/'; break;
		case K_KMULTIPLY: c = '*'; break;
		case K_KENTER:	c = CAR; break;
		case K_KPOINT:
#ifdef MSWIN


				c = MapVirtualKey(VK_DECIMAL, 2); break;
#else
				c = '.'; break;
#endif
		case K_K0:	c = '0'; break;
		case K_K1:	c = '1'; break;
		case K_K2:	c = '2'; break;
		case K_K3:	c = '3'; break;
		case K_K4:	c = '4'; break;
		case K_K5:	c = '5'; break;
		case K_K6:	c = '6'; break;
		case K_K7:	c = '7'; break;
		case K_K8:	c = '8'; break;
		case K_K9:	c = '9'; break;

		case K_XHOME:
		case K_ZHOME:	if (mod_mask == MOD_MASK_SHIFT)
				{
				    c = K_S_HOME;
				    mod_mask = 0;
				}
				else if (mod_mask == MOD_MASK_CTRL)
				{
				    c = K_C_HOME;
				    mod_mask = 0;
				}
				else
				    c = K_HOME;
				break;
		case K_XEND:
		case K_ZEND:	if (mod_mask == MOD_MASK_SHIFT)
				{
				    c = K_S_END;
				    mod_mask = 0;
				}
				else if (mod_mask == MOD_MASK_CTRL)
				{
				    c = K_C_END;
				    mod_mask = 0;
				}
				else
				    c = K_END;
				break;

		case K_XUP:	c = K_UP; break;
		case K_XDOWN:	c = K_DOWN; break;
		case K_XLEFT:	c = K_LEFT; break;
		case K_XRIGHT:	c = K_RIGHT; break;
	    }


	    if (has_mbyte && (n = MB_BYTE2LEN_CHECK(c)) > 1)
	    {
		++no_mapping;
		buf[0] = c;
		for (i = 1; i < n; ++i)
		{
		    buf[i] = vgetorpeek(TRUE);
		    if (buf[i] == K_SPECIAL
#ifdef FEAT_GUI
			    || (buf[i] == CSI)
#endif
			    )
		    {


			c = vgetorpeek(TRUE);
			if (vgetorpeek(TRUE) == KE_CSI && c == KS_EXTRA)
			    buf[i] = CSI;
		    }
		}
		--no_mapping;
		c = (*mb_ptr2char)(buf);
	    }

	    if (vgetc_char == 0)
	    {
		vgetc_mod_mask = mod_mask;
		vgetc_char = c;
	    }

	    break;
	}
    }

#ifdef FEAT_EVAL


    may_garbage_collect = FALSE;
#endif

#ifdef FEAT_BEVAL_TERM
    if (c != K_MOUSEMOVE && c != K_IGNORE && c != K_CURSORHOLD)
    {

	bevalexpr_due_set = FALSE;
	ui_remove_balloon();
    }
#endif
#ifdef FEAT_PROP_POPUP


    if ((!ex_normal_busy || in_feedkeys) && popup_do_filter(c))
    {
	if (c == Ctrl_C)
	    got_int = FALSE;
	c = K_IGNORE;
    }
#endif


    if (c != K_IGNORE)
	state_no_longer_safe("key typed");

    return c;
}
