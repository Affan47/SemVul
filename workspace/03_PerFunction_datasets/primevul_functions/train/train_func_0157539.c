Perl_re_op_compile(pTHX_ SV ** const patternp, int pat_count,
		    OP *expr, const regexp_engine* eng, REGEXP *old_re,
		     bool *is_bare_re, U32 orig_rx_flags, U32 pm_flags)
{
    REGEXP *rx;
    struct regexp *r;
    regexp_internal *ri;
    STRLEN plen;
    char *exp;
    regnode *scan;
    I32 flags;
    SSize_t minlen = 0;
    U32 rx_flags;
    SV *pat;
    SV** new_patternp = patternp;


    I32 sawlookahead = 0;
    I32 sawplus = 0;
    I32 sawopen = 0;
    I32 sawminmod = 0;

    regex_charset initial_charset = get_regex_charset(orig_rx_flags);
    bool recompile = 0;
    bool runtime_code = 0;
    scan_data_t data;
    RExC_state_t RExC_state;
    RExC_state_t * const pRExC_state = &RExC_state;
#ifdef TRIE_STUDY_OPT
    int restudied = 0;
    RExC_state_t copyRExC_state;
#endif
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_RE_OP_COMPILE;

    DEBUG_r(if (!PL_colorset) reginitcolors());


    if (! PL_AboveLatin1) {
#ifdef DEBUGGING
        char * dump_len_string;
#endif

	PL_AboveLatin1 = _new_invlist_C_array(AboveLatin1_invlist);
	PL_Latin1 = _new_invlist_C_array(Latin1_invlist);
	PL_UpperLatin1 = _new_invlist_C_array(UpperLatin1_invlist);
        PL_utf8_foldable = _new_invlist_C_array(_Perl_Any_Folds_invlist);
        PL_HasMultiCharFold =
                       _new_invlist_C_array(_Perl_Folds_To_Multi_Char_invlist);


	PL_InBitmap = _new_invlist(2);
	PL_InBitmap = _add_range_to_invlist(PL_InBitmap, 0,
                                                    NUM_ANYOF_CODE_POINTS - 1);
#ifdef DEBUGGING
        dump_len_string = PerlEnv_getenv("PERL_DUMP_RE_MAX_LEN");
        if (   ! dump_len_string
            || ! grok_atoUV(dump_len_string, (UV *)&PL_dump_re_max_len, NULL))
        {
            PL_dump_re_max_len = 60;
        }
#endif
    }

    pRExC_state->warn_text = NULL;
    pRExC_state->code_blocks = NULL;

    if (is_bare_re)
	*is_bare_re = FALSE;

    if (expr && (expr->op_type == OP_LIST ||
		(expr->op_type == OP_NULL && expr->op_targ == OP_LIST))) {

	OP *o;
	int ncode = 0;

	for (o = cLISTOPx(expr)->op_first; o; o = OpSIBLING(o))
	    if (o->op_type == OP_NULL && (o->op_flags & OPf_SPECIAL))
		ncode++;

	if (ncode)
            pRExC_state->code_blocks = S_alloc_code_blocks(aTHX_ ncode);
    }

    if (!pat_count) {


        int n;
        OP *o;


        assert(expr);
        n = 0;
        if (expr->op_type == OP_CONST)
            n = 1;
        else
            for (o = cLISTOPx(expr)->op_first; o; o = OpSIBLING(o)) {
                if (o->op_type == OP_CONST)
                    n++;
            }


        assert(!new_patternp);
        Newx(new_patternp, n, SV*);
        SAVEFREEPV(new_patternp);
        pat_count = n;

        n = 0;
        if (expr->op_type == OP_CONST)
            new_patternp[n] = cSVOPx_sv(expr);
        else
            for (o = cLISTOPx(expr)->op_first; o; o = OpSIBLING(o)) {
                if (o->op_type == OP_CONST)
                    new_patternp[n++] = cSVOPo_sv;
            }

    }

    DEBUG_PARSE_r(Perl_re_printf( aTHX_
        "Assembling pattern from %d elements%s\n", pat_count,
            orig_rx_flags & RXf_SPLIT ? " for split" : ""));


    if (pRExC_state->code_blocks && pRExC_state->code_blocks->count
         && expr->op_type != OP_CONST)
    {
            expr = cLISTOPx(expr)->op_first;
            assert(   expr->op_type == OP_PUSHMARK
                   || (expr->op_type == OP_NULL && expr->op_targ == OP_PUSHMARK)
                   || expr->op_type == OP_PADRANGE);
            expr = OpSIBLING(expr);
    }

    pat = S_concat_pat(aTHX_ pRExC_state, NULL, new_patternp, pat_count,
                        expr, &recompile, NULL);


    {
        SV *re = pat;
        if (SvROK(re))
            re = SvRV(re);
        if (SvTYPE(re) == SVt_REGEXP) {
            if (is_bare_re)
                *is_bare_re = TRUE;
            SvREFCNT_inc(re);
            DEBUG_PARSE_r(Perl_re_printf( aTHX_
                "Precompiled pattern%s\n",
                    orig_rx_flags & RXf_SPLIT ? " for split" : ""));

            return (REGEXP*)re;
        }
    }

    exp = SvPV_nomg(pat, plen);

    if (!eng->op_comp) {
	if ((SvUTF8(pat) && IN_BYTES)
		|| SvGMAGICAL(pat) || SvAMAGIC(pat))
	{


	    pat = newSVpvn_flags(exp, plen, SVs_TEMP |
					(IN_BYTES ? 0 : SvUTF8(pat)));
	}
	return CALLREGCOMP_ENG(eng, pat, orig_rx_flags);
    }


    RExC_utf8 = RExC_orig_utf8 = (plen == 0 || IN_BYTES) ? 0 : SvUTF8(pat);

    RExC_uni_semantics = 0;
    RExC_seen_unfolded_sharp_s = 0;
    RExC_contains_locale = 0;
    RExC_strict = cBOOL(pm_flags & RXf_PMf_STRICT);
    RExC_study_started = 0;
    pRExC_state->runtime_code_qr = NULL;
    RExC_frame_head= NULL;
    RExC_frame_last= NULL;
    RExC_frame_count= 0;

    DEBUG_r({
        RExC_mysv1= sv_newmortal();
        RExC_mysv2= sv_newmortal();
    });
    DEBUG_COMPILE_r({
            SV *dsv= sv_newmortal();
            RE_PV_QUOTED_DECL(s, RExC_utf8, dsv, exp, plen, PL_dump_re_max_len);
            Perl_re_printf( aTHX_  "%sCompiling REx%s %s\n",
                          PL_colors[4],PL_colors[5],s);
        });

  redo_first_pass:


    if ((pm_flags & PMf_USE_RE_EVAL)


		|| (IN_PERL_COMPILETIME && (PL_hints & HINT_RE_EVAL))
    )
	runtime_code = S_has_runtime_code(aTHX_ pRExC_state, exp, plen);


    if (   old_re
        && !recompile
        && !!RX_UTF8(old_re) == !!RExC_utf8
        && ( RX_COMPFLAGS(old_re) == ( orig_rx_flags & RXf_PMf_FLAGCOPYMASK ) )
	&& RX_PRECOMP(old_re)
	&& RX_PRELEN(old_re) == plen
        && memEQ(RX_PRECOMP(old_re), exp, plen)
	&& !runtime_code  )
    {
        return old_re;
    }

    rx_flags = orig_rx_flags;

    if (   initial_charset == REGEX_DEPENDS_CHARSET
        && (RExC_utf8 ||RExC_uni_semantics))
    {


	set_regex_charset(&rx_flags, REGEX_UNICODE_CHARSET);
    }

    RExC_precomp = exp;
    RExC_precomp_adj = 0;
    RExC_flags = rx_flags;
    RExC_pm_flags = pm_flags;

    if (runtime_code) {
        assert(TAINTING_get || !TAINT_get);
	if (TAINT_get)
	    Perl_croak(aTHX_ "Eval-group in insecure regular expression");

	if (!S_compile_runtime_code(aTHX_ pRExC_state, exp, plen)) {


            S_pat_upgrade_to_utf8(aTHX_ pRExC_state, &exp, &plen,
                pRExC_state->code_blocks ? pRExC_state->code_blocks->count : 0);
            goto redo_first_pass;
	}
    }
    assert(!pRExC_state->runtime_code_qr);

    RExC_sawback = 0;

    RExC_seen = 0;
    RExC_maxlen = 0;
    RExC_in_lookbehind = 0;
    RExC_seen_zerolen = *exp == '^' ? -1 : 0;
    RExC_extralen = 0;
#ifdef EBCDIC
    RExC_recode_x_to_native = 0;
#endif
    RExC_in_multi_char_class = 0;


    RExC_parse = exp;
    RExC_start = RExC_adjusted_start = exp;
    RExC_end = exp + plen;
    RExC_precomp_end = RExC_end;
    RExC_naughty = 0;
    RExC_npar = 1;
    RExC_nestroot = 0;
    RExC_size = 0L;
    RExC_emit = (regnode *) &RExC_emit_dummy;
    RExC_whilem_seen = 0;
    RExC_open_parens = NULL;
    RExC_close_parens = NULL;
    RExC_end_op = NULL;
    RExC_paren_names = NULL;
#ifdef DEBUGGING
    RExC_paren_name_list = NULL;
#endif
    RExC_recurse = NULL;
    RExC_study_chunk_recursed = NULL;
    RExC_study_chunk_recursed_bytes= 0;
    RExC_recurse_count = 0;
    pRExC_state->code_index = 0;


    assert(*RExC_end == '\0');

    DEBUG_PARSE_r(
        Perl_re_printf( aTHX_  "Starting first pass (sizing)\n");
        RExC_lastnum=0;
        RExC_lastparse=NULL;
    );

    if (reg(pRExC_state, 0, &flags,1) == NULL) {


        if (flags & RESTART_PASS1) {
            if (flags & NEED_UTF8) {
                S_pat_upgrade_to_utf8(aTHX_ pRExC_state, &exp, &plen,
                pRExC_state->code_blocks ? pRExC_state->code_blocks->count : 0);
            }
            else {
                DEBUG_PARSE_r(Perl_re_printf( aTHX_
                "Need to redo pass 1\n"));
            }

            goto redo_first_pass;
        }
        Perl_croak(aTHX_ "panic: reg returned NULL to re_op_compile for sizing pass, flags=%#" UVxf, (UV) flags);
    }

    DEBUG_PARSE_r({
        Perl_re_printf( aTHX_
            "Required size %" IVdf " nodes\n"
            "Starting second pass (creation)\n",
            (IV)RExC_size);
        RExC_lastnum=0;
        RExC_lastparse=NULL;
    });


    if ((RExC_utf8 || RExC_uni_semantics)
	 && get_regex_charset(rx_flags) == REGEX_DEPENDS_CHARSET)
    {
	set_regex_charset(&rx_flags, REGEX_UNICODE_CHARSET);
    }


    if (RExC_size >= 0x10000L && RExC_extralen)
        RExC_size += RExC_extralen;
    else
	RExC_extralen = 0;
    if (RExC_whilem_seen > 15)
	RExC_whilem_seen = 15;


    rx = (REGEXP*) newSV_type(SVt_REGEXP);
    r = ReANY(rx);
    Newxc(ri, sizeof(regexp_internal) + (unsigned)RExC_size * sizeof(regnode),
	 char, regexp_internal);
    if ( r == NULL || ri == NULL )
	FAIL("Regexp out of space");
#ifdef DEBUGGING

    Zero(ri, sizeof(regexp_internal) + (unsigned)RExC_size * sizeof(regnode),
         char);
#else

    Zero(ri, sizeof(regexp_internal), char);
#endif


    RXi_SET( r, ri );
    r->engine= eng;
    r->extflags = rx_flags;
    RXp_COMPFLAGS(r) = orig_rx_flags & RXf_PMf_FLAGCOPYMASK;

    if (pm_flags & PMf_IS_QR) {
	ri->code_blocks = pRExC_state->code_blocks;
	if (ri->code_blocks)
            ri->code_blocks->refcnt++;
    }

    {
        bool has_p     = ((r->extflags & RXf_PMf_KEEPCOPY) == RXf_PMf_KEEPCOPY);
        bool has_charset = (get_regex_charset(r->extflags)
                                                    != REGEX_DEPENDS_CHARSET);


        bool has_default =
                    (((r->extflags & RXf_PMf_STD_PMMOD) != RXf_PMf_STD_PMMOD)
                    || ! has_charset);
        bool has_runon = ((RExC_seen & REG_RUN_ON_COMMENT_SEEN)
                                                   == REG_RUN_ON_COMMENT_SEEN);
	U8 reganch = (U8)((r->extflags & RXf_PMf_STD_PMMOD)
			    >> RXf_PMf_STD_PMMOD_SHIFT);
	const char *fptr = STD_PAT_MODS;
	char *p;


	const STRLEN wraplen = plen + has_p + has_runon
            + has_default
            + PL_bitcount[reganch]


	    + ((has_charset) ? MAX_CHARSET_NAME_LENGTH : 0)
            + (sizeof("(?:)") - 1);


        assert(sizeof(STD_PAT_MODS) <= 8);

        p = sv_grow(MUTABLE_SV(rx), wraplen + 1);
        SvPOK_on(rx);
	if (RExC_utf8)
	    SvFLAGS(rx) |= SVf_UTF8;
        *p++='('; *p++='?';


        if (has_default) {
            *p++= DEFAULT_PAT_MOD;
        }
        if (has_charset) {
	    STRLEN len;
	    const char* const name = get_regex_charset_name(r->extflags, &len);
	    Copy(name, p, len, char);
	    p += len;
        }
        if (has_p)
            *p++ = KEEPCOPY_PAT_MOD;
        {
            char ch;
            while((ch = *fptr++)) {
                if(reganch & 1)
                    *p++ = ch;
                reganch >>= 1;
            }
        }

        *p++ = ':';
        Copy(RExC_precomp, p, plen, char);
	assert ((RX_WRAPPED(rx) - p) < 16);
	r->pre_prefix = p - RX_WRAPPED(rx);
        p += plen;
        if (has_runon)
            *p++ = '\n';
        *p++ = ')';
        *p = 0;
	SvCUR_set(rx, p - RX_WRAPPED(rx));
    }

    r->intflags = 0;
    r->nparens = RExC_npar - 1;


#ifdef RE_TRACK_PATTERN_OFFSETS
    Newxz(ri->u.offsets, 2*RExC_size+1, U32);
    DEBUG_OFFSETS_r(Perl_re_printf( aTHX_
                          "%s %" UVuf " bytes for offset annotations.\n",
                          ri->u.offsets ? "Got" : "Couldn't get",
                          (UV)((2*RExC_size+1) * sizeof(U32))));
#endif
    SetProgLen(ri,RExC_size);
    RExC_rx_sv = rx;
    RExC_rx = r;
    RExC_rxi = ri;


    RExC_flags = rx_flags;
    RExC_pm_flags = pm_flags;
    RExC_parse = exp;
    RExC_end = exp + plen;
    RExC_naughty = 0;
    RExC_emit_start = ri->program;
    RExC_emit = ri->program;
    RExC_emit_bound = ri->program + RExC_size + 1;
    pRExC_state->code_index = 0;

    *((char*) RExC_emit++) = (char) REG_MAGIC;


    if (RExC_seen & REG_RECURSE_SEEN) {
        DEBUG_OPTIMISE_MORE_r(Perl_re_printf( aTHX_
            "%*s%*s Setting up open/close parens\n",
                  22, "|    |", (int)(0 * 2 + 1), ""));


        Newxz(RExC_open_parens, RExC_npar,regnode *);
        SAVEFREEPV(RExC_open_parens);
        RExC_open_parens[0] = RExC_emit;


        Newxz(RExC_close_parens, RExC_npar,regnode *);
        SAVEFREEPV(RExC_close_parens);


        RExC_study_chunk_recursed_bytes= (RExC_npar >> 3) +
                                         ((RExC_npar & 0x07) != 0);
        Newx(RExC_study_chunk_recursed,
             RExC_study_chunk_recursed_bytes * RExC_npar, U8);
        SAVEFREEPV(RExC_study_chunk_recursed);
    }
    RExC_npar = 1;
    if (reg(pRExC_state, 0, &flags,1) == NULL) {
	ReREFCNT_dec(rx);
        Perl_croak(aTHX_ "panic: reg returned NULL to re_op_compile for generation pass, flags=%#" UVxf, (UV) flags);
    }
    DEBUG_OPTIMISE_r(
        Perl_re_printf( aTHX_  "Starting post parse optimization\n");
    );


    Newx(r->substrs, 1, struct reg_substr_data);
    if (RExC_recurse_count) {
        Newxz(RExC_recurse,RExC_recurse_count,regnode *);
        SAVEFREEPV(RExC_recurse);
    }

  reStudy:
    r->minlen = minlen = sawlookahead = sawplus = sawopen = sawminmod = 0;
    DEBUG_r(
        RExC_study_chunk_recursed_count= 0;
    );
    Zero(r->substrs, 1, struct reg_substr_data);
    if (RExC_study_chunk_recursed) {
        Zero(RExC_study_chunk_recursed,
             RExC_study_chunk_recursed_bytes * RExC_npar, U8);
    }


#ifdef TRIE_STUDY_OPT
    if (!restudied) {
        StructCopy(&zero_scan_data, &data, scan_data_t);
        copyRExC_state = RExC_state;
    } else {
        U32 seen=RExC_seen;
        DEBUG_OPTIMISE_r(Perl_re_printf( aTHX_ "Restudying\n"));

        RExC_state = copyRExC_state;
        if (seen & REG_TOP_LEVEL_BRANCHES_SEEN)
            RExC_seen |= REG_TOP_LEVEL_BRANCHES_SEEN;
        else
            RExC_seen &= ~REG_TOP_LEVEL_BRANCHES_SEEN;
	StructCopy(&zero_scan_data, &data, scan_data_t);
    }
#else
    StructCopy(&zero_scan_data, &data, scan_data_t);
#endif


    r->extflags = RExC_flags;


    if (UTF)
	SvUTF8_on(rx);
    ri->regstclass = NULL;
    if (RExC_naughty >= TOO_NAUGHTY)
	r->intflags |= PREGf_NAUGHTY;
    scan = ri->program + 1;


    if (!(RExC_seen & REG_TOP_LEVEL_BRANCHES_SEEN)) {

	SSize_t fake;
	STRLEN longest_length[2];
	regnode_ssc ch_class;
	int stclass_flag;
	SSize_t last_close = 0;
        regnode *first= scan;
        regnode *first_next= regnext(first);
        int i;


	while ((OP(first) == OPEN && (sawopen = 1)) ||

	    (OP(first) == BRANCH && OP(first_next) != BRANCH) ||

	    (OP(first) == IFMATCH && !first->flags && (sawlookahead = 1)) ||
	    (OP(first) == PLUS) ||
	    (OP(first) == MINMOD) ||

	    (PL_regkind[OP(first)] == CURLY && ARG1(first) > 0) ||
	    (OP(first) == NOTHING && PL_regkind[OP(first_next)] != END ))
	{


		if (OP(first) == PLUS)
		    sawplus = 1;
                else {
                    if (OP(first) == MINMOD)
                        sawminmod = 1;
		    first += regarglen[OP(first)];
                }
		first = NEXTOPER(first);
		first_next= regnext(first);
	}


      again:
        DEBUG_PEEP("first:", first, 0, 0);

	if (PL_regkind[OP(first)] == EXACT) {
	    if (OP(first) == EXACT || OP(first) == EXACTL)
		NOOP;
	    else
		ri->regstclass = first;
	}
#ifdef TRIE_STCLASS
	else if (PL_regkind[OP(first)] == TRIE &&
	        ((reg_trie_data *)ri->data->data[ ARG(first) ])->minlen>0)
	{

            ri->regstclass = construct_ahocorasick_from_trie(pRExC_state, (regnode *)first, 0);
	}
#endif
	else if (REGNODE_SIMPLE(OP(first)))
	    ri->regstclass = first;
	else if (PL_regkind[OP(first)] == BOUND ||
		 PL_regkind[OP(first)] == NBOUND)
	    ri->regstclass = first;
	else if (PL_regkind[OP(first)] == BOL) {
            r->intflags |= (OP(first) == MBOL
                           ? PREGf_ANCH_MBOL
                           : PREGf_ANCH_SBOL);
	    first = NEXTOPER(first);
	    goto again;
	}
	else if (OP(first) == GPOS) {
            r->intflags |= PREGf_ANCH_GPOS;
	    first = NEXTOPER(first);
	    goto again;
	}
	else if ((!sawopen || !RExC_sawback) &&
            !sawlookahead &&
	    (OP(first) == STAR &&
	    PL_regkind[OP(NEXTOPER(first))] == REG_ANY) &&
            !(r->intflags & PREGf_ANCH) && !pRExC_state->code_blocks)
	{

	    const int type =
		(OP(NEXTOPER(first)) == REG_ANY)
                    ? PREGf_ANCH_MBOL
                    : PREGf_ANCH_SBOL;
            r->intflags |= (type | PREGf_IMPLICIT);
	    first = NEXTOPER(first);
	    goto again;
	}
        if (sawplus && !sawminmod && !sawlookahead
            && (!sawopen || !RExC_sawback)
	    && !pRExC_state->code_blocks)

	    r->intflags |= PREGf_SKIP;


#ifdef TRIE_STUDY_OPT
	DEBUG_PARSE_r(
	    if (!restudied)
                Perl_re_printf( aTHX_  "first at %" IVdf "\n",
			      (IV)(first - scan + 1))
        );
#else
	DEBUG_PARSE_r(
            Perl_re_printf( aTHX_  "first at %" IVdf "\n",
	        (IV)(first - scan + 1))
        );
#endif


	data.substrs[0].str = newSVpvs("");
	data.substrs[1].str = newSVpvs("");
	data.last_found = newSVpvs("");
	data.cur_is_floating = 0;
	ENTER_with_name("study_chunk");
	SAVEFREESV(data.substrs[0].str);
	SAVEFREESV(data.substrs[1].str);
	SAVEFREESV(data.last_found);
	first = scan;
	if (!ri->regstclass) {
	    ssc_init(pRExC_state, &ch_class);
	    data.start_class = &ch_class;
	    stclass_flag = SCF_DO_STCLASS_AND;
	} else
	    stclass_flag = 0;
	data.last_closep = &last_close;

        DEBUG_RExC_seen();
	minlen = study_chunk(pRExC_state, &first, &minlen, &fake,
                             scan + RExC_size,
            &data, -1, 0, NULL,
            SCF_DO_SUBSTR | SCF_WHILEM_VISITED_POS | stclass_flag
                          | (restudied ? SCF_TRIE_DOING_RESTUDY : 0),
            0);


        CHECK_RESTUDY_GOTO_butfirst(LEAVE_with_name("study_chunk"));


	if ( RExC_npar == 1 && !data.cur_is_floating
	     && data.last_start_min == 0 && data.last_end > 0
	     && !RExC_seen_zerolen
             && !(RExC_seen & REG_VERBARG_SEEN)
             && !(RExC_seen & REG_GPOS_SEEN)
        ){
	    r->extflags |= RXf_CHECK_ALL;
        }
	scan_commit(pRExC_state, &data,&minlen,0);


        for (i = 1; i >= 0; i--) {
            longest_length[i] = CHR_SVLEN(data.substrs[i].str);

            if (   !(   i
                     && SvCUR(data.substrs[0].str)
                     &&    data.substrs[0].min_offset
                        == data.substrs[1].min_offset
                     &&    SvCUR(data.substrs[0].str)
                        == SvCUR(data.substrs[1].str)
                    )
                && S_setup_longest (aTHX_ pRExC_state,
                                        &(r->substrs->data[i]),
                                        &(data.substrs[i]),
                                        longest_length[i]))
            {
                r->substrs->data[i].min_offset =
                        data.substrs[i].min_offset - data.substrs[i].lookbehind;

                r->substrs->data[i].max_offset = data.substrs[i].max_offset;

                if (data.substrs[i].max_offset < SSize_t_MAX)
                    r->substrs->data[i].max_offset -= data.substrs[i].lookbehind;
                SvREFCNT_inc_simple_void_NN(data.substrs[i].str);
            }
            else {
                r->substrs->data[i].substr      = NULL;
                r->substrs->data[i].utf8_substr = NULL;
                longest_length[i] = 0;
            }
        }

	LEAVE_with_name("study_chunk");

	if (ri->regstclass
	    && (OP(ri->regstclass) == REG_ANY || OP(ri->regstclass) == SANY))
	    ri->regstclass = NULL;

	if ((!(r->substrs->data[0].substr || r->substrs->data[0].utf8_substr)
              || r->substrs->data[0].min_offset)
	    && stclass_flag
            && ! (ANYOF_FLAGS(data.start_class) & SSC_MATCHES_EMPTY_STRING)
	    && is_ssc_worth_it(pRExC_state, data.start_class))
	{
	    const U32 n = add_data(pRExC_state, STR_WITH_LEN("f"));

            ssc_finalize(pRExC_state, data.start_class);

	    Newx(RExC_rxi->data->data[n], 1, regnode_ssc);
	    StructCopy(data.start_class,
		       (regnode_ssc*)RExC_rxi->data->data[n],
		       regnode_ssc);
	    ri->regstclass = (regnode*)RExC_rxi->data->data[n];
	    r->intflags &= ~PREGf_SKIP;
	    DEBUG_COMPILE_r({ SV *sv = sv_newmortal();
                      regprop(r, sv, (regnode*)data.start_class, NULL, pRExC_state);
                      Perl_re_printf( aTHX_
				    "synthetic stclass \"%s\".\n",
				    SvPVX_const(sv));});
            data.start_class = NULL;
	}


	i = (longest_length[0] <= longest_length[1]);
        r->substrs->check_ix = i;
        r->check_end_shift  = r->substrs->data[i].end_shift;
        r->check_substr     = r->substrs->data[i].substr;
        r->check_utf8       = r->substrs->data[i].utf8_substr;
        r->check_offset_min = r->substrs->data[i].min_offset;
        r->check_offset_max = r->substrs->data[i].max_offset;
        if (!i && (r->intflags & (PREGf_ANCH_SBOL|PREGf_ANCH_GPOS)))
            r->intflags |= PREGf_NOSCAN;

	if ((r->check_substr || r->check_utf8) ) {
	    r->extflags |= RXf_USE_INTUIT;
	    if (SvTAIL(r->check_substr ? r->check_substr : r->check_utf8))
		r->extflags |= RXf_INTUIT_TAIL;
	}


    }
    else {

	SSize_t fake;
	regnode_ssc ch_class;
	SSize_t last_close = 0;

        DEBUG_PARSE_r(Perl_re_printf( aTHX_  "\nMulti Top Level\n"));

	scan = ri->program + 1;
	ssc_init(pRExC_state, &ch_class);
	data.start_class = &ch_class;
	data.last_closep = &last_close;

        DEBUG_RExC_seen();
	minlen = study_chunk(pRExC_state,
            &scan, &minlen, &fake, scan + RExC_size, &data, -1, 0, NULL,
            SCF_DO_STCLASS_AND|SCF_WHILEM_VISITED_POS|(restudied
                                                      ? SCF_TRIE_DOING_RESTUDY
                                                      : 0),
            0);

        CHECK_RESTUDY_GOTO_butfirst(NOOP);

	r->check_substr = NULL;
        r->check_utf8 = NULL;
        r->substrs->data[0].substr      = NULL;
        r->substrs->data[0].utf8_substr = NULL;
        r->substrs->data[1].substr      = NULL;
        r->substrs->data[1].utf8_substr = NULL;

        if (! (ANYOF_FLAGS(data.start_class) & SSC_MATCHES_EMPTY_STRING)
	    && is_ssc_worth_it(pRExC_state, data.start_class))
        {
	    const U32 n = add_data(pRExC_state, STR_WITH_LEN("f"));

            ssc_finalize(pRExC_state, data.start_class);

	    Newx(RExC_rxi->data->data[n], 1, regnode_ssc);
	    StructCopy(data.start_class,
		       (regnode_ssc*)RExC_rxi->data->data[n],
		       regnode_ssc);
	    ri->regstclass = (regnode*)RExC_rxi->data->data[n];
	    r->intflags &= ~PREGf_SKIP;
	    DEBUG_COMPILE_r({ SV* sv = sv_newmortal();
                      regprop(r, sv, (regnode*)data.start_class, NULL, pRExC_state);
                      Perl_re_printf( aTHX_
				    "synthetic stclass \"%s\".\n",
				    SvPVX_const(sv));});
            data.start_class = NULL;
	}
    }

    if (RExC_seen & REG_UNBOUNDED_QUANTIFIER_SEEN) {
        r->extflags |= RXf_UNBOUNDED_QUANTIFIER_SEEN;
        r->maxlen = REG_INFTY;
    }
    else {
        r->maxlen = RExC_maxlen;
    }


    DEBUG_OPTIMISE_r({
        Perl_re_printf( aTHX_ "minlen: %" IVdf " r->minlen:%" IVdf " maxlen:%" IVdf "\n",
                      (IV)minlen, (IV)r->minlen, (IV)RExC_maxlen);
    });
    r->minlenret = minlen;
    if (r->minlen < minlen)
        r->minlen = minlen;

    if (RExC_seen & REG_RECURSE_SEEN ) {
        r->intflags |= PREGf_RECURSE_SEEN;
        Newxz(r->recurse_locinput, r->nparens + 1, char *);
    }
    if (RExC_seen & REG_GPOS_SEEN)
        r->intflags |= PREGf_GPOS_SEEN;
    if (RExC_seen & REG_LOOKBEHIND_SEEN)
        r->extflags |= RXf_NO_INPLACE_SUBST;

    if (pRExC_state->code_blocks)
	r->extflags |= RXf_EVAL_SEEN;
    if (RExC_seen & REG_VERBARG_SEEN)
    {
	r->intflags |= PREGf_VERBARG_SEEN;
        r->extflags |= RXf_NO_INPLACE_SUBST;
    }
    if (RExC_seen & REG_CUTGROUP_SEEN)
	r->intflags |= PREGf_CUTGROUP_SEEN;
    if (pm_flags & PMf_USE_RE_EVAL)
	r->intflags |= PREGf_USE_RE_EVAL;
    if (RExC_paren_names)
        RXp_PAREN_NAMES(r) = MUTABLE_HV(SvREFCNT_inc(RExC_paren_names));
    else
        RXp_PAREN_NAMES(r) = NULL;


    if (r->intflags & PREGf_ANCH)
        r->extflags |= RXf_IS_ANCHORED;


    {


        regnode *first = ri->program + 1;
        U8 fop = OP(first);
        regnode *next = regnext(first);
        U8 nop = OP(next);

        if (PL_regkind[fop] == NOTHING && nop == END)
            r->extflags |= RXf_NULL;
        else if ((fop == MBOL || (fop == SBOL && !first->flags)) && nop == END)


            r->extflags |= RXf_START_ONLY;
        else if (fop == PLUS
                 && PL_regkind[nop] == POSIXD && FLAGS(next) == _CC_SPACE
                 && nop == END)
            r->extflags |= RXf_WHITE;
        else if ( r->extflags & RXf_SPLIT
                  && (fop == EXACT || fop == EXACTL)
                  && STR_LEN(first) == 1
                  && *(STRING(first)) == ' '
                  && nop == END )
            r->extflags |= (RXf_SKIPWHITE|RXf_WHITE);

    }

    if (RExC_contains_locale) {
        RXp_EXTFLAGS(r) |= RXf_TAINTED;
    }

#ifdef DEBUGGING
    if (RExC_paren_names) {
        ri->name_list_idx = add_data( pRExC_state, STR_WITH_LEN("a"));
        ri->data->data[ri->name_list_idx]
                                   = (void*)SvREFCNT_inc(RExC_paren_name_list);
    } else
#endif
    ri->name_list_idx = 0;

    while ( RExC_recurse_count > 0 ) {
        const regnode *scan = RExC_recurse[ --RExC_recurse_count ];


        assert(scan && OP(scan) == GOSUB);
        ARG2L_SET( scan, RExC_open_parens[ARG(scan)] - scan );
    }

    Newxz(r->offs, RExC_npar, regexp_paren_pair);

    DEBUG_TEST_r({
        Perl_re_printf( aTHX_ "study_chunk_recursed_count: %lu\n",
            (unsigned long)RExC_study_chunk_recursed_count);
    });
    DEBUG_DUMP_r({
        DEBUG_RExC_seen();
        Perl_re_printf( aTHX_ "Final program:\n");
        regdump(r);
    });
#ifdef RE_TRACK_PATTERN_OFFSETS
    DEBUG_OFFSETS_r(if (ri->u.offsets) {
        const STRLEN len = ri->u.offsets[0];
        STRLEN i;
        GET_RE_DEBUG_FLAGS_DECL;
        Perl_re_printf( aTHX_
                      "Offsets: [%" UVuf "]\n\t", (UV)ri->u.offsets[0]);
        for (i = 1; i <= len; i++) {
            if (ri->u.offsets[i*2-1] || ri->u.offsets[i*2])
                Perl_re_printf( aTHX_  "%" UVuf ":%" UVuf "[%" UVuf "] ",
                (UV)i, (UV)ri->u.offsets[i*2-1], (UV)ri->u.offsets[i*2]);
            }
        Perl_re_printf( aTHX_  "\n");
    });
#endif

#ifdef USE_ITHREADS


    if (old_re && SvREADONLY(old_re))
        SvREADONLY_on(rx);
#endif
    return rx;
}
