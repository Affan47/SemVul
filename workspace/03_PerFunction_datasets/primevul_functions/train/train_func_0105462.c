STATIC regnode_offset
S_regatom(pTHX_ RExC_state_t *pRExC_state, I32 *flagp, U32 depth)
{
    dVAR;
    regnode_offset ret = 0;
    I32 flags = 0;
    char *parse_start;
    U8 op;
    int invert = 0;
    U8 arg;

    GET_RE_DEBUG_FLAGS_DECL;

    *flagp = WORST;

    DEBUG_PARSE("atom");

    PERL_ARGS_ASSERT_REGATOM;

  tryagain:
    parse_start = RExC_parse;
    assert(RExC_parse < RExC_end);
    switch ((U8)*RExC_parse) {
    case '^':
	RExC_seen_zerolen++;
	nextchar(pRExC_state);
	if (RExC_flags & RXf_PMf_MULTILINE)
	    ret = reg_node(pRExC_state, MBOL);
	else
	    ret = reg_node(pRExC_state, SBOL);
        Set_Node_Length(REGNODE_p(ret), 1);
	break;
    case '$':
	nextchar(pRExC_state);
	if (*RExC_parse)
	    RExC_seen_zerolen++;
	if (RExC_flags & RXf_PMf_MULTILINE)
	    ret = reg_node(pRExC_state, MEOL);
	else
	    ret = reg_node(pRExC_state, SEOL);
        Set_Node_Length(REGNODE_p(ret), 1);
	break;
    case '.':
	nextchar(pRExC_state);
	if (RExC_flags & RXf_PMf_SINGLELINE)
	    ret = reg_node(pRExC_state, SANY);
	else
	    ret = reg_node(pRExC_state, REG_ANY);
	*flagp |= HASWIDTH|SIMPLE;
	MARK_NAUGHTY(1);
        Set_Node_Length(REGNODE_p(ret), 1);
	break;
    case '[':
    {
	char * const oregcomp_parse = ++RExC_parse;
        ret = regclass(pRExC_state, flagp, depth+1,
                       FALSE,
                       TRUE,
                       FALSE,
                       (bool) RExC_strict,
                       TRUE,
                       NULL);
        if (ret == 0) {
            RETURN_FAIL_ON_RESTART_FLAGP(flagp);
            FAIL2("panic: regclass returned failure to regatom, flags=%#" UVxf,
                  (UV) *flagp);
        }
	if (*RExC_parse != ']') {
	    RExC_parse = oregcomp_parse;
	    vFAIL("Unmatched [");
	}
	nextchar(pRExC_state);
        Set_Node_Length(REGNODE_p(ret), RExC_parse - oregcomp_parse + 1);
	break;
    }
    case '(':
	nextchar(pRExC_state);
        ret = reg(pRExC_state, 2, &flags, depth+1);
	if (ret == 0) {
		if (flags & TRYAGAIN) {
		    if (RExC_parse >= RExC_end) {

			*flagp |= TRYAGAIN;
			return(0);
		    }
		    goto tryagain;
		}
                RETURN_FAIL_ON_RESTART(flags, flagp);
                FAIL2("panic: reg returned failure to regatom, flags=%#" UVxf,
                                                                 (UV) flags);
	}
	*flagp |= flags&(HASWIDTH|SPSTART|SIMPLE|POSTPONED);
	break;
    case '|':
    case ')':
	if (flags & TRYAGAIN) {
	    *flagp |= TRYAGAIN;
	    return 0;
	}
	vFAIL("Internal urp");

	break;
    case '?':
    case '+':
    case '*':
	RExC_parse++;
	vFAIL("Quantifier follows nothing");
	break;
    case '\\':

	RExC_parse++;
	switch ((U8)*RExC_parse) {

	case 'A':
	    RExC_seen_zerolen++;
	    ret = reg_node(pRExC_state, SBOL);

            FLAGS(REGNODE_p(ret)) = 1;
	    *flagp |= SIMPLE;
	    goto finish_meta_pat;
	case 'G':
	    ret = reg_node(pRExC_state, GPOS);
            RExC_seen |= REG_GPOS_SEEN;
	    *flagp |= SIMPLE;
	    goto finish_meta_pat;
	case 'K':
	    RExC_seen_zerolen++;
	    ret = reg_node(pRExC_state, KEEPS);
	    *flagp |= SIMPLE;

            RExC_seen |= REG_LOOKBEHIND_SEEN;
	    goto finish_meta_pat;
	case 'Z':
	    ret = reg_node(pRExC_state, SEOL);
	    *flagp |= SIMPLE;
	    RExC_seen_zerolen++;
	    goto finish_meta_pat;
	case 'z':
	    ret = reg_node(pRExC_state, EOS);
	    *flagp |= SIMPLE;
	    RExC_seen_zerolen++;
	    goto finish_meta_pat;
	case 'C':
	    vFAIL("\\C no longer supported");
	case 'X':
	    ret = reg_node(pRExC_state, CLUMP);
	    *flagp |= HASWIDTH;
	    goto finish_meta_pat;

	case 'W':
            invert = 1;

	case 'w':
            arg = ANYOF_WORDCHAR;
            goto join_posix;

	case 'B':
            invert = 1;

	case 'b':
          {
            U8 flags = 0;
	    regex_charset charset = get_regex_charset(RExC_flags);

	    RExC_seen_zerolen++;
            RExC_seen |= REG_LOOKBEHIND_SEEN;
	    op = BOUND + charset;

	    if (RExC_parse >= RExC_end || *(RExC_parse + 1) != '{') {
                flags = TRADITIONAL_BOUND;
                if (op > BOUNDA) {
                    op = BOUNDA;
                }
            }
            else {
                STRLEN length;
                char name = *RExC_parse;
                char * endbrace = NULL;
                RExC_parse += 2;
                endbrace = (char *) memchr(RExC_parse, '}', RExC_end - RExC_parse);

                if (! endbrace) {
                    vFAIL2("Missing right brace on \\%c{}", name);
                }

                if (endbrace == RExC_parse) {
                    RExC_parse++;
                    vFAIL2("Empty \\%c{}", name);
                }
                length = endbrace - RExC_parse;

                switch (*RExC_parse) {
                    case 'g':
                        if (    length != 1
                            && (memNEs(RExC_parse + 1, length - 1, "cb")))
                        {
                            goto bad_bound_type;
                        }
                        flags = GCB_BOUND;
                        break;
                    case 'l':
                        if (length != 2 || *(RExC_parse + 1) != 'b') {
                            goto bad_bound_type;
                        }
                        flags = LB_BOUND;
                        break;
                    case 's':
                        if (length != 2 || *(RExC_parse + 1) != 'b') {
                            goto bad_bound_type;
                        }
                        flags = SB_BOUND;
                        break;
                    case 'w':
                        if (length != 2 || *(RExC_parse + 1) != 'b') {
                            goto bad_bound_type;
                        }
                        flags = WB_BOUND;
                        break;
                    default:
                      bad_bound_type:
                        RExC_parse = endbrace;
			vFAIL2utf8f(
                            "'%" UTF8f "' is an unknown bound type",
			    UTF8fARG(UTF, length, endbrace - length));
                        NOT_REACHED;
                }
                RExC_parse = endbrace;
                REQUIRE_UNI_RULES(flagp, 0);

                if (op == BOUND) {
                    op = BOUNDU;
                }
                else if (op >= BOUNDA) {
                    op = BOUNDU;
                    length += 4;

                    ckWARN4reg(RExC_parse + 1,
                              "Using /u for '%.*s' instead of /%s",
                              (unsigned) length,
                              endbrace - length + 1,
                              (charset == REGEX_ASCII_RESTRICTED_CHARSET)
                              ? ASCII_RESTRICT_PAT_MODS
                              : ASCII_MORE_RESTRICT_PAT_MODS);
                }
	    }

            if (op == BOUND) {
                RExC_seen_d_op = TRUE;
            }
            else if (op == BOUNDL) {
                RExC_contains_locale = 1;
            }

            if (invert) {
                op += NBOUND - BOUND;
            }

	    ret = reg_node(pRExC_state, op);
            FLAGS(REGNODE_p(ret)) = flags;

	    *flagp |= SIMPLE;

	    goto finish_meta_pat;
          }

	case 'D':
            invert = 1;

	case 'd':
            arg = ANYOF_DIGIT;
            if (! DEPENDS_SEMANTICS) {
                goto join_posix;
            }

            op = POSIXU;
            goto join_posix_op_known;

	case 'R':
	    ret = reg_node(pRExC_state, LNBREAK);
	    *flagp |= HASWIDTH|SIMPLE;
	    goto finish_meta_pat;

	case 'H':
            invert = 1;

	case 'h':
	    arg = ANYOF_BLANK;
            op = POSIXU;
            goto join_posix_op_known;

	case 'V':
            invert = 1;

	case 'v':
	    arg = ANYOF_VERTWS;
            op = POSIXU;
            goto join_posix_op_known;

	case 'S':
            invert = 1;

	case 's':
            arg = ANYOF_SPACE;

          join_posix:

	    op = POSIXD + get_regex_charset(RExC_flags);
            if (op > POSIXA) {
                op = POSIXA;
            }
            else if (op == POSIXL) {
                RExC_contains_locale = 1;
            }
            else if (op == POSIXD) {
                RExC_seen_d_op = TRUE;
            }

          join_posix_op_known:

            if (invert) {
                op += NPOSIXD - POSIXD;
            }

	    ret = reg_node(pRExC_state, op);
            FLAGS(REGNODE_p(ret)) = namedclass_to_classnum(arg);

	    *flagp |= HASWIDTH|SIMPLE;

          finish_meta_pat:
            if (   UCHARAT(RExC_parse + 1) == '{'
                && UNLIKELY(! new_regcurly(RExC_parse + 1, RExC_end)))
            {
                RExC_parse += 2;
                vFAIL("Unescaped left brace in regex is illegal here");
            }
	    nextchar(pRExC_state);
            Set_Node_Length(REGNODE_p(ret), 2);
	    break;
	case 'p':
	case 'P':
            RExC_parse--;

            ret = regclass(pRExC_state, flagp, depth+1,
                           TRUE,
                           FALSE,
                           FALSE,
                           (bool) RExC_strict,
                           TRUE,
                           NULL);
            RETURN_FAIL_ON_RESTART_FLAGP(flagp);

            if (!ret)
                FAIL2("panic: regclass returned failure to regatom, flags=%#" UVxf,
                      (UV) *flagp);

            RExC_parse--;

            Set_Node_Offset(REGNODE_p(ret), parse_start);
            Set_Node_Cur_Length(REGNODE_p(ret), parse_start - 2);
            nextchar(pRExC_state);
	    break;
        case 'N':

            ++RExC_parse;
            if (grok_bslash_N(pRExC_state,
                              &ret,
                              NULL,
                              NULL,
                              flagp,
                              RExC_strict,
                              depth)
            ) {
                break;
            }

            RETURN_FAIL_ON_RESTART_FLAGP(flagp);

            RExC_parse = parse_start;
            goto defchar;

	case 'k':
      parse_named_seq:
        {
            char ch;
            if (   RExC_parse >= RExC_end - 1
                || ((   ch = RExC_parse[1]) != '<'
                                      && ch != '\''
                                      && ch != '{'))
            {
	        RExC_parse++;

	        vFAIL2("Sequence %.2s... not terminated", parse_start);
	    } else {
		RExC_parse += 2;
                ret = handle_named_backref(pRExC_state,
                                           flagp,
                                           parse_start,
                                           (ch == '<')
                                           ? '>'
                                           : (ch == '{')
                                             ? '}'
                                             : '\'');
            }
            break;
	}
	case 'g':
	case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	    {
		I32 num;
		bool hasbrace = 0;

		if (*RExC_parse == 'g') {
                    bool isrel = 0;

		    RExC_parse++;
		    if (*RExC_parse == '{') {
		        RExC_parse++;
		        hasbrace = 1;
		    }
		    if (*RExC_parse == '-') {
		        RExC_parse++;
		        isrel = 1;
		    }
		    if (hasbrace && !isDIGIT(*RExC_parse)) {
		        if (isrel) RExC_parse--;
                        RExC_parse -= 2;
		        goto parse_named_seq;
                    }

                    if (RExC_parse >= RExC_end) {
                        goto unterminated_g;
                    }
                    num = S_backref_value(RExC_parse, RExC_end);
                    if (num == 0)
                        vFAIL("Reference to invalid group 0");
                    else if (num == I32_MAX) {
                         if (isDIGIT(*RExC_parse))
			    vFAIL("Reference to nonexistent group");
                        else
                          unterminated_g:
                            vFAIL("Unterminated \\g... pattern");
                    }

                    if (isrel) {
                        num = RExC_npar - num;
                        if (num < 1)
                            vFAIL("Reference to nonexistent or unclosed group");
                    }
                }
                else {
                    num = S_backref_value(RExC_parse, RExC_end);

                    if (

                        num > 9

                        && num >= RExC_npar

                        && *RExC_parse != '8'

                        && *RExC_parse != '9'
                    ) {

                        RExC_parse = parse_start;
                        goto defchar;
                    }
                }

                while (isDIGIT(*RExC_parse))
                    RExC_parse++;
                if (hasbrace) {
                    if (*RExC_parse != '}')
                        vFAIL("Unterminated \\g{...} pattern");
                    RExC_parse++;
                }
                if (num >= (I32)RExC_npar) {

                    if (ALL_PARENS_COUNTED)  {
                        if (num >= RExC_total_parens)  {
                            vFAIL("Reference to nonexistent group");
                        }
                    }
                    else {
                        REQUIRE_PARENS_PASS;
                    }
                }
                RExC_sawback = 1;
                ret = reganode(pRExC_state,
                               ((! FOLD)
                                 ? REF
                                 : (ASCII_FOLD_RESTRICTED)
                                   ? REFFA
                                   : (AT_LEAST_UNI_SEMANTICS)
                                     ? REFFU
                                     : (LOC)
                                       ? REFFL
                                       : REFF),
                                num);
                if (OP(REGNODE_p(ret)) == REFF) {
                    RExC_seen_d_op = TRUE;
                }
                *flagp |= HASWIDTH;

                Set_Node_Offset(REGNODE_p(ret), parse_start);
                Set_Node_Cur_Length(REGNODE_p(ret), parse_start-1);
                skip_to_be_ignored_text(pRExC_state, &RExC_parse,
                                        FALSE  );
	    }
	    break;
	case '\0':
	    if (RExC_parse >= RExC_end)
		FAIL("Trailing \\");

	default:

            RExC_parse = parse_start;
	    goto defchar;
	}
	break;

    case '#':

        assert((RExC_flags & RXf_PMf_EXTENDED) == 0);

    default:
	  defchar: {

	    STRLEN len = 0;
	    UV ender = 0;
	    char *p;
	    char *s;

#define MAX_NODE_STRING_SIZE (255-UTF8_MAXBYTES_CASE)

	    char *s0;
	    U8 upper_parse = MAX_NODE_STRING_SIZE;

            U8 node_type = EXACT;

            Ptrdiff_t initial_size = STR_SZ(256);

            bool next_is_quantifier;
            char * oldp = NULL;

            bool maybe_exactfu = FOLD && (DEPENDS_SEMANTICS || LOC);

            U8 maybe_SIMPLE = SIMPLE;

            bool requires_utf8_target = FALSE;

            bool has_ss = FALSE;

            bool has_micro_sign = FALSE;

            ret = regnode_guts(pRExC_state, node_type, initial_size, "exact");
            FILL_NODE(ret, node_type);
            RExC_emit++;

	    s = STRING(REGNODE_p(ret));

            s0 = s;

	  reparse:

            assert( ! UTF
                   || UTF8_IS_INVARIANT(UCHARAT(RExC_parse))
                   || UTF8_IS_START(UCHARAT(RExC_parse)));

	    for (p = RExC_parse; len < upper_parse && p < RExC_end; ) {

                Size_t added_len = 1;

		oldp = p;

                assert(   (RExC_flags & RXf_PMf_EXTENDED) == 0
                       || ! is_PATWS_safe((p), RExC_end, UTF));

		switch ((U8)*p) {
		case '^':
		case '$':
		case '.':
		case '[':
		case '(':
		case ')':
		case '|':
		    goto loopdone;
		case '\\':

		    switch ((U8)*++p) {

		    case 'A':
		    case 'b': case 'B':
		    case 'C':
		    case 'd': case 'D':
		    case 'g': case 'G':
		    case 'h': case 'H':
		    case 'k': case 'K':
		    case 'p': case 'P':
		              case 'R':
		    case 's': case 'S':
		    case 'v': case 'V':
		    case 'w': case 'W':
                    case 'X':
		    case 'z': case 'Z':
			--p;
			goto loopdone;

		    case 'n':
			ender = '\n';
			p++;
			break;
		    case 'N':
                        RExC_parse = p + 1;
                        if (! grok_bslash_N(pRExC_state,
                                            NULL,
                                            &ender,
                                            NULL,
                                            flagp,
                                            RExC_strict,
                                            depth)
                        ) {
                            if (*flagp & NEED_UTF8)
                                FAIL("panic: grok_bslash_N set NEED_UTF8");
                            RETURN_FAIL_ON_RESTART_FLAGP(flagp);

                            RExC_parse = p = oldp;
                            goto loopdone;
                        }
                        p = RExC_parse;
                        RExC_parse = parse_start;

                        if (node_type == EXACTF) {
                            node_type = EXACTFU;

                            if (! maybe_exactfu) {
                                len = 0;
                                s = s0;
                                goto reparse;
                            }
                        }

                        break;
		    case 'r':
			ender = '\r';
			p++;
			break;
		    case 't':
			ender = '\t';
			p++;
			break;
		    case 'f':
			ender = '\f';
			p++;
			break;
		    case 'e':
			ender = ESC_NATIVE;
			p++;
			break;
		    case 'a':
			ender = '\a';
			p++;
			break;
		    case 'o':
			{
			    UV result;
			    const char* error_msg;

			    bool valid = grok_bslash_o(&p,
                                                       RExC_end,
						       &result,
						       &error_msg,
						       TO_OUTPUT_WARNINGS(p),
                                                       (bool) RExC_strict,
                                                       TRUE,
                                                       UTF);
			    if (! valid) {
				RExC_parse = p;
				vFAIL(error_msg);
			    }
                            UPDATE_WARNINGS_LOC(p - 1);
                            ender = result;
			    break;
			}
		    case 'x':
			{
                            UV result = UV_MAX;
			    const char* error_msg;

			    bool valid = grok_bslash_x(&p,
                                                       RExC_end,
						       &result,
						       &error_msg,
                                                       TO_OUTPUT_WARNINGS(p),
                                                       (bool) RExC_strict,
                                                       TRUE,
                                                       UTF);
			    if (! valid) {
				RExC_parse = p;
				vFAIL(error_msg);
			    }
                            UPDATE_WARNINGS_LOC(p - 1);
                            ender = result;

                            if (ender < 0x100) {
#ifdef EBCDIC
                                if (RExC_recode_x_to_native) {
                                    ender = LATIN1_TO_NATIVE(ender);
                                }
#endif
			    }
			    break;
			}
		    case 'c':
			p++;
			ender = grok_bslash_c(*p, TO_OUTPUT_WARNINGS(p));
                        UPDATE_WARNINGS_LOC(p);
                        p++;
			break;
                    case '8': case '9':
                        --p;

                        goto loopdone;
                    case '1': case '2': case '3':case '4':
		    case '5': case '6': case '7':

                        if ( !isDIGIT(p[1]) || S_backref_value(p, RExC_end) < RExC_npar)
                        {
                            --p;
                            goto loopdone;
                        }

                    case '0':
			{
			    I32 flags = PERL_SCAN_SILENT_ILLDIGIT;
			    STRLEN numlen = 3;
			    ender = grok_oct(p, &numlen, &flags, NULL);
			    p += numlen;
                            if (   isDIGIT(*p)
                                && ckWARN(WARN_REGEXP)
                                && numlen < 3)
                            {
				reg_warn_non_literal_string(
                                         p + 1,
                                         form_short_octal_warning(p, numlen));
                            }
			}
			break;
		    case '\0':
			if (p >= RExC_end)
			    FAIL("Trailing \\");

		    default:
			if (isALPHANUMERIC(*p)) {

                            if (! isALPHA(*p) || *(p + 1) != '{') {
                                ckWARN2reg(p + 1, "Unrecognized escape \\%.1s"
                                                  " passed through", p);
                            }
			}
			goto normal_default;
		    }
		    break;
		case '{':

		    if (len || (p > RExC_start && isALPHA_A(*(p - 1)))) {
                        if (      RExC_strict
                            || (  p > parse_start + 1
                                && isALPHA_A(*(p - 1))
                                && *(p - 2) == '\\')
                            || new_regcurly(p, RExC_end))
                        {
                            RExC_parse = p + 1;
                            vFAIL("Unescaped left brace in regex is "
                                  "illegal here");
                        }
                        ckWARNreg(p + 1, "Unescaped left brace in regex is"
                                         " passed through");
		    }
		    goto normal_default;
                case '}':
                case ']':
                    if (p > RExC_parse && RExC_strict) {
                        ckWARN2reg(p + 1, "Unescaped literal '%c'", *p);
                    }

		default:
		  normal_default:
		    if (! UTF8_IS_INVARIANT(*p) && UTF) {
			STRLEN numlen;
			ender = utf8n_to_uvchr((U8*)p, RExC_end - p,
					       &numlen, UTF8_ALLOW_DEFAULT);
			p += numlen;
		    }
		    else
			ender = (U8) *p++;
		    break;
		}

                if (ender > 255) {
                    REQUIRE_UTF8(flagp);
                }

                skip_to_be_ignored_text(pRExC_state, &p,
                                        FALSE  );

                next_is_quantifier =    LIKELY(p < RExC_end)
                                     && UNLIKELY(ISMULT2(p));

                if (next_is_quantifier && LIKELY(len)) {
                    p = oldp;
                    goto loopdone;
                }

                if (! FOLD) {

                      not_fold_common:
                        if (UVCHR_IS_INVARIANT(ender) || ! UTF) {
                            *(s++) = (char) ender;
                        }
                        else {
                            U8 * new_s = uvchr_to_utf8((U8*)s, ender);
                            added_len = (char *) new_s - s;
                            s = (char *) new_s;

                            if (ender > 255)  {
                                requires_utf8_target = TRUE;
                            }
                        }
                }
                else if (LOC && is_PROBLEMATIC_LOCALE_FOLD_cp(ender)) {

                    if (! len) {
                        node_type = EXACTFL;
                        RExC_contains_locale = 1;
                    }
                    else if (node_type == EXACT) {
                        p = oldp;
                        goto loopdone;
                    }

                    maybe_exactfu = FALSE;

                    goto not_fold_common;
                }
                else
                     if (   (ender < 256 && ! IS_IN_SOME_FOLD_L1(ender))
                         || (ender > 255
                            && ! _invlist_contains_cp(PL_in_some_fold, ender)))
                {

                    if (len && node_type != EXACT) {
                        p = oldp;
                        goto loopdone;
                    }

                    goto not_fold_common;
                }
                else {

                    if (! len) {
                        node_type = compute_EXACTish(pRExC_state);
                    }
                    else if (node_type == EXACT) {
                        p = oldp;
                        goto loopdone;
                    }

                    if (UTF) {
                        if (UVCHR_IS_INVARIANT(ender)) {
                            *(s)++ = (U8) toFOLD(ender);
                        }
                        else {
                            ender = _to_uni_fold_flags(
                                    ender,
                                    (U8 *) s,
                                    &added_len,
                                    FOLD_FLAGS_FULL | ((ASCII_FOLD_RESTRICTED)
                                                    ? FOLD_FLAGS_NOMIX_ASCII
                                                    : 0));
                            s += added_len;

                            if (   ender > 255
                                && LIKELY(ender != GREEK_SMALL_LETTER_MU))
                            {

                                requires_utf8_target = TRUE;
                            }
                        }
                    }
                    else {

                        if (PL_fold[ender] != PL_fold_latin1[ender]) {
                            maybe_exactfu = FALSE;
                        }

#if    UNICODE_MAJOR_VERSION > 3    \
   || (UNICODE_MAJOR_VERSION == 3 && (   UNICODE_DOT_VERSION > 0)       \
                                      || UNICODE_DOT_DOT_VERSION > 0)

                        if (   UNLIKELY(ender == LATIN_SMALL_LETTER_SHARP_S)
                                 || (   isALPHA_FOLD_EQ(ender, 's')
                                     && len > 0
                                     && isALPHA_FOLD_EQ(*(s-1), 's')))
                        {

                            has_ss = TRUE;
                            maybe_exactfu = FALSE;
                            if (UNLIKELY(ender == LATIN_SMALL_LETTER_SHARP_S)) {
                                maybe_SIMPLE = 0;
                                if (node_type == EXACTFU) {
                                    *(s++) = 's';

                                    ender = 's';
                                    added_len = 2;
                                }
                            }
                        }
#endif

                        else if (UNLIKELY(ender == MICRO_SIGN)) {
                            has_micro_sign = TRUE;
                        }

                        *(s++) = (DEPENDS_SEMANTICS)
                                 ? (char) toFOLD(ender)

                                 : (char) toLOWER_L1(ender);
                    }
		}

                len += added_len;

		if (next_is_quantifier) {

                    goto loopdone;
		}

	    }

            if (FOLD && p < RExC_end && upper_parse == MAX_NODE_STRING_SIZE) {
                PERL_UINT_FAST8_T backup_count = 0;

                const STRLEN full_len = len;

		assert(len >= MAX_NODE_STRING_SIZE);

		if (! UTF) {

                    if (ASCII_FOLD_RESTRICTED) {
                        goto loopdone;
                    }

                    while (--s >= s0 && IS_NON_FINAL_FOLD(*s)) {
                        backup_count++;
                    }
                    len = s - s0 + 1;
		}
                else {

                    s = (char *) utf8_hop_back((U8 *) s, -1, (U8 *) s0);

                    while (s >= s0) {
                        if (UTF8_IS_INVARIANT(*s)) {

                            if (ASCII_FOLD_RESTRICTED
                                || ! IS_NON_FINAL_FOLD(*s))
                            {
                                break;
                            }
                        }
                        else if (UTF8_IS_DOWNGRADEABLE_START(*s)) {
                            if (! IS_NON_FINAL_FOLD(EIGHT_BIT_UTF8_TO_NATIVE(
                                                                  *s, *(s+1))))
                            {
                                break;
                            }
                        }
                        else if (! _invlist_contains_cp(
                                        PL_NonFinalFold,
                                        valid_utf8_to_uvchr((U8 *) s, NULL)))
                        {
                            break;
                        }

                        s = (s == s0) ? s -1 : (char *) utf8_hop((U8 *) s, -1);
                        backup_count++;
                    }

                    len = (s < s0) ? 0 : s - s0 + UTF8SKIP(s);
		}

                if (len == 0) {
                    len = full_len;

                } else {

                    if (backup_count == 0) {
                        goto loopdone;
                    }
                    else if (backup_count == 1) {

                        p = oldp;
                        goto loopdone;
                    }

                    upper_parse = len;
                    len = 0;
                    s = s0;
                    goto reparse;
                }
	    }

          loopdone:

            change_engine_size(pRExC_state,
                                - (Ptrdiff_t) (initial_size - STR_SZ(len)));

            if (len == 0) {
                OP(REGNODE_p(ret)) = NOTHING;
            }
            else {

                if (node_type == EXACT) {
                    if (LOC) {
                        node_type = EXACTL;
                    }
                    else if (requires_utf8_target) {
                        node_type = EXACT_ONLY8;
                    }
                } else if (FOLD) {
                    if (    UNLIKELY(has_micro_sign || has_ss)
                        && (node_type == EXACTFU || (   node_type == EXACTF
                                                     && maybe_exactfu)))
                    {
                        assert(! UTF);
                        node_type = EXACTFUP;
                    }
                    else if (node_type == EXACTFL) {

                        if (maybe_exactfu) {
                            node_type = EXACTFLU8;
                        }
                        else if (UNLIKELY(
                             _invlist_contains_cp(PL_HasMultiCharFold, ender)))
                        {

                            maybe_SIMPLE = 0;
                        }
                    }
                    else if (node_type == EXACTF) {

                        if (! maybe_exactfu) {
                            RExC_seen_d_op = TRUE;
                        }
                        else if (   isALPHA_FOLD_EQ(* STRING(REGNODE_p(ret)), 's')
                                 || isALPHA_FOLD_EQ(ender, 's'))
                        {

                            node_type = EXACTFU_S_EDGE;
                        }
                        else {
                            node_type = EXACTFU;
                        }
                    }

                    if (requires_utf8_target && node_type == EXACTFU) {
                        node_type = EXACTFU_ONLY8;
                    }
                }

                OP(REGNODE_p(ret)) = node_type;
                STR_LEN(REGNODE_p(ret)) = len;
                RExC_emit += STR_SZ(len);

                if (len > (Size_t) ((UTF) ? UVCHR_SKIP(ender) : 1)) {
                    maybe_SIMPLE = 0;
                }

                *flagp |= HASWIDTH | maybe_SIMPLE;
            }

            Set_Node_Length(REGNODE_p(ret), p - parse_start - 1);
            RExC_parse = p;

	    {

		IV iv = len;
		if (iv < 0)
		    vFAIL("Internal disaster");
	    }

	}
	break;
    }

    skip_to_be_ignored_text(pRExC_state, &RExC_parse,
                                            FALSE  );
    if (   *RExC_parse == '{'
        && OP(REGNODE_p(ret)) != SBOL && ! regcurly(RExC_parse))
    {
        if (RExC_strict || new_regcurly(RExC_parse, RExC_end)) {
            RExC_parse++;
            vFAIL("Unescaped left brace in regex is illegal here");
        }
        ckWARNreg(RExC_parse + 1, "Unescaped left brace in regex is"
                                  " passed through");
    }

    return(ret);
}
}
}
}
}
