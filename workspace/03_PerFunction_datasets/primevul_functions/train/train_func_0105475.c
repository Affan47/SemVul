STATIC regnode_offset
S_reg(pTHX_ RExC_state_t *pRExC_state, I32 paren, I32 *flagp, U32 depth)

{
    regnode_offset ret = 0;
    regnode_offset br;
    regnode_offset lastbr;
    regnode_offset ender = 0;
    I32 parno = 0;
    I32 flags;
    U32 oregflags = RExC_flags;
    bool have_branch = 0;
    bool is_open = 0;
    I32 freeze_paren = 0;
    I32 after_freeze = 0;
    I32 num;
    SV * max_open;

    char * parse_start = RExC_parse;
    char * const oregcomp_parse = RExC_parse;

    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REG;
    DEBUG_PARSE("reg ");

    max_open = get_sv(RE_COMPILE_RECURSION_LIMIT, GV_ADD);
    assert(max_open);
    if (!SvIOK(max_open)) {
        sv_setiv(max_open, RE_COMPILE_RECURSION_INIT);
    }
    if (depth > 4 * (UV) SvIV(max_open)) {
        vFAIL("Too many nested open parens");
    }

    *flagp = 0;

    assert(*RExC_end == '\0');

    if (paren) {

        bool has_intervening_patws = (paren == 2)
                                  && *(RExC_parse - 1) != '(';

        if (RExC_parse >= RExC_end) {
	    vFAIL("Unmatched (");
        }

        if (paren == 'r') {
            paren = '>';
            goto parse_rest;
        }
        else if ( *RExC_parse == '*') {
	    char *start_verb = RExC_parse + 1;
	    STRLEN verb_len;
	    char *start_arg = NULL;
	    unsigned char op = 0;
            int arg_required = 0;
            int internal_argval = -1;
            bool has_upper = FALSE;

            if (has_intervening_patws) {
                RExC_parse++;

                if (isUPPER(*RExC_parse)) {
                    vFAIL("In '(*VERB...)', the '(' and '*' must be adjacent");
                }
                else {
                    vFAIL("In '(*...)', the '(' and '*' must be adjacent");
                }
            }
	    while (RExC_parse < RExC_end && *RExC_parse != ')' ) {
	        if ( *RExC_parse == ':' ) {
	            start_arg = RExC_parse + 1;
	            break;
	        }
                else if (! UTF) {
                    if (isUPPER(*RExC_parse)) {
                        has_upper = TRUE;
                    }
                    RExC_parse++;
                }
                else {
                    RExC_parse += UTF8SKIP(RExC_parse);
                }
	    }
	    verb_len = RExC_parse - start_verb;
	    if ( start_arg ) {
                if (RExC_parse >= RExC_end) {
                    goto unterminated_verb_pattern;
                }

	        RExC_parse += UTF ? UTF8SKIP(RExC_parse) : 1;
	        while ( RExC_parse < RExC_end && *RExC_parse != ')' ) {
                    RExC_parse += UTF ? UTF8SKIP(RExC_parse) : 1;
                }
	        if ( RExC_parse >= RExC_end || *RExC_parse != ')' ) {
                  unterminated_verb_pattern:
                    if (has_upper) {
                        vFAIL("Unterminated verb pattern argument");
                    }
                    else {
                        vFAIL("Unterminated '(*...' argument");
                    }
                }
	    } else {
	        if ( RExC_parse >= RExC_end || *RExC_parse != ')' ) {
                    if (has_upper) {
                        vFAIL("Unterminated verb pattern");
                    }
                    else {
                        vFAIL("Unterminated '(*...' construct");
                    }
                }
	    }

	    switch ( *start_verb ) {
            case 'A':
                if ( memEQs(start_verb, verb_len,"ACCEPT") ) {
		    op = ACCEPT;
		    internal_argval = RExC_nestroot;
		}
		break;
            case 'C':
                if ( memEQs(start_verb, verb_len,"COMMIT") )
                    op = COMMIT;
                break;
            case 'F':
                if ( verb_len==1 || memEQs(start_verb, verb_len,"FAIL") ) {
		    op = OPFAIL;
		}
		break;
            case ':':
	    case 'M':
	        if ( verb_len==0 || memEQs(start_verb, verb_len,"MARK") ) {
                    op = MARKPOINT;
                    arg_required = 1;
                }
                break;
            case 'P':
                if ( memEQs(start_verb, verb_len,"PRUNE") )
                    op = PRUNE;
                break;
            case 'S':
                if ( memEQs(start_verb, verb_len,"SKIP") )
                    op = SKIP;
                break;
            case 'T':

                if ( memEQs(start_verb, verb_len,"THEN") ) {
                    op = CUTGROUP;
                    RExC_seen |= REG_CUTGROUP_SEEN;
                }
                break;
            case 'a':
                if (   memEQs(start_verb, verb_len, "asr")
                    || memEQs(start_verb, verb_len, "atomic_script_run"))
                {
                    paren = 'r';
                    goto script_run;
                }
                else if (memEQs(start_verb, verb_len, "atomic")) {
                    paren = 't';
                    goto alpha_assertions;
                }
                break;
            case 'p':
                if (   memEQs(start_verb, verb_len, "plb")
                    || memEQs(start_verb, verb_len, "positive_lookbehind"))
                {
                    paren = 'b';
                    goto lookbehind_alpha_assertions;
                }
                else if (   memEQs(start_verb, verb_len, "pla")
                         || memEQs(start_verb, verb_len, "positive_lookahead"))
                {
                    paren = 'a';
                    goto alpha_assertions;
                }
                break;
            case 'n':
                if (   memEQs(start_verb, verb_len, "nlb")
                    || memEQs(start_verb, verb_len, "negative_lookbehind"))
                {
                    paren = 'B';
                    goto lookbehind_alpha_assertions;
                }
                else if (   memEQs(start_verb, verb_len, "nla")
                         || memEQs(start_verb, verb_len, "negative_lookahead"))
                {
                    paren = 'A';
                    goto alpha_assertions;
                }
                break;
            case 's':
                if (   memEQs(start_verb, verb_len, "sr")
                    || memEQs(start_verb, verb_len, "script_run"))
                {
                    regnode_offset atomic;

                    paren = 's';

                   script_run:

                    REQUIRE_UNI_RULES(flagp, 0);

                    if (! start_arg) {
                        goto no_colon;
                    }

                    RExC_parse = start_arg;

                    if (RExC_in_script_run) {

                        ret = 0;

                        if (paren == 's') {
                            paren = ':';
                            goto parse_rest;
                        }

                        paren = '>';
                        goto parse_rest;
                    }

                    ckWARNexperimental(RExC_parse,
                        WARN_EXPERIMENTAL__SCRIPT_RUN,
                        "The script_run feature is experimental");

                    if (paren == 's') {

                        ret = reg_node(pRExC_state, SROPEN);
                        RExC_in_script_run = 1;
                        is_open = 1;
                        goto parse_rest;
                    }

                    ret = reg_node(pRExC_state, SROPEN);

                    RExC_in_script_run = 1;

                    atomic = reg(pRExC_state, 'r', &flags, depth);
                    if (flags & (RESTART_PARSE|NEED_UTF8)) {
                        *flagp = flags & (RESTART_PARSE|NEED_UTF8);
                        return 0;
                    }

                    if (! REGTAIL(pRExC_state, ret, atomic)) {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }

                    if (! REGTAIL(pRExC_state, atomic, reg_node(pRExC_state,
                                                                SRCLOSE)))
                    {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }

                    RExC_in_script_run = 0;
                    return ret;
                }

                break;

            lookbehind_alpha_assertions:
                RExC_seen |= REG_LOOKBEHIND_SEEN;
                RExC_in_lookbehind++;

            alpha_assertions:
                ckWARNexperimental(RExC_parse,
                        WARN_EXPERIMENTAL__ALPHA_ASSERTIONS,
                        "The alpha_assertions feature is experimental");

                RExC_seen_zerolen++;

                if (! start_arg) {
                    goto no_colon;
                }

                if (paren == 'A' && RExC_parse == start_arg) {
                    ret=reganode(pRExC_state, OPFAIL, 0);
                    nextchar(pRExC_state);
                    return ret;
	        }

                RExC_parse = start_arg;
                goto parse_rest;

              no_colon:
                vFAIL2utf8f(
                "'(*%" UTF8f "' requires a terminating ':'",
                UTF8fARG(UTF, verb_len, start_verb));
		NOT_REACHED;

	    }
	    if ( ! op ) {
	        RExC_parse += UTF
                              ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                              : 1;
                if (has_upper || verb_len == 0) {
                    vFAIL2utf8f(
                    "Unknown verb pattern '%" UTF8f "'",
                    UTF8fARG(UTF, verb_len, start_verb));
                }
                else {
                    vFAIL2utf8f(
                    "Unknown '(*...)' construct '%" UTF8f "'",
                    UTF8fARG(UTF, verb_len, start_verb));
                }
	    }
            if ( RExC_parse == start_arg ) {
                start_arg = NULL;
            }
            if ( arg_required && !start_arg ) {
                vFAIL3("Verb pattern '%.*s' has a mandatory argument",
                    verb_len, start_verb);
            }
            if (internal_argval == -1) {
                ret = reganode(pRExC_state, op, 0);
            } else {
                ret = reg2Lanode(pRExC_state, op, 0, internal_argval);
            }
            RExC_seen |= REG_VERBARG_SEEN;
            if (start_arg) {
                SV *sv = newSVpvn( start_arg,
                                    RExC_parse - start_arg);
                ARG(REGNODE_p(ret)) = add_data( pRExC_state,
                                        STR_WITH_LEN("S"));
                RExC_rxi->data->data[ARG(REGNODE_p(ret))]=(void*)sv;
                FLAGS(REGNODE_p(ret)) = 1;
            } else {
                FLAGS(REGNODE_p(ret)) = 0;
            }
            if ( internal_argval != -1 )
                ARG2L_SET(REGNODE_p(ret), internal_argval);
	    nextchar(pRExC_state);
	    return ret;
        }
        else if (*RExC_parse == '?') {
	    bool is_logical = 0;
	    const char * const seqstart = RExC_parse;
            const char * endptr;
            if (has_intervening_patws) {
                RExC_parse++;
                vFAIL("In '(?...)', the '(' and '?' must be adjacent");
            }

	    RExC_parse++;
            paren = *RExC_parse;
            RExC_parse += UTF ? UTF8SKIP(RExC_parse) : 1;
            if (RExC_parse > RExC_end) {
                paren = '\0';
            }
	    ret = 0;
	    switch (paren) {

	    case 'P':
	        paren = *RExC_parse;
		if ( paren == '<') {
                    RExC_parse++;
                    if (RExC_parse >= RExC_end) {
                        vFAIL("Sequence (?P<... not terminated");
                    }
		    goto named_capture;
                }
                else if (paren == '>') {
                    RExC_parse++;
                    if (RExC_parse >= RExC_end) {
                        vFAIL("Sequence (?P>... not terminated");
                    }
                    goto named_recursion;
                }
                else if (paren == '=') {
                    RExC_parse++;
                    return handle_named_backref(pRExC_state, flagp,
                                                parse_start, ')');
                }
                RExC_parse += SKIP_IF_CHAR(RExC_parse, RExC_end);

		vFAIL3("Sequence (%.*s...) not recognized",
                                RExC_parse-seqstart, seqstart);
		NOT_REACHED;
            case '<':
		if (*RExC_parse == '!')
		    paren = ',';
		else if (*RExC_parse != '=')
              named_capture:
		{
		    char *name_start;
		    SV *svname;
		    paren= '>';

            case '\'':
                    name_start = RExC_parse;
                    svname = reg_scan_name(pRExC_state, REG_RSN_RETURN_NAME);
		    if (   RExC_parse == name_start
                        || RExC_parse >= RExC_end
                        || *RExC_parse != paren)
                    {
		        vFAIL2("Sequence (?%c... not terminated",
		            paren=='>' ? '<' : paren);
                    }
		    {
			HE *he_str;
			SV *sv_dat = NULL;
                        if (!svname)
                            Perl_croak(aTHX_
                                "panic: reg_scan_name returned NULL");
                        if (!RExC_paren_names) {
                            RExC_paren_names= newHV();
                            sv_2mortal(MUTABLE_SV(RExC_paren_names));
#ifdef DEBUGGING
                            RExC_paren_name_list= newAV();
                            sv_2mortal(MUTABLE_SV(RExC_paren_name_list));
#endif
                        }
                        he_str = hv_fetch_ent( RExC_paren_names, svname, 1, 0 );
                        if ( he_str )
                            sv_dat = HeVAL(he_str);
                        if ( ! sv_dat ) {

                            Perl_croak(aTHX_
                                "panic: paren_name hash element allocation failed");
                        } else if ( SvPOK(sv_dat) ) {

                            IV count = SvIV(sv_dat);
                            I32 *pv = (I32*)SvPVX(sv_dat);
                            IV i;
                            for ( i = 0 ; i < count ; i++ ) {
                                if ( pv[i] == RExC_npar ) {
                                    count = 0;
                                    break;
                                }
                            }
                            if ( count ) {
                                pv = (I32*)SvGROW(sv_dat,
                                                SvCUR(sv_dat) + sizeof(I32)+1);
                                SvCUR_set(sv_dat, SvCUR(sv_dat) + sizeof(I32));
                                pv[count] = RExC_npar;
                                SvIV_set(sv_dat, SvIVX(sv_dat) + 1);
                            }
                        } else {
                            (void)SvUPGRADE(sv_dat, SVt_PVNV);
                            sv_setpvn(sv_dat, (char *)&(RExC_npar),
                                                                sizeof(I32));
                            SvIOK_on(sv_dat);
                            SvIV_set(sv_dat, 1);
                        }
#ifdef DEBUGGING

                        if (!av_store(RExC_paren_name_list,
                                      RExC_npar, SvREFCNT_inc_NN(svname)))
                            SvREFCNT_dec_NN(svname);
#endif

                    }
                    nextchar(pRExC_state);
		    paren = 1;
		    goto capturing_parens;
		}

                RExC_seen |= REG_LOOKBEHIND_SEEN;
		RExC_in_lookbehind++;
		RExC_parse++;
                if (RExC_parse >= RExC_end) {
                    vFAIL("Sequence (?... not terminated");
                }

	    case '=':
		RExC_seen_zerolen++;
                break;
	    case '!':
		RExC_seen_zerolen++;

                skip_to_be_ignored_text(pRExC_state, &RExC_parse,
                                        FALSE  );
	        if (*RExC_parse == ')') {
                    ret=reganode(pRExC_state, OPFAIL, 0);
	            nextchar(pRExC_state);
	            return ret;
	        }
	        break;
	    case '|':

	        paren = ':';
	        after_freeze = freeze_paren = RExC_npar;

                REQUIRE_PARENS_PASS;
	        break;
	    case ':':
	    case '>':
		break;
	    case '$':
	    case '@':
		vFAIL2("Sequence (?%c...) not implemented", (int)paren);
		break;
	    case '0' :
	    case 'R' :
                if (RExC_parse == RExC_end || *RExC_parse != ')')
		    FAIL("Sequence (?R) not terminated");
                num = 0;
                RExC_seen |= REG_RECURSE_SEEN;

                REQUIRE_PARENS_PASS;

		*flagp |= POSTPONED;
                goto gen_recurse_regop;

            case '&':
                parse_start = RExC_parse - 1;
              named_recursion:
                {
                    SV *sv_dat = reg_scan_name(pRExC_state,
                                               REG_RSN_RETURN_DATA);
                   num = sv_dat ? *((I32 *)SvPVX(sv_dat)) : 0;
                }
                if (RExC_parse >= RExC_end || *RExC_parse != ')')
                    vFAIL("Sequence (?&... not terminated");
                goto gen_recurse_regop;

            case '+':
                if (! inRANGE(RExC_parse[0], '1', '9')) {
                    RExC_parse++;
                    vFAIL("Illegal pattern");
                }
                goto parse_recursion;

            case '-':
                if (! inRANGE(RExC_parse[0], '1', '9')) {
                    RExC_parse--;
                    goto parse_flags;
                }

            case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':
	        RExC_parse = (char *) seqstart + 1;
              parse_recursion:
                {
                    bool is_neg = FALSE;
                    UV unum;
                    parse_start = RExC_parse - 1;
                    if (*RExC_parse == '-') {
                        RExC_parse++;
                        is_neg = TRUE;
                    }
                    endptr = RExC_end;
                    if (grok_atoUV(RExC_parse, &unum, &endptr)
                        && unum <= I32_MAX
                    ) {
                        num = (I32)unum;
                        RExC_parse = (char*)endptr;
                    } else
                        num = I32_MAX;
                    if (is_neg) {

                        num = -num;
                    }
                }
	        if (*RExC_parse!=')')
	            vFAIL("Expecting close bracket");

              gen_recurse_regop:
                if ( paren == '-' ) {

                    num = RExC_npar + num;
                    if (num < 1)  {

                        if (ALL_PARENS_COUNTED)  {
                            RExC_parse++;
                            vFAIL("Reference to nonexistent group");
                        }
                        else {
                            REQUIRE_PARENS_PASS;
                        }
                    }
                } else if ( paren == '+' ) {
                    num = RExC_npar + num - 1;
                }

                ret = reg2Lanode(pRExC_state, GOSUB, num, RExC_recurse_count);
                if (num >= RExC_npar) {

                    if (ALL_PARENS_COUNTED)  {
                        if (num >= RExC_total_parens) {
                            RExC_parse++;
                            vFAIL("Reference to nonexistent group");
                        }
                    }
                    else {
                        REQUIRE_PARENS_PASS;
                    }
                }
                RExC_recurse_count++;
                DEBUG_OPTIMISE_MORE_r(Perl_re_printf( aTHX_
                    "%*s%*s Recurse #%" UVuf " to %" IVdf "\n",
                            22, "|    |", (int)(depth * 2 + 1), "",
                            (UV)ARG(REGNODE_p(ret)),
                            (IV)ARG2L(REGNODE_p(ret))));
                RExC_seen |= REG_RECURSE_SEEN;

                Set_Node_Length(REGNODE_p(ret),
                                1 + regarglen[OP(REGNODE_p(ret))]);
		Set_Node_Offset(REGNODE_p(ret), parse_start);

                *flagp |= POSTPONED;
                assert(*RExC_parse == ')');
                nextchar(pRExC_state);
                return ret;

	    case '?':
		is_logical = 1;
		if (*RExC_parse != '{') {
                    RExC_parse += SKIP_IF_CHAR(RExC_parse, RExC_end);

                    vFAIL2utf8f(
                        "Sequence (%" UTF8f "...) not recognized",
                        UTF8fARG(UTF, RExC_parse-seqstart, seqstart));
		    NOT_REACHED;
		}
		*flagp |= POSTPONED;
		paren = '{';
                RExC_parse++;

	    case '{':
	    {
		U32 n = 0;
		struct reg_code_block *cb;
                OP * o;

		RExC_seen_zerolen++;

		if (   !pRExC_state->code_blocks
		    || pRExC_state->code_index
                                        >= pRExC_state->code_blocks->count
		    || pRExC_state->code_blocks->cb[pRExC_state->code_index].start
			!= (STRLEN)((RExC_parse -3 - (is_logical ? 1 : 0))
			    - RExC_start)
		) {
		    if (RExC_pm_flags & PMf_USE_RE_EVAL)
			FAIL("panic: Sequence (?{...}): no code block found\n");
		    FAIL("Eval-group not allowed at runtime, use re 'eval'");
		}

		cb = &pRExC_state->code_blocks->cb[pRExC_state->code_index];
		RExC_parse = RExC_start + cb->end;
		o = cb->block;
                if (cb->src_regex) {
                    n = add_data(pRExC_state, STR_WITH_LEN("rl"));
                    RExC_rxi->data->data[n] =
                        (void*)SvREFCNT_inc((SV*)cb->src_regex);
                    RExC_rxi->data->data[n+1] = (void*)o;
                }
                else {
                    n = add_data(pRExC_state,
                            (RExC_pm_flags & PMf_HAS_CV) ? "L" : "l", 1);
                    RExC_rxi->data->data[n] = (void*)o;
                }
		pRExC_state->code_index++;
		nextchar(pRExC_state);

		if (is_logical) {
                    regnode_offset eval;
		    ret = reg_node(pRExC_state, LOGICAL);

                    eval = reg2Lanode(pRExC_state, EVAL,
                                       n,

                                       RExC_flags & RXf_PMf_COMPILETIME
                                      );
                    FLAGS(REGNODE_p(ret)) = 2;
                    if (! REGTAIL(pRExC_state, ret, eval)) {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }

		    return ret;
		}
		ret = reg2Lanode(pRExC_state, EVAL, n, 0);
		Set_Node_Length(REGNODE_p(ret), RExC_parse - parse_start + 1);
		Set_Node_Offset(REGNODE_p(ret), parse_start);
		return ret;
	    }
	    case '(':
	    {
	        int is_define= 0;
                const int DEFINE_len = sizeof("DEFINE") - 1;
		if (    RExC_parse < RExC_end - 1
                    && (   (       RExC_parse[0] == '?'
                            && (   RExC_parse[1] == '='
                                || RExC_parse[1] == '!'
                                || RExC_parse[1] == '<'
                                || RExC_parse[1] == '{'))
		        || (       RExC_parse[0] == '*'
                            && (   memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "pla:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "plb:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "nla:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "nlb:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "positive_lookahead:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "positive_lookbehind:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "negative_lookahead:")
                                || memBEGINs(RExC_parse + 1,
                                         (Size_t) (RExC_end - (RExC_parse + 1)),
                                         "negative_lookbehind:"))))
                ) {
                    I32 flag;
                    regnode_offset tail;

                    ret = reg_node(pRExC_state, LOGICAL);
                    FLAGS(REGNODE_p(ret)) = 1;

                    tail = reg(pRExC_state, 1, &flag, depth+1);
                    RETURN_FAIL_ON_RESTART(flag, flagp);
                    if (! REGTAIL(pRExC_state, ret, tail)) {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }
                    goto insert_if;
                }
		else if (   RExC_parse[0] == '<'
		         || RExC_parse[0] == '\'' )
	        {
	            char ch = RExC_parse[0] == '<' ? '>' : '\'';
	            char *name_start= RExC_parse++;
	            U32 num = 0;
	            SV *sv_dat=reg_scan_name(pRExC_state, REG_RSN_RETURN_DATA);
	            if (   RExC_parse == name_start
                        || RExC_parse >= RExC_end
                        || *RExC_parse != ch)
                    {
                        vFAIL2("Sequence (?(%c... not terminated",
                            (ch == '>' ? '<' : ch));
                    }
                    RExC_parse++;
                    if (sv_dat) {
                        num = add_data( pRExC_state, STR_WITH_LEN("S"));
                        RExC_rxi->data->data[num]=(void*)sv_dat;
                        SvREFCNT_inc_simple_void_NN(sv_dat);
                    }
                    ret = reganode(pRExC_state, NGROUPP, num);
                    goto insert_if_check_paren;
		}
		else if (memBEGINs(RExC_parse,
                                   (STRLEN) (RExC_end - RExC_parse),
                                   "DEFINE"))
                {
		    ret = reganode(pRExC_state, DEFINEP, 0);
		    RExC_parse += DEFINE_len;
		    is_define = 1;
		    goto insert_if_check_paren;
		}
		else if (RExC_parse[0] == 'R') {
		    RExC_parse++;

		    parno = 0;
                    if (RExC_parse[0] == '0') {
                        parno = 1;
                        RExC_parse++;
                    }
                    else if (inRANGE(RExC_parse[0], '1', '9')) {
                        UV uv;
                        endptr = RExC_end;
                        if (grok_atoUV(RExC_parse, &uv, &endptr)
                            && uv <= I32_MAX
                        ) {
                            parno = (I32)uv + 1;
                            RExC_parse = (char*)endptr;
                        }

		    } else if (RExC_parse[0] == '&') {
		        SV *sv_dat;
		        RExC_parse++;
		        sv_dat = reg_scan_name(pRExC_state,
                                               REG_RSN_RETURN_DATA);
                        if (sv_dat)
                            parno = 1 + *((I32 *)SvPVX(sv_dat));
		    }
		    ret = reganode(pRExC_state, INSUBP, parno);
		    goto insert_if_check_paren;
		}
                else if (inRANGE(RExC_parse[0], '1', '9')) {

		    char c;
                    UV uv;
                    endptr = RExC_end;
                    if (grok_atoUV(RExC_parse, &uv, &endptr)
                        && uv <= I32_MAX
                    ) {
                        parno = (I32)uv;
                        RExC_parse = (char*)endptr;
                    }
                    else {
                        vFAIL("panic: grok_atoUV returned FALSE");
                    }
                    ret = reganode(pRExC_state, GROUPP, parno);

                 insert_if_check_paren:
		    if (UCHARAT(RExC_parse) != ')') {
                        RExC_parse += UTF
                                      ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                                      : 1;
			vFAIL("Switch condition not recognized");
		    }
		    nextchar(pRExC_state);
		  insert_if:
                    if (! REGTAIL(pRExC_state, ret, reganode(pRExC_state,
                                                             IFTHEN, 0)))
                    {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }
                    br = regbranch(pRExC_state, &flags, 1, depth+1);
		    if (br == 0) {
                        RETURN_FAIL_ON_RESTART(flags,flagp);
                        FAIL2("panic: regbranch returned failure, flags=%#" UVxf,
                              (UV) flags);
                    } else
                    if (! REGTAIL(pRExC_state, br, reganode(pRExC_state,
                                                             LONGJMP, 0)))
                    {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }
		    c = UCHARAT(RExC_parse);
                    nextchar(pRExC_state);
		    if (flags&HASWIDTH)
			*flagp |= HASWIDTH;
		    if (c == '|') {
		        if (is_define)
		            vFAIL("(?(DEFINE)....) does not allow branches");

                        lastbr = reganode(pRExC_state, IFTHEN, 0);

                        if (!regbranch(pRExC_state, &flags, 1, depth+1)) {
                            RETURN_FAIL_ON_RESTART(flags, flagp);
                            FAIL2("panic: regbranch returned failure, flags=%#" UVxf,
                                  (UV) flags);
                        }
                        if (! REGTAIL(pRExC_state, ret, lastbr)) {
                            REQUIRE_BRANCHJ(flagp, 0);
                        }
		 	if (flags&HASWIDTH)
			    *flagp |= HASWIDTH;
                        c = UCHARAT(RExC_parse);
                        nextchar(pRExC_state);
		    }
		    else
			lastbr = 0;
                    if (c != ')') {
                        if (RExC_parse >= RExC_end)
                            vFAIL("Switch (?(condition)... not terminated");
                        else
                            vFAIL("Switch (?(condition)... contains too many branches");
                    }
		    ender = reg_node(pRExC_state, TAIL);
                    if (! REGTAIL(pRExC_state, br, ender)) {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }
		    if (lastbr) {
                        if (! REGTAIL(pRExC_state, lastbr, ender)) {
                            REQUIRE_BRANCHJ(flagp, 0);
                        }
                        if (! REGTAIL(pRExC_state,
                                      REGNODE_OFFSET(
                                                 NEXTOPER(
                                                 NEXTOPER(REGNODE_p(lastbr)))),
                                      ender))
                        {
                            REQUIRE_BRANCHJ(flagp, 0);
                        }
		    }
		    else
                        if (! REGTAIL(pRExC_state, ret, ender)) {
                            REQUIRE_BRANCHJ(flagp, 0);
                        }
#if 0
                    RExC_size++;
#endif
		    return ret;
		}
                RExC_parse += UTF
                              ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                              : 1;
                vFAIL("Unknown switch condition (?(...))");
	    }
	    case '[':
                return handle_regex_sets(pRExC_state, NULL, flagp, depth+1,
                                         oregcomp_parse);
            case 0:
		RExC_parse--;
                vFAIL("Sequence (? incomplete");
                break;

            case ')':
                if (RExC_strict) {
                    ckWARNreg(RExC_parse, "Empty (?) without any modifiers");
                }

	    default:
	        RExC_parse = (char *) seqstart + 1;
              parse_flags:
		parse_lparen_question_flags(pRExC_state);
                if (UCHARAT(RExC_parse) != ':') {
                    if (RExC_parse < RExC_end)
                        nextchar(pRExC_state);
                    *flagp = TRYAGAIN;
                    return 0;
                }
                paren = ':';
                nextchar(pRExC_state);
                ret = 0;
                goto parse_rest;
            }
	}
	else {
            if (*RExC_parse == '{') {
                ckWARNregdep(RExC_parse + 1,
                            "Unescaped left brace in regex is "
                            "deprecated here (and will be fatal "
                            "in Perl 5.32), passed through");
            }

        if (!(RExC_flags & RXf_PMf_NOCAPTURE)) {
	  capturing_parens:
	    parno = RExC_npar;
	    RExC_npar++;
            if (! ALL_PARENS_COUNTED) {

                if (!RExC_parens_buf_size) {

                    RExC_parens_buf_size = 10;

                    Newxz(RExC_open_parens, RExC_parens_buf_size,
                            regnode_offset);
                    RExC_open_parens[0] = 1;

                    Newxz(RExC_close_parens, RExC_parens_buf_size,
                            regnode_offset);

                }
                else if (RExC_npar > RExC_parens_buf_size) {
                    I32 old_size = RExC_parens_buf_size;

                    RExC_parens_buf_size *= 2;

                    Renew(RExC_open_parens, RExC_parens_buf_size,
                            regnode_offset);
                    Zero(RExC_open_parens + old_size,
                            RExC_parens_buf_size - old_size, regnode_offset);

                    Renew(RExC_close_parens, RExC_parens_buf_size,
                            regnode_offset);
                    Zero(RExC_close_parens + old_size,
                            RExC_parens_buf_size - old_size, regnode_offset);
                }
            }

	    ret = reganode(pRExC_state, OPEN, parno);
            if (!RExC_nestroot)
                RExC_nestroot = parno;
            if (RExC_open_parens && !RExC_open_parens[parno])
            {
                DEBUG_OPTIMISE_MORE_r(Perl_re_printf( aTHX_
                    "%*s%*s Setting open paren #%" IVdf " to %d\n",
                    22, "|    |", (int)(depth * 2 + 1), "",
                    (IV)parno, ret));
                RExC_open_parens[parno]= ret;
            }

            Set_Node_Length(REGNODE_p(ret), 1);
            Set_Node_Offset(REGNODE_p(ret), RExC_parse);
	    is_open = 1;
	} else {

            paren = ':';
	    ret = 0;
	}
        }
    }
    else
	ret = 0;

   parse_rest:

    parse_start = RExC_parse;
    br = regbranch(pRExC_state, &flags, 1, depth+1);

    if (br == 0) {
        RETURN_FAIL_ON_RESTART(flags, flagp);
        FAIL2("panic: regbranch returned failure, flags=%#" UVxf, (UV) flags);
    }
    if (*RExC_parse == '|') {
	if (RExC_use_BRANCHJ) {
	    reginsert(pRExC_state, BRANCHJ, br, depth+1);
	}
	else {
	    reginsert(pRExC_state, BRANCH, br, depth+1);
            Set_Node_Length(REGNODE_p(br), paren != 0);
            Set_Node_Offset_To_R(br, parse_start-RExC_start);
        }
	have_branch = 1;
    }
    else if (paren == ':') {
	*flagp |= flags&SIMPLE;
    }
    if (is_open) {
        if (! REGTAIL(pRExC_state, ret, br)) {
            REQUIRE_BRANCHJ(flagp, 0);
        }
    }
    else if (paren != '?')
	ret = br;
    *flagp |= flags & (SPSTART | HASWIDTH | POSTPONED);
    lastbr = br;
    while (*RExC_parse == '|') {
	if (RExC_use_BRANCHJ) {
            bool shut_gcc_up;

	    ender = reganode(pRExC_state, LONGJMP, 0);

            shut_gcc_up = REGTAIL(pRExC_state,
                         REGNODE_OFFSET(NEXTOPER(NEXTOPER(REGNODE_p(lastbr)))),
                         ender);
            PERL_UNUSED_VAR(shut_gcc_up);
	}
	nextchar(pRExC_state);
	if (freeze_paren) {
	    if (RExC_npar > after_freeze)
	        after_freeze = RExC_npar;
            RExC_npar = freeze_paren;
        }
        br = regbranch(pRExC_state, &flags, 0, depth+1);

	if (br == 0) {
            RETURN_FAIL_ON_RESTART(flags, flagp);
            FAIL2("panic: regbranch returned failure, flags=%#" UVxf, (UV) flags);
        }
        if (!  REGTAIL(pRExC_state, lastbr, br)) {
            REQUIRE_BRANCHJ(flagp, 0);
        }
	lastbr = br;
	*flagp |= flags & (SPSTART | HASWIDTH | POSTPONED);
    }

    if (have_branch || paren != ':') {
        regnode * br;

	switch (paren) {
	case ':':
	    ender = reg_node(pRExC_state, TAIL);
	    break;
	case 1: case 2:
	    ender = reganode(pRExC_state, CLOSE, parno);
            if ( RExC_close_parens ) {
                DEBUG_OPTIMISE_MORE_r(Perl_re_printf( aTHX_
                        "%*s%*s Setting close paren #%" IVdf " to %d\n",
                        22, "|    |", (int)(depth * 2 + 1), "",
                        (IV)parno, ender));
                RExC_close_parens[parno]= ender;
	        if (RExC_nestroot == parno)
	            RExC_nestroot = 0;
	    }
            Set_Node_Offset(REGNODE_p(ender), RExC_parse+1);
            Set_Node_Length(REGNODE_p(ender), 1);
	    break;
	case 's':
	    ender = reg_node(pRExC_state, SRCLOSE);
            RExC_in_script_run = 0;
	    break;
	case '<':
        case 'a':
        case 'A':
        case 'b':
        case 'B':
	case ',':
	case '=':
	case '!':
	    *flagp &= ~HASWIDTH;

        case 't':
	case '>':
	    ender = reg_node(pRExC_state, SUCCEED);
	    break;
	case 0:
	    ender = reg_node(pRExC_state, END);
            assert(!RExC_end_op);
            RExC_end_op = REGNODE_p(ender);
            if (RExC_close_parens) {
                DEBUG_OPTIMISE_MORE_r(Perl_re_printf( aTHX_
                    "%*s%*s Setting close paren #0 (END) to %d\n",
                    22, "|    |", (int)(depth * 2 + 1), "",
                    ender));

                RExC_close_parens[0]= ender;
            }
	    break;
	}
        DEBUG_PARSE_r({
            DEBUG_PARSE_MSG("lsbr");
            regprop(RExC_rx, RExC_mysv1, REGNODE_p(lastbr), NULL, pRExC_state);
            regprop(RExC_rx, RExC_mysv2, REGNODE_p(ender), NULL, pRExC_state);
            Perl_re_printf( aTHX_  "~ tying lastbr %s (%" IVdf ") to ender %s (%" IVdf ") offset %" IVdf "\n",
                          SvPV_nolen_const(RExC_mysv1),
                          (IV)lastbr,
                          SvPV_nolen_const(RExC_mysv2),
                          (IV)ender,
                          (IV)(ender - lastbr)
            );
        });
        if (! REGTAIL(pRExC_state, lastbr, ender)) {
            REQUIRE_BRANCHJ(flagp, 0);
        }

	if (have_branch) {
            char is_nothing= 1;
	    if (depth==1)
                RExC_seen |= REG_TOP_LEVEL_BRANCHES_SEEN;

	    for (br = REGNODE_p(ret); br; br = regnext(br)) {
		const U8 op = PL_regkind[OP(br)];
		if (op == BRANCH) {
                    if (! REGTAIL_STUDY(pRExC_state,
                                        REGNODE_OFFSET(NEXTOPER(br)),
                                        ender))
                    {
                        REQUIRE_BRANCHJ(flagp, 0);
                    }
                    if ( OP(NEXTOPER(br)) != NOTHING
                         || regnext(NEXTOPER(br)) != REGNODE_p(ender))
                        is_nothing= 0;
		}
		else if (op == BRANCHJ) {
                    bool shut_gcc_up = REGTAIL_STUDY(pRExC_state,
                                        REGNODE_OFFSET(NEXTOPER(NEXTOPER(br))),
                                        ender);
                    PERL_UNUSED_VAR(shut_gcc_up);

                        is_nothing= 0;
		}
	    }
            if (is_nothing) {
                regnode * ret_as_regnode = REGNODE_p(ret);
                br= PL_regkind[OP(ret_as_regnode)] != BRANCH
                               ? regnext(ret_as_regnode)
                               : ret_as_regnode;
                DEBUG_PARSE_r({
                    DEBUG_PARSE_MSG("NADA");
                    regprop(RExC_rx, RExC_mysv1, ret_as_regnode,
                                     NULL, pRExC_state);
                    regprop(RExC_rx, RExC_mysv2, REGNODE_p(ender),
                                     NULL, pRExC_state);
                    Perl_re_printf( aTHX_  "~ converting ret %s (%" IVdf ") to ender %s (%" IVdf ") offset %" IVdf "\n",
                                  SvPV_nolen_const(RExC_mysv1),
                                  (IV)REG_NODE_NUM(ret_as_regnode),
                                  SvPV_nolen_const(RExC_mysv2),
                                  (IV)ender,
                                  (IV)(ender - ret)
                    );
                });
                OP(br)= NOTHING;
                if (OP(REGNODE_p(ender)) == TAIL) {
                    NEXT_OFF(br)= 0;
                    RExC_emit= REGNODE_OFFSET(br) + 1;
                } else {
                    regnode *opt;
                    for ( opt= br + 1; opt < REGNODE_p(ender) ; opt++ )
                        OP(opt)= OPTIMIZED;
                    NEXT_OFF(br)= REGNODE_p(ender) - br;
                }
            }
	}
    }

    {
        const char *p;

        static const char parens[] = "=!aA<,>Bbt";

	if (paren && (p = strchr(parens, paren))) {
	    U8 node = ((p - parens) % 2) ? UNLESSM : IFMATCH;
	    int flag = (p - parens) > 3;

	    if (paren == '>' || paren == 't') {
		node = SUSPEND, flag = 0;
            }

	    reginsert(pRExC_state, node, ret, depth+1);
            Set_Node_Cur_Length(REGNODE_p(ret), parse_start);
	    Set_Node_Offset(REGNODE_p(ret), parse_start + 1);
	    FLAGS(REGNODE_p(ret)) = flag;
            if (! REGTAIL_STUDY(pRExC_state, ret, reg_node(pRExC_state, TAIL)))
            {
                REQUIRE_BRANCHJ(flagp, 0);
            }
	}
    }

    if (paren) {

	RExC_flags = oregflags | (RExC_flags & RXf_PMf_KEEPCOPY);
        if (DEPENDS_SEMANTICS && RExC_uni_semantics) {
            set_regex_charset(&RExC_flags, REGEX_UNICODE_CHARSET);
        }
	if (RExC_parse >= RExC_end || UCHARAT(RExC_parse) != ')') {
	    RExC_parse = oregcomp_parse;
	    vFAIL("Unmatched (");
	}
	nextchar(pRExC_state);
    }
    else if (!paren && RExC_parse < RExC_end) {
	if (*RExC_parse == ')') {
	    RExC_parse++;
	    vFAIL("Unmatched )");
	}
	else
	    FAIL("Junk on end of regexp");
	NOT_REACHED;
    }

    if (RExC_in_lookbehind) {
	RExC_in_lookbehind--;
    }
    if (after_freeze > RExC_npar)
        RExC_npar = after_freeze;
    return(ret);
}
}
}
}
}
}
