write_vim_spell(spellinfo_T *spin, char_u *fname)
{
    FILE	*fd;
    int		regionmask;
    int		round;
    wordnode_T	*tree;
    int		nodecount;
    int		i;
    int		l;
    garray_T	*gap;
    fromto_T	*ftp;
    char_u	*p;
    int		rr;
    int		retval = OK;
    size_t	fwv = 1;


    fd = mch_fopen((char *)fname, "w");
    if (fd == NULL)
    {
	EMSG2(_(e_notopen), fname);
	return FAIL;
    }


    fwv &= fwrite(VIMSPELLMAGIC, VIMSPELLMAGICL, (size_t)1, fd);
    if (fwv != (size_t)1)

	goto theend;

    putc(VIMSPELLVERSION, fd);


    if (spin->si_info != NULL)
    {
	putc(SN_INFO, fd);
	putc(0, fd);

	i = (int)STRLEN(spin->si_info);
	put_bytes(fd, (long_u)i, 4);
	fwv &= fwrite(spin->si_info, (size_t)i, (size_t)1, fd);
    }


    if (spin->si_region_count > 1)
    {
	putc(SN_REGION, fd);
	putc(SNF_REQUIRED, fd);
	l = spin->si_region_count * 2;
	put_bytes(fd, (long_u)l, 4);
	fwv &= fwrite(spin->si_region_name, (size_t)l, (size_t)1, fd);

	regionmask = (1 << spin->si_region_count) - 1;
    }
    else
	regionmask = 0;


    if (!spin->si_ascii && !spin->si_add)
    {
	char_u	folchars[128 * 8];
	int	flags;

	putc(SN_CHARFLAGS, fd);
	putc(SNF_REQUIRED, fd);


	l = 0;
	for (i = 128; i < 256; ++i)
	{
#ifdef FEAT_MBYTE
	    if (has_mbyte)
		l += mb_char2bytes(spelltab.st_fold[i], folchars + l);
	    else
#endif
		folchars[l++] = spelltab.st_fold[i];
	}
	put_bytes(fd, (long_u)(1 + 128 + 2 + l), 4);

	fputc(128, fd);
	for (i = 128; i < 256; ++i)
	{
	    flags = 0;
	    if (spelltab.st_isw[i])
		flags |= CF_WORD;
	    if (spelltab.st_isu[i])
		flags |= CF_UPPER;
	    fputc(flags, fd);
	}

	put_bytes(fd, (long_u)l, 2);
	fwv &= fwrite(folchars, (size_t)l, (size_t)1, fd);
    }


    if (spin->si_midword != NULL)
    {
	putc(SN_MIDWORD, fd);
	putc(SNF_REQUIRED, fd);

	i = (int)STRLEN(spin->si_midword);
	put_bytes(fd, (long_u)i, 4);
	fwv &= fwrite(spin->si_midword, (size_t)i, (size_t)1, fd);

    }


    if (spin->si_prefcond.ga_len > 0)
    {
	putc(SN_PREFCOND, fd);
	putc(SNF_REQUIRED, fd);

	l = write_spell_prefcond(NULL, &spin->si_prefcond);
	put_bytes(fd, (long_u)l, 4);

	write_spell_prefcond(fd, &spin->si_prefcond);
    }


    for (round = 1; round <= 3; ++round)
    {
	if (round == 1)
	    gap = &spin->si_rep;
	else if (round == 2)
	{

	    if (spin->si_sofofr != NULL && spin->si_sofoto != NULL)
		continue;
	    gap = &spin->si_sal;
	}
	else
	    gap = &spin->si_repsal;


	if (gap->ga_len == 0)
	    continue;


	if (round != 2)
	    qsort(gap->ga_data, (size_t)gap->ga_len,
					       sizeof(fromto_T), rep_compare);

	i = round == 1 ? SN_REP : (round == 2 ? SN_SAL : SN_REPSAL);
	putc(i, fd);


	putc(0, fd);


	l = 2;
	for (i = 0; i < gap->ga_len; ++i)
	{
	    ftp = &((fromto_T *)gap->ga_data)[i];
	    l += 1 + (int)STRLEN(ftp->ft_from);
	    l += 1 + (int)STRLEN(ftp->ft_to);
	}
	if (round == 2)
	    ++l;
	put_bytes(fd, (long_u)l, 4);

	if (round == 2)
	{
	    i = 0;
	    if (spin->si_followup)
		i |= SAL_F0LLOWUP;
	    if (spin->si_collapse)
		i |= SAL_COLLAPSE;
	    if (spin->si_rem_accents)
		i |= SAL_REM_ACCENTS;
	    putc(i, fd);
	}

	put_bytes(fd, (long_u)gap->ga_len, 2);
	for (i = 0; i < gap->ga_len; ++i)
	{


	    ftp = &((fromto_T *)gap->ga_data)[i];
	    for (rr = 1; rr <= 2; ++rr)
	    {
		p = rr == 1 ? ftp->ft_from : ftp->ft_to;
		l = (int)STRLEN(p);
		putc(l, fd);
		if (l > 0)
		    fwv &= fwrite(p, l, (size_t)1, fd);
	    }
	}

    }


    if (spin->si_sofofr != NULL && spin->si_sofoto != NULL)
    {
	putc(SN_SOFO, fd);
	putc(0, fd);

	l = (int)STRLEN(spin->si_sofofr);
	put_bytes(fd, (long_u)(l + STRLEN(spin->si_sofoto) + 4), 4);


	put_bytes(fd, (long_u)l, 2);
	fwv &= fwrite(spin->si_sofofr, l, (size_t)1, fd);

	l = (int)STRLEN(spin->si_sofoto);
	put_bytes(fd, (long_u)l, 2);
	fwv &= fwrite(spin->si_sofoto, l, (size_t)1, fd);
    }


    if (spin->si_commonwords.ht_used > 0)
    {
	putc(SN_WORDS, fd);
	putc(0, fd);


	for (round = 1; round <= 2; ++round)
	{
	    int		todo;
	    int		len = 0;
	    hashitem_T	*hi;

	    todo = (int)spin->si_commonwords.ht_used;
	    for (hi = spin->si_commonwords.ht_array; todo > 0; ++hi)
		if (!HASHITEM_EMPTY(hi))
		{
		    l = (int)STRLEN(hi->hi_key) + 1;
		    len += l;
		    if (round == 2)
			fwv &= fwrite(hi->hi_key, (size_t)l, (size_t)1, fd);
		    --todo;
		}
	    if (round == 1)
		put_bytes(fd, (long_u)len, 4);
	}
    }


    if (spin->si_map.ga_len > 0)
    {
	putc(SN_MAP, fd);
	putc(0, fd);
	l = spin->si_map.ga_len;
	put_bytes(fd, (long_u)l, 4);
	fwv &= fwrite(spin->si_map.ga_data, (size_t)l, (size_t)1, fd);

    }


    if (!spin->si_nosugfile
	    && (spin->si_sal.ga_len > 0
		     || (spin->si_sofofr != NULL && spin->si_sofoto != NULL)))
    {
	putc(SN_SUGFILE, fd);
	putc(0, fd);
	put_bytes(fd, (long_u)8, 4);


	spin->si_sugtime = time(NULL);
	put_time(fd, spin->si_sugtime);
    }


    if (spin->si_nosplitsugs)
    {
	putc(SN_NOSPLITSUGS, fd);
	putc(0, fd);
	put_bytes(fd, (long_u)0, 4);
    }


    if (spin->si_nocompoundsugs)
    {
	putc(SN_NOCOMPOUNDSUGS, fd);
	putc(0, fd);
	put_bytes(fd, (long_u)0, 4);
    }


    if (spin->si_compflags != NULL)
    {
	putc(SN_COMPOUND, fd);
	putc(0, fd);

	l = (int)STRLEN(spin->si_compflags);
	for (i = 0; i < spin->si_comppat.ga_len; ++i)
	    l += (int)STRLEN(((char_u **)(spin->si_comppat.ga_data))[i]) + 1;
	put_bytes(fd, (long_u)(l + 7), 4);

	putc(spin->si_compmax, fd);
	putc(spin->si_compminlen, fd);
	putc(spin->si_compsylmax, fd);
	putc(0, fd);
	putc(spin->si_compoptions, fd);
	put_bytes(fd, (long_u)spin->si_comppat.ga_len, 2);

	for (i = 0; i < spin->si_comppat.ga_len; ++i)
	{
	    p = ((char_u **)(spin->si_comppat.ga_data))[i];
	    putc((int)STRLEN(p), fd);
	    fwv &= fwrite(p, (size_t)STRLEN(p), (size_t)1, fd);

	}

	fwv &= fwrite(spin->si_compflags, (size_t)STRLEN(spin->si_compflags),
							       (size_t)1, fd);
    }


    if (spin->si_nobreak)
    {
	putc(SN_NOBREAK, fd);
	putc(0, fd);


	put_bytes(fd, (long_u)0, 4);
    }


    if (spin->si_syllable != NULL)
    {
	putc(SN_SYLLABLE, fd);
	putc(0, fd);

	l = (int)STRLEN(spin->si_syllable);
	put_bytes(fd, (long_u)l, 4);
	fwv &= fwrite(spin->si_syllable, (size_t)l, (size_t)1, fd);

    }


    putc(SN_END, fd);


    spin->si_memtot = 0;
    for (round = 1; round <= 3; ++round)
    {
	if (round == 1)
	    tree = spin->si_foldroot->wn_sibling;
	else if (round == 2)
	    tree = spin->si_keeproot->wn_sibling;
	else
	    tree = spin->si_prefroot->wn_sibling;


	clear_node(tree);


	nodecount = put_node(NULL, tree, 0, regionmask, round == 3);


	put_bytes(fd, (long_u)nodecount, 4);
	spin->si_memtot += nodecount + nodecount * sizeof(int);


	(void)put_node(fd, tree, 0, regionmask, round == 3);
    }


    if (putc(0, fd) == EOF)
	retval = FAIL;
theend:
    if (fclose(fd) == EOF)
	retval = FAIL;

    if (fwv != (size_t)1)
	retval = FAIL;
    if (retval == FAIL)
	EMSG(_(e_write));

    return retval;
}
