ins_typebuf(
    char_u	*str,
    int		noremap,
    int		offset,
    int		nottyped,
    int		silent)
{
    char_u	*s1, *s2;
    int		newlen;
    int		addlen;
    int		i;
    int		newoff;
    int		val;
    int		nrm;

    init_typebuf();
    if (++typebuf.tb_change_cnt == 0)
	typebuf.tb_change_cnt = 1;

    addlen = (int)STRLEN(str);

    if (offset == 0 && addlen <= typebuf.tb_off)
    {


	typebuf.tb_off -= addlen;
	mch_memmove(typebuf.tb_buf + typebuf.tb_off, str, (size_t)addlen);
    }
    else if (typebuf.tb_len == 0 && typebuf.tb_buflen
					       >= addlen + 3 * (MAXMAPLEN + 4))
    {


	typebuf.tb_off = (typebuf.tb_buflen - addlen - 3 * (MAXMAPLEN + 4)) / 2;
	mch_memmove(typebuf.tb_buf + typebuf.tb_off, str, (size_t)addlen);
    }
    else
    {


	newoff = MAXMAPLEN + 4;
	newlen = typebuf.tb_len + addlen + newoff + 4 * (MAXMAPLEN + 4);
	if (newlen < 0)
	{
	    emsg(_(e_toocompl));
	    setcursor();
	    return FAIL;
	}
	s1 = alloc(newlen);
	if (s1 == NULL)
	    return FAIL;
	s2 = alloc(newlen);
	if (s2 == NULL)
	{
	    vim_free(s1);
	    return FAIL;
	}
	typebuf.tb_buflen = newlen;


	mch_memmove(s1 + newoff, typebuf.tb_buf + typebuf.tb_off,
							      (size_t)offset);

	mch_memmove(s1 + newoff + offset, str, (size_t)addlen);


	mch_memmove(s1 + newoff + offset + addlen,
				     typebuf.tb_buf + typebuf.tb_off + offset,
				       (size_t)(typebuf.tb_len - offset + 1));
	if (typebuf.tb_buf != typebuf_init)
	    vim_free(typebuf.tb_buf);
	typebuf.tb_buf = s1;

	mch_memmove(s2 + newoff, typebuf.tb_noremap + typebuf.tb_off,
							      (size_t)offset);
	mch_memmove(s2 + newoff + offset + addlen,
		   typebuf.tb_noremap + typebuf.tb_off + offset,
					   (size_t)(typebuf.tb_len - offset));
	if (typebuf.tb_noremap != noremapbuf_init)
	    vim_free(typebuf.tb_noremap);
	typebuf.tb_noremap = s2;

	typebuf.tb_off = newoff;
    }
    typebuf.tb_len += addlen;


    if (noremap == REMAP_SCRIPT)
	val = RM_SCRIPT;
    else if (noremap == REMAP_SKIP)
	val = RM_ABBR;
    else
	val = RM_NONE;


    if (noremap == REMAP_SKIP)
	nrm = 1;
    else if (noremap < 0)
	nrm = addlen;
    else
	nrm = noremap;
    for (i = 0; i < addlen; ++i)
	typebuf.tb_noremap[typebuf.tb_off + i + offset] =
						  (--nrm >= 0) ? val : RM_YES;


    if (nottyped || typebuf.tb_maplen > offset)
	typebuf.tb_maplen += addlen;
    if (silent || typebuf.tb_silent > offset)
    {
	typebuf.tb_silent += addlen;
	cmd_silent = TRUE;
    }
    if (typebuf.tb_no_abbr_cnt && offset == 0)
	typebuf.tb_no_abbr_cnt += addlen;

    return OK;
}
