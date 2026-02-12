spell_read_aff(spellinfo_T *spin, char_u *fname)
{
    FILE	*fd;
    afffile_T	*aff;
    char_u	rline[MAXLINELEN];
    char_u	*line;
    char_u	*pc = NULL;
#define MAXITEMCNT  30
    char_u	*(items[MAXITEMCNT]);
    int		itemcnt;
    char_u	*p;
    int		lnum = 0;
    affheader_T	*cur_aff = NULL;
    int		did_postpone_prefix = FALSE;
    int		aff_todo = 0;
    hashtab_T	*tp;
    char_u	*low = NULL;
    char_u	*fol = NULL;
    char_u	*upp = NULL;
    int		do_rep;
    int		do_repsal;
    int		do_sal;
    int		do_mapline;
    int		found_map = FALSE;
    hashitem_T	*hi;
    int		l;
    int		compminlen = 0;
    int		compsylmax = 0;
    int		compoptions = 0;
    int		compmax = 0;
    char_u	*compflags = NULL;

    char_u	*midword = NULL;
    char_u	*syllable = NULL;
    char_u	*sofofrom = NULL;
    char_u	*sofoto = NULL;


    fd = mch_fopen((char *)fname, "r");
    if (fd == NULL)
    {
	EMSG2(_(e_notopen), fname);
	return NULL;
    }

    vim_snprintf((char *)IObuff, IOSIZE, _("Reading affix file %s ..."), fname);
    spell_message(spin, IObuff);


    do_rep = spin->si_rep.ga_len == 0;


    do_repsal = spin->si_repsal.ga_len == 0;


    do_sal = spin->si_sal.ga_len == 0;


    do_mapline = spin->si_map.ga_len == 0;


    aff = (afffile_T *)getroom(spin, sizeof(afffile_T), TRUE);
    if (aff == NULL)
    {
	fclose(fd);
	return NULL;
    }
    hash_init(&aff->af_pref);
    hash_init(&aff->af_suff);
    hash_init(&aff->af_comp);


    while (!vim_fgets(rline, MAXLINELEN, fd) && !got_int)
    {
	line_breakcheck();
	++lnum;


	if (*rline == '#')
	    continue;


	vim_free(pc);
#ifdef FEAT_MBYTE
	if (spin->si_conv.vc_type != CONV_NONE)
	{
	    pc = string_convert(&spin->si_conv, rline, NULL);
	    if (pc == NULL)
	    {
		smsg((char_u *)_("Conversion failure for word in %s line %d: %s"),
							   fname, lnum, rline);
		continue;
	    }
	    line = pc;
	}
	else
#endif
	{
	    pc = NULL;
	    line = rline;
	}


	itemcnt = 0;
	for (p = line; ; )
	{
	    while (*p != NUL && *p <= ' ')
		++p;
	    if (*p == NUL)
		break;
	    if (itemcnt == MAXITEMCNT)
		break;
	    items[itemcnt++] = p;

	    if (itemcnt == 2 && spell_info_item(items[0]))
		while (*p >= ' ' || *p == TAB)
		    ++p;
	    else
		while (*p > ' ')
		    ++p;
	    if (*p == NUL)
		break;
	    *p++ = NUL;
	}


	if (itemcnt > 0)
	{
	    if (is_aff_rule(items, itemcnt, "SET", 2) && aff->af_enc == NULL)
	    {
#ifdef FEAT_MBYTE

		aff->af_enc = enc_canonize(items[1]);
		if (aff->af_enc != NULL && !spin->si_ascii
			&& convert_setup(&spin->si_conv, aff->af_enc,
							       p_enc) == FAIL)
		    smsg((char_u *)_("Conversion in %s not supported: from %s to %s"),
					       fname, aff->af_enc, p_enc);
		spin->si_conv.vc_fail = TRUE;
#else
		    smsg((char_u *)_("Conversion in %s not supported"), fname);
#endif
	    }
	    else if (is_aff_rule(items, itemcnt, "FLAG", 2)
					      && aff->af_flagtype == AFT_CHAR)
	    {
		if (STRCMP(items[1], "long") == 0)
		    aff->af_flagtype = AFT_LONG;
		else if (STRCMP(items[1], "num") == 0)
		    aff->af_flagtype = AFT_NUM;
		else if (STRCMP(items[1], "caplong") == 0)
		    aff->af_flagtype = AFT_CAPLONG;
		else
		    smsg((char_u *)_("Invalid value for FLAG in %s line %d: %s"),
			    fname, lnum, items[1]);
		if (aff->af_rare != 0
			|| aff->af_keepcase != 0
			|| aff->af_bad != 0
			|| aff->af_needaffix != 0
			|| aff->af_circumfix != 0
			|| aff->af_needcomp != 0
			|| aff->af_comproot != 0
			|| aff->af_nosuggest != 0
			|| compflags != NULL
			|| aff->af_suff.ht_used > 0
			|| aff->af_pref.ht_used > 0)
		    smsg((char_u *)_("FLAG after using flags in %s line %d: %s"),
			    fname, lnum, items[1]);
	    }
	    else if (spell_info_item(items[0]))
	    {
		    p = (char_u *)getroom(spin,
			    (spin->si_info == NULL ? 0 : STRLEN(spin->si_info))
			    + STRLEN(items[0])
			    + STRLEN(items[1]) + 3, FALSE);
		    if (p != NULL)
		    {
			if (spin->si_info != NULL)
			{
			    STRCPY(p, spin->si_info);
			    STRCAT(p, "\n");
			}
			STRCAT(p, items[0]);
			STRCAT(p, " ");
			STRCAT(p, items[1]);
			spin->si_info = p;
		    }
	    }
	    else if (is_aff_rule(items, itemcnt, "MIDWORD", 2)
							   && midword == NULL)
	    {
		midword = getroom_save(spin, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "TRY", 2))
	    {

	    }

	    else if ((is_aff_rule(items, itemcnt, "RAR", 2)
			|| is_aff_rule(items, itemcnt, "RARE", 2))
							 && aff->af_rare == 0)
	    {
		aff->af_rare = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }

	    else if ((is_aff_rule(items, itemcnt, "KEP", 2)
			|| is_aff_rule(items, itemcnt, "KEEPCASE", 2))
						     && aff->af_keepcase == 0)
	    {
		aff->af_keepcase = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if ((is_aff_rule(items, itemcnt, "BAD", 2)
			|| is_aff_rule(items, itemcnt, "FORBIDDENWORD", 2))
							  && aff->af_bad == 0)
	    {
		aff->af_bad = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "NEEDAFFIX", 2)
						    && aff->af_needaffix == 0)
	    {
		aff->af_needaffix = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "CIRCUMFIX", 2)
						    && aff->af_circumfix == 0)
	    {
		aff->af_circumfix = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "NOSUGGEST", 2)
						    && aff->af_nosuggest == 0)
	    {
		aff->af_nosuggest = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if ((is_aff_rule(items, itemcnt, "NEEDCOMPOUND", 2)
			|| is_aff_rule(items, itemcnt, "ONLYINCOMPOUND", 2))
						     && aff->af_needcomp == 0)
	    {
		aff->af_needcomp = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDROOT", 2)
						     && aff->af_comproot == 0)
	    {
		aff->af_comproot = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDFORBIDFLAG", 2)
						   && aff->af_compforbid == 0)
	    {
		aff->af_compforbid = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
		if (aff->af_pref.ht_used > 0)
		    smsg((char_u *)_("Defining COMPOUNDFORBIDFLAG after PFX item may give wrong results in %s line %d"),
			    fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDPERMITFLAG", 2)
						   && aff->af_comppermit == 0)
	    {
		aff->af_comppermit = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
		if (aff->af_pref.ht_used > 0)
		    smsg((char_u *)_("Defining COMPOUNDPERMITFLAG after PFX item may give wrong results in %s line %d"),
			    fname, lnum);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDFLAG", 2)
							 && compflags == NULL)
	    {


		p = getroom(spin, STRLEN(items[1]) + 2, FALSE);
		if (p != NULL)
		{
		    STRCPY(p, items[1]);
		    STRCAT(p, "+");
		    compflags = p;
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDRULES", 2))
	    {


		if (atoi((char *)items[1]) == 0)
		    smsg((char_u *)_("Wrong COMPOUNDRULES value in %s line %d: %s"),
						       fname, lnum, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDRULE", 2))
	    {

		if (compflags != NULL || *skipdigits(items[1]) != NUL)
		{


		    l = (int)STRLEN(items[1]) + 1;
		    if (compflags != NULL)
			l += (int)STRLEN(compflags) + 1;
		    p = getroom(spin, l, FALSE);
		    if (p != NULL)
		    {
			if (compflags != NULL)
			{
			    STRCPY(p, compflags);
			    STRCAT(p, "/");
			}
			STRCAT(p, items[1]);
			compflags = p;
		    }
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDWORDMAX", 2)
							      && compmax == 0)
	    {
		compmax = atoi((char *)items[1]);
		if (compmax == 0)
		    smsg((char_u *)_("Wrong COMPOUNDWORDMAX value in %s line %d: %s"),
						       fname, lnum, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDMIN", 2)
							   && compminlen == 0)
	    {
		compminlen = atoi((char *)items[1]);
		if (compminlen == 0)
		    smsg((char_u *)_("Wrong COMPOUNDMIN value in %s line %d: %s"),
						       fname, lnum, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "COMPOUNDSYLMAX", 2)
							   && compsylmax == 0)
	    {
		compsylmax = atoi((char *)items[1]);
		if (compsylmax == 0)
		    smsg((char_u *)_("Wrong COMPOUNDSYLMAX value in %s line %d: %s"),
						       fname, lnum, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDDUP", 1))
	    {
		compoptions |= COMP_CHECKDUP;
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDREP", 1))
	    {
		compoptions |= COMP_CHECKREP;
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDCASE", 1))
	    {
		compoptions |= COMP_CHECKCASE;
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDTRIPLE", 1))
	    {
		compoptions |= COMP_CHECKTRIPLE;
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDPATTERN", 2))
	    {
		if (atoi((char *)items[1]) == 0)
		    smsg((char_u *)_("Wrong CHECKCOMPOUNDPATTERN value in %s line %d: %s"),
						       fname, lnum, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "CHECKCOMPOUNDPATTERN", 3))
	    {
		garray_T    *gap = &spin->si_comppat;
		int	    i;


		for (i = 0; i < gap->ga_len - 1; i += 2)
		    if (STRCMP(((char_u **)(gap->ga_data))[i], items[1]) == 0
			    && STRCMP(((char_u **)(gap->ga_data))[i + 1],
							       items[2]) == 0)
			break;
		if (i >= gap->ga_len && ga_grow(gap, 2) == OK)
		{
		    ((char_u **)(gap->ga_data))[gap->ga_len++]
					       = getroom_save(spin, items[1]);
		    ((char_u **)(gap->ga_data))[gap->ga_len++]
					       = getroom_save(spin, items[2]);
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "SYLLABLE", 2)
							  && syllable == NULL)
	    {
		syllable = getroom_save(spin, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "NOBREAK", 1))
	    {
		spin->si_nobreak = TRUE;
	    }
	    else if (is_aff_rule(items, itemcnt, "NOSPLITSUGS", 1))
	    {
		spin->si_nosplitsugs = TRUE;
	    }
	    else if (is_aff_rule(items, itemcnt, "NOCOMPOUNDSUGS", 1))
	    {
		spin->si_nocompoundsugs = TRUE;
	    }
	    else if (is_aff_rule(items, itemcnt, "NOSUGFILE", 1))
	    {
		spin->si_nosugfile = TRUE;
	    }
	    else if (is_aff_rule(items, itemcnt, "PFXPOSTPONE", 1))
	    {
		aff->af_pfxpostpone = TRUE;
	    }
	    else if (is_aff_rule(items, itemcnt, "IGNOREEXTRA", 1))
	    {
		aff->af_ignoreextra = TRUE;
	    }
	    else if ((STRCMP(items[0], "PFX") == 0
					      || STRCMP(items[0], "SFX") == 0)
		    && aff_todo == 0
		    && itemcnt >= 4)
	    {
		int	lasti = 4;
		char_u	key[AH_KEY_LEN];

		if (*items[0] == 'P')
		    tp = &aff->af_pref;
		else
		    tp = &aff->af_suff;


		vim_strncpy(key, items[1], AH_KEY_LEN - 1);
		hi = hash_find(tp, key);
		if (!HASHITEM_EMPTY(hi))
		{
		    cur_aff = HI2AH(hi);
		    if (cur_aff->ah_combine != (*items[2] == 'Y'))
			smsg((char_u *)_("Different combining flag in continued affix block in %s line %d: %s"),
						   fname, lnum, items[1]);
		    if (!cur_aff->ah_follows)
			smsg((char_u *)_("Duplicate affix in %s line %d: %s"),
						       fname, lnum, items[1]);
		}
		else
		{

		    cur_aff = (affheader_T *)getroom(spin,
						   sizeof(affheader_T), TRUE);
		    if (cur_aff == NULL)
			break;
		    cur_aff->ah_flag = affitem2flag(aff->af_flagtype, items[1],
								 fname, lnum);
		    if (cur_aff->ah_flag == 0 || STRLEN(items[1]) >= AH_KEY_LEN)
			break;
		    if (cur_aff->ah_flag == aff->af_bad
			    || cur_aff->ah_flag == aff->af_rare
			    || cur_aff->ah_flag == aff->af_keepcase
			    || cur_aff->ah_flag == aff->af_needaffix
			    || cur_aff->ah_flag == aff->af_circumfix
			    || cur_aff->ah_flag == aff->af_nosuggest
			    || cur_aff->ah_flag == aff->af_needcomp
			    || cur_aff->ah_flag == aff->af_comproot)
			smsg((char_u *)_("Affix also used for BAD/RARE/KEEPCASE/NEEDAFFIX/NEEDCOMPOUND/NOSUGGEST in %s line %d: %s"),
						       fname, lnum, items[1]);
		    STRCPY(cur_aff->ah_key, items[1]);
		    hash_add(tp, cur_aff->ah_key);

		    cur_aff->ah_combine = (*items[2] == 'Y');
		}


		if (itemcnt > lasti && STRCMP(items[lasti], "S") == 0)
		{
		    ++lasti;
		    cur_aff->ah_follows = TRUE;
		}
		else
		    cur_aff->ah_follows = FALSE;


		if (itemcnt > lasti && *items[lasti] != '#')
		    smsg((char_u *)_(e_afftrailing), fname, lnum, items[lasti]);

		if (STRCMP(items[2], "Y") != 0 && STRCMP(items[2], "N") != 0)
		    smsg((char_u *)_("Expected Y or N in %s line %d: %s"),
						       fname, lnum, items[2]);

		if (*items[0] == 'P' && aff->af_pfxpostpone)
		{
		    if (cur_aff->ah_newID == 0)
		    {


			check_renumber(spin);
			cur_aff->ah_newID = ++spin->si_newprefID;


			did_postpone_prefix = FALSE;
		    }
		    else

			did_postpone_prefix = TRUE;
		}

		aff_todo = atoi((char *)items[3]);
	    }
	    else if ((STRCMP(items[0], "PFX") == 0
					      || STRCMP(items[0], "SFX") == 0)
		    && aff_todo > 0
		    && STRCMP(cur_aff->ah_key, items[1]) == 0
		    && itemcnt >= 5)
	    {
		affentry_T	*aff_entry;
		int		upper = FALSE;
		int		lasti = 5;


		if (itemcnt > lasti
			&& !aff->af_ignoreextra
			&& *items[lasti] != '#'
			&& (STRCMP(items[lasti], "-") != 0
						     || itemcnt != lasti + 1))
		    smsg((char_u *)_(e_afftrailing), fname, lnum, items[lasti]);


		--aff_todo;
		aff_entry = (affentry_T *)getroom(spin,
						    sizeof(affentry_T), TRUE);
		if (aff_entry == NULL)
		    break;

		if (STRCMP(items[2], "0") != 0)
		    aff_entry->ae_chop = getroom_save(spin, items[2]);
		if (STRCMP(items[3], "0") != 0)
		{
		    aff_entry->ae_add = getroom_save(spin, items[3]);


		    aff_entry->ae_flags = vim_strchr(aff_entry->ae_add, '/');
		    if (aff_entry->ae_flags != NULL)
		    {
			*aff_entry->ae_flags++ = NUL;
			aff_process_flags(aff, aff_entry);
		    }
		}


		if (!spin->si_ascii || !(has_non_ascii(aff_entry->ae_chop)
					  || has_non_ascii(aff_entry->ae_add)))
		{
		    aff_entry->ae_next = cur_aff->ah_first;
		    cur_aff->ah_first = aff_entry;

		    if (STRCMP(items[4], ".") != 0)
		    {
			char_u	buf[MAXLINELEN];

			aff_entry->ae_cond = getroom_save(spin, items[4]);
			if (*items[0] == 'P')
			    sprintf((char *)buf, "^%s", items[4]);
			else
			    sprintf((char *)buf, "%s$", items[4]);
			aff_entry->ae_prog = vim_regcomp(buf,
					    RE_MAGIC + RE_STRING + RE_STRICT);
			if (aff_entry->ae_prog == NULL)
			    smsg((char_u *)_("Broken condition in %s line %d: %s"),
						       fname, lnum, items[4]);
		    }


		    if (*items[0] == 'P' && aff->af_pfxpostpone
					       && aff_entry->ae_flags == NULL)
		    {


			if (aff_entry->ae_chop != NULL
				&& aff_entry->ae_add != NULL
#ifdef FEAT_MBYTE
				&& aff_entry->ae_chop[(*mb_ptr2len)(
						   aff_entry->ae_chop)] == NUL
#else
				&& aff_entry->ae_chop[1] == NUL
#endif
				)
			{
			    int		c, c_up;

			    c = PTR2CHAR(aff_entry->ae_chop);
			    c_up = SPELL_TOUPPER(c);
			    if (c_up != c
				    && (aff_entry->ae_cond == NULL
					|| PTR2CHAR(aff_entry->ae_cond) == c))
			    {
				p = aff_entry->ae_add
						  + STRLEN(aff_entry->ae_add);
				mb_ptr_back(aff_entry->ae_add, p);
				if (PTR2CHAR(p) == c_up)
				{
				    upper = TRUE;
				    aff_entry->ae_chop = NULL;
				    *p = NUL;


				    if (aff_entry->ae_cond != NULL)
				    {
					char_u	buf[MAXLINELEN];
#ifdef FEAT_MBYTE
					if (has_mbyte)
					{
					    onecap_copy(items[4], buf, TRUE);
					    aff_entry->ae_cond = getroom_save(
								   spin, buf);
					}
					else
#endif
					    *aff_entry->ae_cond = c_up;
					if (aff_entry->ae_cond != NULL)
					{
					    sprintf((char *)buf, "^%s",
							  aff_entry->ae_cond);
					    vim_regfree(aff_entry->ae_prog);
					    aff_entry->ae_prog = vim_regcomp(
						    buf, RE_MAGIC + RE_STRING);
					}
				    }
				}
			    }
			}

			if (aff_entry->ae_chop == NULL
					       && aff_entry->ae_flags == NULL)
			{
			    int		idx;
			    char_u	**pp;
			    int		n;


			    for (idx = spin->si_prefcond.ga_len - 1; idx >= 0;
									--idx)
			    {
				p = ((char_u **)spin->si_prefcond.ga_data)[idx];
				if (str_equal(p, aff_entry->ae_cond))
				    break;
			    }
			    if (idx < 0 && ga_grow(&spin->si_prefcond, 1) == OK)
			    {

				idx = spin->si_prefcond.ga_len++;
				pp = ((char_u **)spin->si_prefcond.ga_data)
									+ idx;
				if (aff_entry->ae_cond == NULL)
				    *pp = NULL;
				else
				    *pp = getroom_save(spin,
							  aff_entry->ae_cond);
			    }


			    if (aff_entry->ae_add == NULL)
				p = (char_u *)"";
			    else
				p = aff_entry->ae_add;


			    n = PFX_FLAGS;
			    if (!cur_aff->ah_combine)
				n |= WFP_NC;
			    if (upper)
				n |= WFP_UP;
			    if (aff_entry->ae_comppermit)
				n |= WFP_COMPPERMIT;
			    if (aff_entry->ae_compforbid)
				n |= WFP_COMPFORBID;
			    tree_add_word(spin, p, spin->si_prefroot, n,
						      idx, cur_aff->ah_newID);
			    did_postpone_prefix = TRUE;
			}


			if (aff_todo == 0 && !did_postpone_prefix)
			{
			    --spin->si_newprefID;
			    cur_aff->ah_newID = 0;
			}
		    }
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "FOL", 2) && fol == NULL)
	    {
		fol = vim_strsave(items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "LOW", 2) && low == NULL)
	    {
		low = vim_strsave(items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "UPP", 2) && upp == NULL)
	    {
		upp = vim_strsave(items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "REP", 2)
		     || is_aff_rule(items, itemcnt, "REPSAL", 2))
	    {
		;
		if (!isdigit(*items[1]))
		    smsg((char_u *)_("Expected REP(SAL) count in %s line %d"),
								 fname, lnum);
	    }
	    else if ((STRCMP(items[0], "REP") == 0
			|| STRCMP(items[0], "REPSAL") == 0)
		    && itemcnt >= 3)
	    {


		if (itemcnt > 3 && items[3][0] != '#')
		    smsg((char_u *)_(e_afftrailing), fname, lnum, items[3]);
		if (items[0][3] == 'S' ? do_repsal : do_rep)
		{


		    for (p = items[1]; *p != NUL; mb_ptr_adv(p))
			if (*p == '_')
			    *p = ' ';
		    for (p = items[2]; *p != NUL; mb_ptr_adv(p))
			if (*p == '_')
			    *p = ' ';
		    add_fromto(spin, items[0][3] == 'S'
					 ? &spin->si_repsal
					 : &spin->si_rep, items[1], items[2]);
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "MAP", 2))
	    {

		if (!found_map)
		{

		    found_map = TRUE;
		    if (!isdigit(*items[1]))
			smsg((char_u *)_("Expected MAP count in %s line %d"),
								 fname, lnum);
		}
		else if (do_mapline)
		{
		    int		c;


		    for (p = items[1]; *p != NUL; )
		    {
#ifdef FEAT_MBYTE
			c = mb_ptr2char_adv(&p);
#else
			c = *p++;
#endif
			if ((spin->si_map.ga_len > 0
				    && vim_strchr(spin->si_map.ga_data, c)
								      != NULL)
				|| vim_strchr(p, c) != NULL)
			    smsg((char_u *)_("Duplicate character in MAP in %s line %d"),
								 fname, lnum);
		    }


		    ga_concat(&spin->si_map, items[1]);
		    ga_append(&spin->si_map, '/');
		}
	    }

	    else if (is_aff_rule(items, itemcnt, "SAL", 3))
	    {
		if (do_sal)
		{


		    if (STRCMP(items[1], "followup") == 0)
			spin->si_followup = sal_to_bool(items[2]);
		    else if (STRCMP(items[1], "collapse_result") == 0)
			spin->si_collapse = sal_to_bool(items[2]);
		    else if (STRCMP(items[1], "remove_accents") == 0)
			spin->si_rem_accents = sal_to_bool(items[2]);
		    else

			add_fromto(spin, &spin->si_sal, items[1],
				     STRCMP(items[2], "_") == 0 ? (char_u *)""
								: items[2]);
		}
	    }
	    else if (is_aff_rule(items, itemcnt, "SOFOFROM", 2)
							  && sofofrom == NULL)
	    {
		sofofrom = getroom_save(spin, items[1]);
	    }
	    else if (is_aff_rule(items, itemcnt, "SOFOTO", 2)
							    && sofoto == NULL)
	    {
		sofoto = getroom_save(spin, items[1]);
	    }
	    else if (STRCMP(items[0], "COMMON") == 0)
	    {
		int	i;

		for (i = 1; i < itemcnt; ++i)
		{
		    if (HASHITEM_EMPTY(hash_find(&spin->si_commonwords,
								   items[i])))
		    {
			p = vim_strsave(items[i]);
			if (p == NULL)
			    break;
			hash_add(&spin->si_commonwords, p);
		    }
		}
	    }
	    else
		smsg((char_u *)_("Unrecognized or duplicate item in %s line %d: %s"),
						       fname, lnum, items[0]);
	}
    }

    if (fol != NULL || low != NULL || upp != NULL)
    {
	if (spin->si_clear_chartab)
	{


	    init_spell_chartab();
	    spin->si_clear_chartab = FALSE;
	}


	if (!spin->si_ascii
#ifdef FEAT_MBYTE
		&& !enc_utf8
#endif
		)
	{
	    if (fol == NULL || low == NULL || upp == NULL)
		smsg((char_u *)_("Missing FOL/LOW/UPP line in %s"), fname);
	    else
		(void)set_spell_chartab(fol, low, upp);
	}

	vim_free(fol);
	vim_free(low);
	vim_free(upp);
    }


    if (compmax != 0)
    {
	aff_check_number(spin->si_compmax, compmax, "COMPOUNDWORDMAX");
	spin->si_compmax = compmax;
    }

    if (compminlen != 0)
    {
	aff_check_number(spin->si_compminlen, compminlen, "COMPOUNDMIN");
	spin->si_compminlen = compminlen;
    }

    if (compsylmax != 0)
    {
	if (syllable == NULL)
	    smsg((char_u *)_("COMPOUNDSYLMAX used without SYLLABLE"));
	aff_check_number(spin->si_compsylmax, compsylmax, "COMPOUNDSYLMAX");
	spin->si_compsylmax = compsylmax;
    }

    if (compoptions != 0)
    {
	aff_check_number(spin->si_compoptions, compoptions, "COMPOUND options");
	spin->si_compoptions |= compoptions;
    }

    if (compflags != NULL)
	process_compflags(spin, aff, compflags);


    if (spin->si_newcompID < spin->si_newprefID)
    {
	if (spin->si_newcompID == 127 || spin->si_newcompID == 255)
	    MSG(_("Too many postponed prefixes"));
	else if (spin->si_newprefID == 0 || spin->si_newprefID == 127)
	    MSG(_("Too many compound flags"));
	else
	    MSG(_("Too many postponed prefixes and/or compound flags"));
    }

    if (syllable != NULL)
    {
	aff_check_string(spin->si_syllable, syllable, "SYLLABLE");
	spin->si_syllable = syllable;
    }

    if (sofofrom != NULL || sofoto != NULL)
    {
	if (sofofrom == NULL || sofoto == NULL)
	    smsg((char_u *)_("Missing SOFO%s line in %s"),
				     sofofrom == NULL ? "FROM" : "TO", fname);
	else if (spin->si_sal.ga_len > 0)
	    smsg((char_u *)_("Both SAL and SOFO lines in %s"), fname);
	else
	{
	    aff_check_string(spin->si_sofofr, sofofrom, "SOFOFROM");
	    aff_check_string(spin->si_sofoto, sofoto, "SOFOTO");
	    spin->si_sofofr = sofofrom;
	    spin->si_sofoto = sofoto;
	}
    }

    if (midword != NULL)
    {
	aff_check_string(spin->si_midword, midword, "MIDWORD");
	spin->si_midword = midword;
    }

    vim_free(pc);
    fclose(fd);
    return aff;
}
