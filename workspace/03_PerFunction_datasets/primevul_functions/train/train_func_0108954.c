check_abbr(
    int		c,
    char_u	*ptr,
    int		col,
    int		mincol)
{
    int		len;
    int		scol;
    int		j;
    char_u	*s;
    char_u	tb[MB_MAXBYTES + 4];
    mapblock_T	*mp;
#ifdef FEAT_LOCALMAP
    mapblock_T	*mp2;
#endif
    int		clen = 0;
    int		is_id = TRUE;
    int		vim_abbr;

    if (typebuf.tb_no_abbr_cnt)
	return FALSE;


    if ((KeyNoremap & (RM_NONE|RM_SCRIPT)) != 0 && c != Ctrl_RSB)
	return FALSE;


    if (col == 0)
	return FALSE;

    if (has_mbyte)
    {
	char_u *p;

	p = mb_prevptr(ptr, ptr + col);
	if (!vim_iswordp(p))
	    vim_abbr = TRUE;
	else
	{
	    vim_abbr = FALSE;
	    if (p > ptr)
		is_id = vim_iswordp(mb_prevptr(ptr, p));
	}
	clen = 1;
	while (p > ptr + mincol)
	{
	    p = mb_prevptr(ptr, p);
	    if (vim_isspace(*p) || (!vim_abbr && is_id != vim_iswordp(p)))
	    {
		p += (*mb_ptr2len)(p);
		break;
	    }
	    ++clen;
	}
	scol = (int)(p - ptr);
    }
    else
    {
	if (!vim_iswordc(ptr[col - 1]))
	    vim_abbr = TRUE;
	else
	{
	    vim_abbr = FALSE;
	    if (col > 1)
		is_id = vim_iswordc(ptr[col - 2]);
	}
	for (scol = col - 1; scol > 0 && !vim_isspace(ptr[scol - 1])
		&& (vim_abbr || is_id == vim_iswordc(ptr[scol - 1])); --scol)
	    ;
    }

    if (scol < mincol)
	scol = mincol;
    if (scol < col)
    {
	ptr += scol;
	len = col - scol;
#ifdef FEAT_LOCALMAP
	mp = curbuf->b_first_abbr;
	mp2 = first_abbr;
	if (mp == NULL)
	{
	    mp = mp2;
	    mp2 = NULL;
	}
#else
	mp = first_abbr;
#endif
	for ( ; mp;
#ifdef FEAT_LOCALMAP
		mp->m_next == NULL ? (mp = mp2, mp2 = NULL) :
#endif
		(mp = mp->m_next))
	{
	    int		qlen = mp->m_keylen;
	    char_u	*q = mp->m_keys;
	    int		match;

	    if (vim_strbyte(mp->m_keys, K_SPECIAL) != NULL)
	    {
		char_u *qe = vim_strsave(mp->m_keys);


		if (qe != NULL)
		{
		    q = qe;
		    vim_unescape_csi(q);
		    qlen = (int)STRLEN(q);
		}
	    }


	    match =    (mp->m_mode & State)
		    && qlen == len
		    && !STRNCMP(q, ptr, (size_t)len);
	    if (q != mp->m_keys)
		vim_free(q);
	    if (match)
		break;
	}
	if (mp != NULL)
	{


	    j = 0;
	    if (c != Ctrl_RSB)
	    {

		if (IS_SPECIAL(c) || c == K_SPECIAL)
		{
		    tb[j++] = K_SPECIAL;
		    tb[j++] = K_SECOND(c);
		    tb[j++] = K_THIRD(c);
		}
		else
		{
		    if (c < ABBR_OFF && (c < ' ' || c > '~'))
			tb[j++] = Ctrl_V;
		    if (has_mbyte)
		    {

			if (c >= ABBR_OFF)
			    c -= ABBR_OFF;
			j += (*mb_char2bytes)(c, tb + j);
		    }
		    else
			tb[j++] = c;
		}
		tb[j] = NUL;

		(void)ins_typebuf(tb, 1, 0, TRUE, mp->m_silent);
	    }
#ifdef FEAT_EVAL
	    if (mp->m_expr)
		s = eval_map_expr(mp->m_str, c);
	    else
#endif
		s = mp->m_str;
	    if (s != NULL)
	    {

		(void)ins_typebuf(s, mp->m_noremap, 0, TRUE, mp->m_silent);

		typebuf.tb_no_abbr_cnt += (int)STRLEN(s) + j + 1;
#ifdef FEAT_EVAL
		if (mp->m_expr)
		    vim_free(s);
#endif
	    }

	    tb[0] = Ctrl_H;
	    tb[1] = NUL;
	    if (has_mbyte)
		len = clen;
	    while (len-- > 0)
		(void)ins_typebuf(tb, 1, 0, TRUE, mp->m_silent);
	    return TRUE;
	}
    }
    return FALSE;
}
