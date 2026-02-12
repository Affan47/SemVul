cmdline_handle_backslash_key(int c, int *gotesc)
{
    ++no_mapping;
    ++allow_keys;
    c = plain_vgetc();
    --no_mapping;
    --allow_keys;


    if (c != Ctrl_N && c != Ctrl_G && (c != 'e'
		|| (ccline.cmdfirstc == '=' && KeyTyped)
#ifdef FEAT_EVAL
		|| cmdline_star > 0
#endif
		))
    {
	vungetc(c);
	return PROCESS_NEXT_KEY;
    }

#ifdef FEAT_EVAL
    if (c == 'e')
    {
	char_u	*p = NULL;
	int	len;


	if (ccline.cmdpos == ccline.cmdlen)
	    new_cmdpos = 99999;
	else
	    new_cmdpos = ccline.cmdpos;

	c = get_expr_register();
	if (c == '=')
	{


	    ++textwinlock;
	    p = get_expr_line();
	    --textwinlock;

	    if (p != NULL)
	    {
		len = (int)STRLEN(p);
		if (realloc_cmdbuff(len + 1) == OK)
		{
		    ccline.cmdlen = len;
		    STRCPY(ccline.cmdbuff, p);
		    vim_free(p);


		    if (new_cmdpos > ccline.cmdlen)
			ccline.cmdpos = ccline.cmdlen;
		    else
			ccline.cmdpos = new_cmdpos;

		    KeyTyped = FALSE;
		    redrawcmd();
		    return CMDLINE_CHANGED;
		}
		vim_free(p);
	    }
	}
	beep_flush();
	got_int = FALSE;
	did_emsg = FALSE;
	emsg_on_display = FALSE;
	redrawcmd();
	return CMDLINE_NOT_CHANGED;
    }
#endif

    if (c == Ctrl_G && p_im && restart_edit == 0)
	restart_edit = 'a';
    *gotesc = TRUE;

    return GOTO_NORMAL_MODE;
}
