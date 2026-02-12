get_literal(int noReduceKeys)
{
    int		cc;
    int		nc;
    int		i;
    int		hex = FALSE;
    int		octal = FALSE;
    int		unicode = 0;

    if (got_int)
	return Ctrl_C;

#ifdef FEAT_GUI


    if (gui.in_use)
	++allow_keys;
#endif
#ifdef USE_ON_FLY_SCROLL
    dont_scroll = TRUE;
#endif
    ++no_mapping;
    cc = 0;
    i = 0;
    for (;;)
    {
	nc = plain_vgetc();
	if ((nc == ESC || nc == CSI) && !noReduceKeys)
	    nc = decodeModifyOtherKeys(nc);

	if ((mod_mask & ~MOD_MASK_SHIFT) != 0)


	    break;

#ifdef FEAT_CMDL_INFO
	if (!(State & CMDLINE) && MB_BYTE2LEN_CHECK(nc) == 1)
	    add_to_showcmd(nc);
#endif
	if (nc == 'x' || nc == 'X')
	    hex = TRUE;
	else if (nc == 'o' || nc == 'O')
	    octal = TRUE;
	else if (nc == 'u' || nc == 'U')
	    unicode = nc;
	else
	{
	    if (hex || unicode != 0)
	    {
		if (!vim_isxdigit(nc))
		    break;
		cc = cc * 16 + hex2nr(nc);
	    }
	    else if (octal)
	    {
		if (nc < '0' || nc > '7')
		    break;
		cc = cc * 8 + nc - '0';
	    }
	    else
	    {
		if (!VIM_ISDIGIT(nc))
		    break;
		cc = cc * 10 + nc - '0';
	    }

	    ++i;
	}

	if (cc > 255 && unicode == 0)
	    cc = 255;
	nc = 0;

	if (hex)
	{
	    if (i >= 2)
		break;
	}
	else if (unicode)
	{
	    if ((unicode == 'u' && i >= 4) || (unicode == 'U' && i >= 8))
		break;
	}
	else if (i >= 3)
	    break;
    }
    if (i == 0)
    {
	if (nc == K_ZERO)
	{
	    cc = '\n';
	    nc = 0;
	}
	else
	{
	    cc = nc;
	    nc = 0;
	}
    }

    if (cc == 0)
	cc = '\n';
    if (enc_dbcs && (cc & 0xff) == 0)
	cc = '?';


    --no_mapping;
#ifdef FEAT_GUI
    if (gui.in_use)
	--allow_keys;
#endif
    if (nc)
    {
	vungetc(nc);

	mod_mask = 0;
    }
    got_int = FALSE;
    return cc;
}
