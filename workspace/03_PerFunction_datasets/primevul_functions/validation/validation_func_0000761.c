REGEXP *
Perl_re_op_compile(pTHX_ SV ** const patternp, int pat_count,
		    OP *expr, const regexp_engine* eng, REGEXP *old_re,
		     bool *is_bare_re, const U32 orig_rx_flags, const U32 pm_flags)
{
    dVAR;
    REGEXP *Rx;
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


    if (! PL_InBitmap) {
#ifdef DEBUGGING
        char * dump_len_string;
#endif


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
    pRExC_state->unlexed_names = NULL;
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
    RExC_contains_locale = 0;
    RExC_strict = cBOOL(pm_flags & RXf_PMf_STRICT);
    RExC_in_script_run = 0;
    RExC_study_started = 0;
    pRExC_state->runtime_code_qr = NULL;
    RExC_frame_head= NULL;
    RExC_frame_last= NULL;
    RExC_frame_count= 0;
    RExC_latest_warn_offset = 0;
    RExC_use_BRANCHJ = 0;
    RExC_total_parens = 0;
    RExC_open_parens = NULL;
    RExC_close_parens = NULL;
    RExC_paren_names = NULL;
    RExC_size = 0;
    RExC_seen_d_op = FALSE;
#ifdef DEBUGGING
    RExC_paren_name_list = NULL;
#endif

    DEBUG_r({
        RExC_mysv1= sv_newmortal();
        RExC_mysv2= sv_newmortal();
    });

    DEBUG_COMPILE_r({
            SV *dsv= sv_newmortal();
            RE_PV_QUOTED_DECL(s, RExC_utf8, dsv, exp, plen, PL_dump_re_max_len);
            Perl_re_printf( aTHX_  "%sCompiling REx%s %s\n",
                          PL_colors[4], PL_colors[5], s);
        });


    if ((pm_flags & PMf_USE_RE_EVAL)


		|| (IN_PERL_COMPILETIME && (PL_hints & HINT_RE_EVAL))
    )
	runtime_code = S_has_runtime_code(aTHX_ pRExC_state, exp, plen);

  redo_parse:


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


    RExC_rx_sv = Rx = (REGEXP*) newSV_type(SVt_REGEXP);
    RExC_rx = ReANY(Rx);
    if ( RExC_rx == NULL )
        FAIL("Regexp out of space");

    rx_flags = orig_rx_flags;

    if (   (UTF || RExC_uni_semantics)
        && initial_charset == REGEX_DEPENDS_CHARSET)
    {


	set_regex_charset(&rx_flags, REGEX_UNICODE_CHARSET);
        RExC_uni_semantics = 1;
    }

    RExC_pm_flags = pm_flags;

    if (runtime_code) {
        assert(TAINTING_get || !TAINT_get);
	if (TAINT_get)
	    Perl_croak(aTHX_ "Eval-group in insecure regular expression");

	if (!S_compile_runtime_code(aTHX_ pRExC_state, exp, plen)) {


            S_pat_upgrade_to_utf8(aTHX_ pRExC_state, &exp, &plen,
                pRExC_state->code_blocks ? pRExC_state->code_blocks->count : 0);
            goto redo_parse;
	}
    }
    assert(!pRExC_state->runtime_code_qr);

    RExC_sawback = 0;

    RExC_seen = 0;
    RExC_maxlen = 0;
    RExC_in_lookbehind = 0;
    RExC_seen_zerolen = *exp == '^' ? -1 : 0;
#ifdef EBCDIC
    RExC_recode_x_to_native = 0;
#endif
    RExC_in_multi_char_class = 0;

    RExC_start = RExC_copy_start_in_constructed = RExC_copy_start_in_input = RExC_precomp = exp;
    RExC_precomp_end = RExC_end = exp + plen;
    RExC_nestroot = 0;
    RExC_whilem_seen = 0;
    RExC_end_op = NULL;
    RExC_recurse = NULL;
    RExC_study_chunk_recursed = NULL;
    RExC_study_chunk_recursed_bytes= 0;
    RExC_recurse_count = 0;
    pRExC_state->code_index = 0;


    set_regex_pv(pRExC_state, Rx);

    DEBUG_PARSE_r({
        Perl_re_printf( aTHX_
            "Starting parse and generation\n");
        RExC_lastnum=0;
        RExC_lastparse=NULL;
    });


    if (!  RExC_size) {


        RExC_size = STR_SZ(RExC_end - RExC_start);
    }

    Newxc(RExC_rxi, sizeof(regexp_internal) + RExC_size, char, regexp_internal);
    if ( RExC_rxi == NULL )
        FAIL("Regexp out of space");

    Zero(RExC_rxi, sizeof(regexp_internal) + RExC_size, char);
    RXi_SET( RExC_rx, RExC_rxi );


    RExC_size = 0;


    RExC_rx->engine= eng;
    RExC_rx->extflags = rx_flags;
    RXp_COMPFLAGS(RExC_rx) = orig_rx_flags & RXf_PMf_FLAGCOPYMASK;

    if (pm_flags & PMf_IS_QR) {
	RExC_rxi->code_blocks = pRExC_state->code_blocks;
        if (RExC_rxi->code_blocks) {
            RExC_rxi->code_blocks->refcnt++;
        }
    }

    RExC_rx->intflags = 0;

    RExC_flags = rx_flags;
    RExC_parse = exp;


    assert(*RExC_end == '\0');

    RExC_naughty = 0;
    RExC_npar = 1;
    RExC_parens_buf_size = 0;
    RExC_emit_start = RExC_rxi->program;
    pRExC_state->code_index = 0;

    *((char*) RExC_emit_start) = (char) REG_MAGIC;
    RExC_emit = 1;


    if (reg(pRExC_state, 0, &flags, 1)) {


        if (IN_PARENS_PASS) {
            flags |= RESTART_PARSE;
        }


        RExC_total_parens = RExC_npar;
    }
    else if (! MUST_RESTART(flags)) {
	ReREFCNT_dec(Rx);
        Perl_croak(aTHX_ "panic: reg returned failure to re_op_compile, flags=%#" UVxf, (UV) flags);
    }


    if (MUST_RESTART(flags)) {


        if (flags & NEED_UTF8) {


            if (UNLIKELY(RExC_latest_warn_offset > 0)) {
                RExC_latest_warn_offset +=
                            variant_under_utf8_count((U8 *) exp, (U8 *) exp
                                                + RExC_latest_warn_offset);
            }
            S_pat_upgrade_to_utf8(aTHX_ pRExC_state, &exp, &plen,
            pRExC_state->code_blocks ? pRExC_state->code_blocks->count : 0);
            DEBUG_PARSE_r(Perl_re_printf( aTHX_ "Need to redo parse after upgrade\n"));
        }
        else {
            DEBUG_PARSE_r(Perl_re_printf( aTHX_ "Need to redo parse\n"));
        }

        if (ALL_PARENS_COUNTED) {

            Renew(RExC_open_parens, RExC_total_parens, regnode_offset);
            Zero(RExC_open_parens, RExC_total_parens, regnode_offset);
            RExC_open_parens[0] = 1;

            Renew(RExC_close_parens, RExC_total_parens, regnode_offset);
            Zero(RExC_close_parens, RExC_total_parens, regnode_offset);
        }
        else {

            RExC_total_parens = 0;
            if (RExC_open_parens) {
                Safefree(RExC_open_parens);
                RExC_open_parens = NULL;
            }
            if (RExC_close_parens) {
                Safefree(RExC_close_parens);
                RExC_close_parens = NULL;
            }
        }


        SvREFCNT_dec_NN(RExC_rx_sv);

        goto redo_parse;
    }


    set_regex_pv(pRExC_state, Rx);

    RExC_rx->nparens = RExC_total_parens - 1;


    if (RExC_whilem_seen > 15)
        RExC_whilem_seen = 15;

    DEBUG_PARSE_r({
        Perl_re_printf( aTHX_
            "Required size %" IVdf " nodes\n", (IV)RExC_size);
        RExC_lastnum=0;
        RExC_lastparse=NULL;
    });

#ifdef RE_TRACK_PATTERN_OFFSETS
    DEBUG_OFFSETS_r(Perl_re_printf( aTHX_
                          "%s %" UVuf " bytes for offset annotations.\n",
                          RExC_offsets ? "Got" : "Couldn't get",
                          (UV)((RExC_offsets[0] * 2 + 1))));
    DEBUG_OFFSETS_r(if (RExC_offsets) {
        const STRLEN len = RExC_offsets[0];
        STRLEN i;
        GET_RE_DEBUG_FLAGS_DECL;
        Perl_re_printf( aTHX_
                      "Offsets: [%" UVuf "]\n\t", (UV)RExC_offsets[0]);
        for (i = 1; i <= len; i++) {
            if (RExC_offsets[i*2-1] || RExC_offsets[i*2])
                Perl_re_printf( aTHX_  "%" UVuf ":%" UVuf "[%" UVuf "] ",
                (UV)i, (UV)RExC_offsets[i*2-1], (UV)RExC_offsets[i*2]);
        }
        Perl_re_printf( aTHX_  "\n");
    });

#else
    SetProgLen(RExC_rxi,RExC_size);
#endif

    DEBUG_OPTIMISE_r(
        Perl_re_printf( aTHX_  "Starting post parse optimization\n");
    );


    Newx(RExC_rx->substrs, 1, struct reg_substr_data);
    if (RExC_recurse_count) {
        Newx(RExC_recurse, RExC_recurse_count, regnode *);
        SAVEFREEPV(RExC_recurse);
    }

    if (RExC_seen & REG_RECURSE_SEEN) {


        RExC_study_chunk_recursed_bytes= (RExC_total_parens >> 3) +
                                         ((RExC_total_parens & 0x07) != 0);
        Newx(RExC_study_chunk_recursed,
             RExC_study_chunk_recursed_bytes * RExC_total_parens, U8);
        SAVEFREEPV(RExC_study_chunk_recursed);
    }

  reStudy:
    RExC_rx->minlen = minlen = sawlookahead = sawplus = sawopen = sawminmod = 0;
    DEBUG_r(
        RExC_study_chunk_recursed_count= 0;
    );
    Zero(RExC_rx->substrs, 1, struct reg_substr_data);
    if (RExC_study_chunk_recursed) {
        Zero(RExC_study_chunk_recursed,
             RExC_study_chunk_recursed_bytes * RExC_total_parens, U8);
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


    RExC_rx->extflags = RExC_flags;


    if (UTF)
	SvUTF8_on(Rx);
    RExC_rxi->regstclass = NULL;
    if (RExC_naughty >= TOO_NAUGHTY)
	RExC_rx->intflags |= PREGf_NAUGHTY;
    scan = RExC_rxi->program + 1;


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
	    if (   OP(first) == EXACT
                || OP(first) == EXACT_ONLY8
                || OP(first) == EXACTL)
            {
		NOOP;
            }
	    else
		RExC_rxi->regstclass = first;
	}
#ifdef TRIE_STCLASS
	else if (PL_regkind[OP(first)] == TRIE &&
	        ((reg_trie_data *)RExC_rxi->data->data[ ARG(first) ])->minlen>0)
	{

            RExC_rxi->regstclass = construct_ahocorasick_from_trie(pRExC_state, (regnode *)first, 0);
	}
#endif
	else if (REGNODE_SIMPLE(OP(first)))
	    RExC_rxi->regstclass = first;
	else if (PL_regkind[OP(first)] == BOUND ||
		 PL_regkind[OP(first)] == NBOUND)
	    RExC_rxi->regstclass = first;
	else if (PL_regkind[OP(first)] == BOL) {
            RExC_rx->intflags |= (OP(first) == MBOL
                           ? PREGf_ANCH_MBOL
                           : PREGf_ANCH_SBOL);
	    first = NEXTOPER(first);
	    goto again;
	}
	else if (OP(first) == GPOS) {
            RExC_rx->intflags |= PREGf_ANCH_GPOS;
	    first = NEXTOPER(first);
	    goto again;
	}
	else if ((!sawopen || !RExC_sawback) &&
            !sawlookahead &&
	    (OP(first) == STAR &&
	    PL_regkind[OP(NEXTOPER(first))] == REG_ANY) &&
            !(RExC_rx->intflags & PREGf_ANCH) && !pRExC_state->code_blocks)
	{

	    const int type =
		(OP(NEXTOPER(first)) == REG_ANY)
                    ? PREGf_ANCH_MBOL
                    : PREGf_ANCH_SBOL;
            RExC_rx->intflags |= (type | PREGf_IMPLICIT);
	    first = NEXTOPER(first);
	    goto again;
	}
        if (sawplus && !sawminmod && !sawlookahead
            && (!sawopen || !RExC_sawback)
	    && !pRExC_state->code_blocks)

	    RExC_rx->intflags |= PREGf_SKIP;


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
	if (!RExC_rxi->regstclass) {
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


	if ( RExC_total_parens == 1 && !data.cur_is_floating
	     && data.last_start_min == 0 && data.last_end > 0
	     && !RExC_seen_zerolen
             && !(RExC_seen & REG_VERBARG_SEEN)
             && !(RExC_seen & REG_GPOS_SEEN)
        ){
	    RExC_rx->extflags |= RXf_CHECK_ALL;
        }
	scan_commit(pRExC_state, &data,&minlen, 0);


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
                                        &(RExC_rx->substrs->data[i]),
                                        &(data.substrs[i]),
                                        longest_length[i]))
            {
                RExC_rx->substrs->data[i].min_offset =
                        data.substrs[i].min_offset - data.substrs[i].lookbehind;

                RExC_rx->substrs->data[i].max_offset = data.substrs[i].max_offset;

                if (data.substrs[i].max_offset < SSize_t_MAX)
                    RExC_rx->substrs->data[i].max_offset -= data.substrs[i].lookbehind;
                SvREFCNT_inc_simple_void_NN(data.substrs[i].str);
            }
            else {
                RExC_rx->substrs->data[i].substr      = NULL;
                RExC_rx->substrs->data[i].utf8_substr = NULL;
                longest_length[i] = 0;
            }
        }

	LEAVE_with_name("study_chunk");

	if (RExC_rxi->regstclass
	    && (OP(RExC_rxi->regstclass) == REG_ANY || OP(RExC_rxi->regstclass) == SANY))
	    RExC_rxi->regstclass = NULL;

	if ((!(RExC_rx->substrs->data[0].substr || RExC_rx->substrs->data[0].utf8_substr)
              || RExC_rx->substrs->data[0].min_offset)
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
	    RExC_rxi->regstclass = (regnode*)RExC_rxi->data->data[n];
	    RExC_rx->intflags &= ~PREGf_SKIP;
	    DEBUG_COMPILE_r({ SV *sv = sv_newmortal();
                      regprop(RExC_rx, sv, (regnode*)data.start_class, NULL, pRExC_state);
                      Perl_re_printf( aTHX_
				    "synthetic stclass \"%s\".\n",
				    SvPVX_const(sv));});
            data.start_class = NULL;
	}


	i = (longest_length[0] <= longest_length[1]);
        RExC_rx->substrs->check_ix = i;
        RExC_rx->check_end_shift  = RExC_rx->substrs->data[i].end_shift;
        RExC_rx->check_substr     = RExC_rx->substrs->data[i].substr;
        RExC_rx->check_utf8       = RExC_rx->substrs->data[i].utf8_substr;
        RExC_rx->check_offset_min = RExC_rx->substrs->data[i].min_offset;
        RExC_rx->check_offset_max = RExC_rx->substrs->data[i].max_offset;
        if (!i && (RExC_rx->intflags & (PREGf_ANCH_SBOL|PREGf_ANCH_GPOS)))
            RExC_rx->intflags |= PREGf_NOSCAN;

	if ((RExC_rx->check_substr || RExC_rx->check_utf8) ) {
	    RExC_rx->extflags |= RXf_USE_INTUIT;
	    if (SvTAIL(RExC_rx->check_substr ? RExC_rx->check_substr : RExC_rx->check_utf8))
		RExC_rx->extflags |= RXf_INTUIT_TAIL;
	}


    }
    else {

	SSize_t fake;
	regnode_ssc ch_class;
	SSize_t last_close = 0;

        DEBUG_PARSE_r(Perl_re_printf( aTHX_  "\nMulti Top Level\n"));

	scan = RExC_rxi->program + 1;
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

	RExC_rx->check_substr = NULL;
        RExC_rx->check_utf8 = NULL;
        RExC_rx->substrs->data[0].substr      = NULL;
        RExC_rx->substrs->data[0].utf8_substr = NULL;
        RExC_rx->substrs->data[1].substr      = NULL;
        RExC_rx->substrs->data[1].utf8_substr = NULL;

        if (! (ANYOF_FLAGS(data.start_class) & SSC_MATCHES_EMPTY_STRING)
	    && is_ssc_worth_it(pRExC_state, data.start_class))
        {
	    const U32 n = add_data(pRExC_state, STR_WITH_LEN("f"));

            ssc_finalize(pRExC_state, data.start_class);

	    Newx(RExC_rxi->data->data[n], 1, regnode_ssc);
	    StructCopy(data.start_class,
		       (regnode_ssc*)RExC_rxi->data->data[n],
		       regnode_ssc);
	    RExC_rxi->regstclass = (regnode*)RExC_rxi->data->data[n];
	    RExC_rx->intflags &= ~PREGf_SKIP;
	    DEBUG_COMPILE_r({ SV* sv = sv_newmortal();
                      regprop(RExC_rx, sv, (regnode*)data.start_class, NULL, pRExC_state);
                      Perl_re_printf( aTHX_
				    "synthetic stclass \"%s\".\n",
				    SvPVX_const(sv));});
            data.start_class = NULL;
	}
    }

    if (RExC_seen & REG_UNBOUNDED_QUANTIFIER_SEEN) {
        RExC_rx->extflags |= RXf_UNBOUNDED_QUANTIFIER_SEEN;
        RExC_rx->maxlen = REG_INFTY;
    }
    else {
        RExC_rx->maxlen = RExC_maxlen;
    }


    DEBUG_OPTIMISE_r({
        Perl_re_printf( aTHX_ "minlen: %" IVdf " RExC_rx->minlen:%" IVdf " maxlen:%" IVdf "\n",
                      (IV)minlen, (IV)RExC_rx->minlen, (IV)RExC_maxlen);
    });
    RExC_rx->minlenret = minlen;
    if (RExC_rx->minlen < minlen)
        RExC_rx->minlen = minlen;

    if (RExC_seen & REG_RECURSE_SEEN ) {
        RExC_rx->intflags |= PREGf_RECURSE_SEEN;
        Newx(RExC_rx->recurse_locinput, RExC_rx->nparens + 1, char *);
    }
    if (RExC_seen & REG_GPOS_SEEN)
        RExC_rx->intflags |= PREGf_GPOS_SEEN;
    if (RExC_seen & REG_LOOKBEHIND_SEEN)
        RExC_rx->extflags |= RXf_NO_INPLACE_SUBST;

    if (pRExC_state->code_blocks)
	RExC_rx->extflags |= RXf_EVAL_SEEN;
    if (RExC_seen & REG_VERBARG_SEEN)
    {
	RExC_rx->intflags |= PREGf_VERBARG_SEEN;
        RExC_rx->extflags |= RXf_NO_INPLACE_SUBST;
    }
    if (RExC_seen & REG_CUTGROUP_SEEN)
	RExC_rx->intflags |= PREGf_CUTGROUP_SEEN;
    if (pm_flags & PMf_USE_RE_EVAL)
	RExC_rx->intflags |= PREGf_USE_RE_EVAL;
    if (RExC_paren_names)
        RXp_PAREN_NAMES(RExC_rx) = MUTABLE_HV(SvREFCNT_inc(RExC_paren_names));
    else
        RXp_PAREN_NAMES(RExC_rx) = NULL;


    if (RExC_rx->intflags & PREGf_ANCH)
        RExC_rx->extflags |= RXf_IS_ANCHORED;


    {


        regnode *first = RExC_rxi->program + 1;
        U8 fop = OP(first);
        regnode *next = regnext(first);
        U8 nop = OP(next);

        if (PL_regkind[fop] == NOTHING && nop == END)
            RExC_rx->extflags |= RXf_NULL;
        else if ((fop == MBOL || (fop == SBOL && !first->flags)) && nop == END)


            RExC_rx->extflags |= RXf_START_ONLY;
        else if (fop == PLUS
                 && PL_regkind[nop] == POSIXD && FLAGS(next) == _CC_SPACE
                 && nop == END)
            RExC_rx->extflags |= RXf_WHITE;
        else if ( RExC_rx->extflags & RXf_SPLIT
                  && (fop == EXACT || fop == EXACT_ONLY8 || fop == EXACTL)
                  && STR_LEN(first) == 1
                  && *(STRING(first)) == ' '
                  && nop == END )
            RExC_rx->extflags |= (RXf_SKIPWHITE|RXf_WHITE);

    }

    if (RExC_contains_locale) {
        RXp_EXTFLAGS(RExC_rx) |= RXf_TAINTED;
    }

#ifdef DEBUGGING
    if (RExC_paren_names) {
        RExC_rxi->name_list_idx = add_data( pRExC_state, STR_WITH_LEN("a"));
        RExC_rxi->data->data[RExC_rxi->name_list_idx]
                                   = (void*)SvREFCNT_inc(RExC_paren_name_list);
    } else
#endif
    RExC_rxi->name_list_idx = 0;

    while ( RExC_recurse_count > 0 ) {
        const regnode *scan = RExC_recurse[ --RExC_recurse_count ];


        assert(scan && OP(scan) == GOSUB);
        ARG2L_SET( scan, RExC_open_parens[ARG(scan)] - REGNODE_OFFSET(scan));
    }

    Newxz(RExC_rx->offs, RExC_total_parens, regexp_paren_pair);

    DEBUG_TEST_r({
        Perl_re_printf( aTHX_ "study_chunk_recursed_count: %lu\n",
            (unsigned long)RExC_study_chunk_recursed_count);
    });
    DEBUG_DUMP_r({
        DEBUG_RExC_seen();
        Perl_re_printf( aTHX_ "Final program:\n");
        regdump(RExC_rx);
    });

    if (RExC_open_parens) {
        Safefree(RExC_open_parens);
        RExC_open_parens = NULL;
    }
    if (RExC_close_parens) {
        Safefree(RExC_close_parens);
        RExC_close_parens = NULL;
    }

#ifdef USE_ITHREADS


    if (old_re && SvREADONLY(old_re))
        SvREADONLY_on(Rx);
#endif
    return Rx;
}
