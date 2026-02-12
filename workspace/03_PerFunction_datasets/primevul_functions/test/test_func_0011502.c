normal_cmd_get_more_chars(
	int	    idx_arg,
	cmdarg_T    *cap,
	int	    *need_flushbuf UNUSED)
{
    int		idx = idx_arg;
    int		c;
    int		*cp;
    int		repl = FALSE;
    int		lit = FALSE;
    int		langmap_active = FALSE;
    int		lang;
#ifdef HAVE_INPUT_METHOD
    int		save_smd;
#endif

    ++no_mapping;
    ++allow_keys;


    did_cursorhold = TRUE;
    if (cap->cmdchar == 'g')
    {


	cap->nchar = plain_vgetc();
	LANGMAP_ADJUST(cap->nchar, TRUE);
#ifdef FEAT_CMDL_INFO
	*need_flushbuf |= add_to_showcmd(cap->nchar);
#endif
	if (cap->nchar == 'r' || cap->nchar == '\'' || cap->nchar == '`'
		|| cap->nchar == Ctrl_BSL)
	{
	    cp = &cap->extra_char;
	    if (cap->nchar != 'r')
		lit = TRUE;
	    else
		repl = TRUE;
	}
	else
	    cp = NULL;
    }
    else
    {
	if (cap->cmdchar == 'r')
	    repl = TRUE;
	cp = &cap->nchar;
    }
    lang = (repl || (nv_cmds[idx].cmd_flags & NV_LANG));


    if (cp != NULL)
    {
	if (repl)
	{
	    State = MODE_REPLACE;
#ifdef CURSOR_SHAPE
	    ui_cursor_shape();
#endif
	}
	if (lang && curbuf->b_p_iminsert == B_IMODE_LMAP)
	{

	    --no_mapping;
	    --allow_keys;
	    if (repl)
		State = MODE_LREPLACE;
	    else
		State = MODE_LANGMAP;
	    langmap_active = TRUE;
	}
#ifdef HAVE_INPUT_METHOD
	save_smd = p_smd;
	p_smd = FALSE;
	if (lang && curbuf->b_p_iminsert == B_IMODE_IM)
	    im_set_active(TRUE);
#endif
	if ((State & MODE_INSERT) && !p_ek)
	{
#ifdef FEAT_JOB_CHANNEL
	    ch_log_output = TRUE;
#endif


	    out_str(T_BD);
	    out_str(T_CTE);
	}

	*cp = plain_vgetc();

	if ((State & MODE_INSERT) && !p_ek)
	{
#ifdef FEAT_JOB_CHANNEL
	    ch_log_output = TRUE;
#endif

	    out_str(T_BE);
	    out_str(T_CTI);
	}

	if (langmap_active)
	{

	    ++no_mapping;
	    ++allow_keys;
	    State = MODE_NORMAL_BUSY;
	}
#ifdef HAVE_INPUT_METHOD
	if (lang)
	{
	    if (curbuf->b_p_iminsert != B_IMODE_LMAP)
		im_save_status(&curbuf->b_p_iminsert);
	    im_set_active(FALSE);
	}
	p_smd = save_smd;
#endif
	State = MODE_NORMAL_BUSY;
#ifdef FEAT_CMDL_INFO
	*need_flushbuf |= add_to_showcmd(*cp);
#endif

	if (!lit)
	{
#ifdef FEAT_DIGRAPHS

	    if (*cp == Ctrl_K
		    && ((nv_cmds[idx].cmd_flags & NV_LANG)
			|| cp == &cap->extra_char)
		    && vim_strchr(p_cpo, CPO_DIGRAPH) == NULL)
	    {
		c = get_digraph(FALSE);
		if (c > 0)
		{
		    *cp = c;
# ifdef FEAT_CMDL_INFO

		    del_from_showcmd(3);
		    *need_flushbuf |= add_to_showcmd(*cp);
# endif
		}
	    }
#endif


	    LANGMAP_ADJUST(*cp, !lang);
#ifdef FEAT_RIGHTLEFT

	    if (p_hkmap && lang && KeyTyped)
		*cp = hkmap(*cp);
#endif
	}


	if (cp == &cap->extra_char
		&& cap->nchar == Ctrl_BSL
		&& (cap->extra_char == Ctrl_N || cap->extra_char == Ctrl_G))
	{
	    cap->cmdchar = Ctrl_BSL;
	    cap->nchar = cap->extra_char;
	    idx = find_command(cap->cmdchar);
	}
	else if ((cap->nchar == 'n' || cap->nchar == 'N') && cap->cmdchar == 'g')
	    cap->oap->op_type = get_op_type(*cp, NUL);
	else if (*cp == Ctrl_BSL)
	{
	    long towait = (p_ttm >= 0 ? p_ttm : p_tm);


	    while ((c = vpeekc()) <= 0 && towait > 0L)
	    {
		do_sleep(towait > 50L ? 50L : towait, FALSE);
		towait -= 50L;
	    }
	    if (c > 0)
	    {
		c = plain_vgetc();
		if (c != Ctrl_N && c != Ctrl_G)
		    vungetc(c);
		else
		{
		    cap->cmdchar = Ctrl_BSL;
		    cap->nchar = c;
		    idx = find_command(cap->cmdchar);
		}
	    }
	}


	--no_mapping;
	while (enc_utf8 && lang && (c = vpeekc()) > 0
		&& (c >= 0x100 || MB_BYTE2LEN(vpeekc()) > 1))
	{
	    c = plain_vgetc();
	    if (!utf_iscomposing(c))
	    {
		vungetc(c);
		break;
	    }
	    else if (cap->ncharC1 == 0)
		cap->ncharC1 = c;
	    else
		cap->ncharC2 = c;
	}
	++no_mapping;
    }
    --no_mapping;
    --allow_keys;

    return idx;
}
