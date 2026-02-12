do_map(
    int		maptype,
    char_u	*arg,
    int		mode,
    int		abbrev)
{
    char_u	*keys;
    mapblock_T	*mp, **mpp;
    char_u	*rhs;
    char_u	*p;
    int		n;
    int		len = 0;
    char_u	*newstr;
    int		hasarg;
    int		haskey;
    int		did_it = FALSE;
#ifdef FEAT_LOCALMAP
    int		did_local = FALSE;
#endif
    int		round;
    char_u	*keys_buf = NULL;
    char_u	*arg_buf = NULL;
    int		retval = 0;
    int		do_backslash;
    int		hash;
    int		new_hash;
    mapblock_T	**abbr_table;
    mapblock_T	**map_table;
    int		unique = FALSE;
    int		nowait = FALSE;
    int		silent = FALSE;
    int		special = FALSE;
#ifdef FEAT_EVAL
    int		expr = FALSE;
#endif
    int		noremap;
    char_u      *orig_rhs;

    keys = arg;
    map_table = maphash;
    abbr_table = &first_abbr;


    if (maptype == 2)
	noremap = REMAP_NONE;
    else
	noremap = REMAP_YES;


    for (;;)
    {
#ifdef FEAT_LOCALMAP


	if (STRNCMP(keys, "<buffer>", 8) == 0)
	{
	    keys = skipwhite(keys + 8);
	    map_table = curbuf->b_maphash;
	    abbr_table = &curbuf->b_first_abbr;
	    continue;
	}
#endif


	if (STRNCMP(keys, "<nowait>", 8) == 0)
	{
	    keys = skipwhite(keys + 8);
	    nowait = TRUE;
	    continue;
	}


	if (STRNCMP(keys, "<silent>", 8) == 0)
	{
	    keys = skipwhite(keys + 8);
	    silent = TRUE;
	    continue;
	}


	if (STRNCMP(keys, "<special>", 9) == 0)
	{
	    keys = skipwhite(keys + 9);
	    special = TRUE;
	    continue;
	}

#ifdef FEAT_EVAL


	if (STRNCMP(keys, "<script>", 8) == 0)
	{
	    keys = skipwhite(keys + 8);
	    noremap = REMAP_SCRIPT;
	    continue;
	}


	if (STRNCMP(keys, "<expr>", 6) == 0)
	{
	    keys = skipwhite(keys + 6);
	    expr = TRUE;
	    continue;
	}
#endif


	if (STRNCMP(keys, "<unique>", 8) == 0)
	{
	    keys = skipwhite(keys + 8);
	    unique = TRUE;
	    continue;
	}
	break;
    }

    validate_maphash();


    p = keys;
    do_backslash = (vim_strchr(p_cpo, CPO_BSLASH) == NULL);
    while (*p && (maptype == 1 || !VIM_ISWHITE(*p)))
    {
	if ((p[0] == Ctrl_V || (do_backslash && p[0] == '\\')) &&
								  p[1] != NUL)
	    ++p;
	++p;
    }
    if (*p != NUL)
	*p++ = NUL;

    p = skipwhite(p);
    rhs = p;
    hasarg = (*rhs != NUL);
    haskey = (*keys != NUL);


    if (maptype == 1 && !haskey)
    {
	retval = 1;
	goto theend;
    }


    if (haskey)
	keys = replace_termcodes(keys, &keys_buf, TRUE, TRUE, special);
    orig_rhs = rhs;
    if (hasarg)
    {
	if (STRICMP(rhs, "<nop>") == 0)
	    rhs = (char_u *)"";
	else
	    rhs = replace_termcodes(rhs, &arg_buf, FALSE, TRUE, special);
    }


    if (haskey)
    {
	len = (int)STRLEN(keys);
	if (len > MAXMAPLEN)
	{
	    retval = 1;
	    goto theend;
	}

	if (abbrev && maptype != 1)
	{


	    if (has_mbyte)
	    {
		int	first, last;
		int	same = -1;

		first = vim_iswordp(keys);
		last = first;
		p = keys + (*mb_ptr2len)(keys);
		n = 1;
		while (p < keys + len)
		{
		    ++n;
		    last = vim_iswordp(p);
		    if (same == -1 && last != first)
			same = n - 1;
		    p += (*mb_ptr2len)(p);
		}
		if (last && n > 2 && same >= 0 && same < n - 1)
		{
		    retval = 1;
		    goto theend;
		}
	    }
	    else if (vim_iswordc(keys[len - 1]))
		    for (n = 0; n < len - 2; ++n)
			if (vim_iswordc(keys[n]) != vim_iswordc(keys[len - 2]))
			{
			    retval = 1;
			    goto theend;
			}

	    for (n = 0; n < len; ++n)
		if (VIM_ISWHITE(keys[n]))
		{
		    retval = 1;
		    goto theend;
		}
	}
    }

    if (haskey && hasarg && abbrev)
	no_abbr = FALSE;


    if (!haskey || (maptype != 1 && !hasarg))
	msg_start();

#ifdef FEAT_LOCALMAP


    if (map_table == curbuf->b_maphash && haskey && hasarg && maptype != 1)
    {

	for (hash = 0; hash < 256 && !got_int; ++hash)
	{
	    if (abbrev)
	    {
		if (hash != 0)
		    break;
		mp = first_abbr;
	    }
	    else
		mp = maphash[hash];
	    for ( ; mp != NULL && !got_int; mp = mp->m_next)
	    {

		if ((mp->m_mode & mode) != 0
			&& mp->m_keylen == len
			&& unique
			&& STRNCMP(mp->m_keys, keys, (size_t)len) == 0)
		{
		    if (abbrev)
			semsg(_("E224: global abbreviation already exists for %s"),
				mp->m_keys);
		    else
			semsg(_("E225: global mapping already exists for %s"),
				mp->m_keys);
		    retval = 5;
		    goto theend;
		}
	    }
	}
    }


    if (map_table != curbuf->b_maphash && !hasarg && maptype != 1)
    {

	for (hash = 0; hash < 256 && !got_int; ++hash)
	{
	    if (abbrev)
	    {
		if (hash != 0)
		    break;
		mp = curbuf->b_first_abbr;
	    }
	    else
		mp = curbuf->b_maphash[hash];
	    for ( ; mp != NULL && !got_int; mp = mp->m_next)
	    {

		if ((mp->m_mode & mode) != 0)
		{
		    if (!haskey)
		    {
			showmap(mp, TRUE);
			did_local = TRUE;
		    }
		    else
		    {
			n = mp->m_keylen;
			if (STRNCMP(mp->m_keys, keys,
					    (size_t)(n < len ? n : len)) == 0)
			{
			    showmap(mp, TRUE);
			    did_local = TRUE;
			}
		    }
		}
	    }
	}
    }
#endif


    for (round = 0; (round == 0 || maptype == 1) && round <= 1
					      && !did_it && !got_int; ++round)
    {

	for (hash = 0; hash < 256 && !got_int; ++hash)
	{
	    if (abbrev)
	    {
		if (hash > 0)
		    break;
		mpp = abbr_table;
	    }
	    else
		mpp = &(map_table[hash]);
	    for (mp = *mpp; mp != NULL && !got_int; mp = *mpp)
	    {

		if (!(mp->m_mode & mode))
		{
		    mpp = &(mp->m_next);
		    continue;
		}
		if (!haskey)
		{
		    showmap(mp, map_table != maphash);
		    did_it = TRUE;
		}
		else
		{
		    if (round)
		    {
			n = (int)STRLEN(mp->m_str);
			p = mp->m_str;
		    }
		    else
		    {
			n = mp->m_keylen;
			p = mp->m_keys;
		    }
		    if (STRNCMP(p, keys, (size_t)(n < len ? n : len)) == 0)
		    {
			if (maptype == 1)
			{


			    if (n != len && (!abbrev || round || n > len
					       || *skipwhite(keys + n) != NUL))
			    {
				mpp = &(mp->m_next);
				continue;
			    }


			    mp->m_mode &= ~mode;
			    did_it = TRUE;
			}
			else if (!hasarg)
			{
			    showmap(mp, map_table != maphash);
			    did_it = TRUE;
			}
			else if (n != len)
			{
			    mpp = &(mp->m_next);
			    continue;
			}
			else if (unique)
			{
			    if (abbrev)
				semsg(_("E226: abbreviation already exists for %s"),
									   p);
			    else
				semsg(_("E227: mapping already exists for %s"), p);
			    retval = 5;
			    goto theend;
			}
			else
			{
			    mp->m_mode &= ~mode;
			    if (mp->m_mode == 0 && !did_it)
			    {
				newstr = vim_strsave(rhs);
				if (newstr == NULL)
				{
				    retval = 4;
				    goto theend;
				}
				vim_free(mp->m_str);
				mp->m_str = newstr;
				vim_free(mp->m_orig_str);
				mp->m_orig_str = vim_strsave(orig_rhs);
				mp->m_noremap = noremap;
				mp->m_nowait = nowait;
				mp->m_silent = silent;
				mp->m_mode = mode;
#ifdef FEAT_EVAL
				mp->m_expr = expr;
				mp->m_script_ctx = current_sctx;
				mp->m_script_ctx.sc_lnum += sourcing_lnum;
#endif
				did_it = TRUE;
			    }
			}
			if (mp->m_mode == 0)
			{
			    map_free(mpp);
			    continue;
			}


			new_hash = MAP_HASH(mp->m_mode, mp->m_keys[0]);
			if (!abbrev && new_hash != hash)
			{
			    *mpp = mp->m_next;
			    mp->m_next = map_table[new_hash];
			    map_table[new_hash] = mp;

			    continue;
			}
		    }
		}
		mpp = &(mp->m_next);
	    }
	}
    }

    if (maptype == 1)
    {
	if (!did_it)
	    retval = 2;
	else if (*keys == Ctrl_C)
	{

#ifdef FEAT_LOCALMAP
	    if (map_table == curbuf->b_maphash)
		curbuf->b_mapped_ctrl_c &= ~mode;
	    else
#endif
		mapped_ctrl_c &= ~mode;
	}
	goto theend;
    }

    if (!haskey || !hasarg)
    {
	if (!did_it
#ifdef FEAT_LOCALMAP
		&& !did_local
#endif
		)
	{
	    if (abbrev)
		msg(_("No abbreviation found"));
	    else
		msg(_("No mapping found"));
	}
	goto theend;
    }

    if (did_it)
	goto theend;


    mp = (mapblock_T *)alloc((unsigned)sizeof(mapblock_T));
    if (mp == NULL)
    {
	retval = 4;
	goto theend;
    }


    if (*keys == Ctrl_C)
    {
#ifdef FEAT_LOCALMAP
	if (map_table == curbuf->b_maphash)
	    curbuf->b_mapped_ctrl_c |= mode;
	else
#endif
	    mapped_ctrl_c |= mode;
    }

    mp->m_keys = vim_strsave(keys);
    mp->m_str = vim_strsave(rhs);
    mp->m_orig_str = vim_strsave(orig_rhs);
    if (mp->m_keys == NULL || mp->m_str == NULL)
    {
	vim_free(mp->m_keys);
	vim_free(mp->m_str);
	vim_free(mp->m_orig_str);
	vim_free(mp);
	retval = 4;
	goto theend;
    }
    mp->m_keylen = (int)STRLEN(mp->m_keys);
    mp->m_noremap = noremap;
    mp->m_nowait = nowait;
    mp->m_silent = silent;
    mp->m_mode = mode;
#ifdef FEAT_EVAL
    mp->m_expr = expr;
    mp->m_script_ctx = current_sctx;
    mp->m_script_ctx.sc_lnum += sourcing_lnum;
#endif


    if (abbrev)
    {
	mp->m_next = *abbr_table;
	*abbr_table = mp;
    }
    else
    {
	n = MAP_HASH(mp->m_mode, mp->m_keys[0]);
	mp->m_next = map_table[n];
	map_table[n] = mp;
    }

theend:
    vim_free(keys_buf);
    vim_free(arg_buf);
    return retval;
}
