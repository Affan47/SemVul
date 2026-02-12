STATIC regnode_offset
S_regclass(pTHX_ RExC_state_t *pRExC_state, I32 *flagp, U32 depth,
                 const bool stop_at_1,
                 bool allow_mutiple_chars,
                 const bool silence_non_portable,
                 const bool strict,
                 bool optimizable,
                 SV** ret_invlist
          )
{

    dVAR;
    UV prevvalue = OOB_UNICODE, save_prevvalue = OOB_UNICODE;
    IV range = 0;
    UV value = OOB_UNICODE, save_value = OOB_UNICODE;
    regnode_offset ret = -1;
    STRLEN numlen;
    int namedclass = OOB_NAMEDCLASS;
    char *rangebegin = NULL;
    SV *listsv = NULL;
    STRLEN initial_listsv_len = 0;
    SV* properties = NULL;
    SV* posixes = NULL;
    SV* nposixes = NULL;
    SV* simple_posixes = NULL;
    UV element_count = 0;
    AV * multi_char_matches = NULL;
    UV n;
    char * stop_ptr = RExC_end;

    const bool skip_white = cBOOL(   ret_invlist
                                  || (RExC_flags & RXf_PMf_EXTENDED_MORE));

    SV* upper_latin1_only_utf8_matches = NULL;

    SV* cp_list = NULL;

    SV* cp_foldable_list = NULL;

    SV* only_utf8_locale_list = NULL;

    unsigned int non_portable_endpoint = 0;

    bool unicode_range = FALSE;
    bool invert = FALSE;

    bool warn_super = ALWAYS_WARN_SUPER;

    const char * orig_parse = RExC_parse;

    char *not_posix_region_end = RExC_parse - 1;

    AV* posix_warnings = NULL;
    const bool do_posix_warnings = ckWARN(WARN_REGEXP);
    U8 op = END;
    U8 anyof_flags = 0;
    U32 posixl = 0;

#define HAS_USER_DEFINED_PROPERTY 0x01
#define HAS_D_RUNTIME_DEPENDENCY  0x02
#define HAS_L_RUNTIME_DEPENDENCY   0x04
    U32 has_runtime_dependency = 0;

    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REGCLASS;
#ifndef DEBUGGING
    PERL_UNUSED_ARG(depth);
#endif

    if (ret_invlist) {
        optimizable = FALSE;
    }

    DEBUG_PARSE("clas");

#if UNICODE_MAJOR_VERSION < 3       \
    || (UNICODE_MAJOR_VERSION == 3 && UNICODE_DOT_VERSION == 0          \
                                   && UNICODE_DOT_DOT_VERSION == 0)
    allow_mutiple_chars = FALSE;
#endif

    listsv = sv_2mortal(Perl_newSVpvf(aTHX_ "#%d\n", cBOOL(FOLD)));
    initial_listsv_len = SvCUR(listsv);
    SvTEMP_off(listsv);

    SKIP_BRACKETED_WHITE_SPACE(skip_white, RExC_parse);

    assert(RExC_parse <= RExC_end);

    if (UCHARAT(RExC_parse) == '^') {
	RExC_parse++;
        invert = TRUE;
        allow_mutiple_chars = FALSE;
        MARK_NAUGHTY(1);
        SKIP_BRACKETED_WHITE_SPACE(skip_white, RExC_parse);
    }

    if (! ret_invlist && MAYBE_POSIXCC(UCHARAT(RExC_parse))) {
        int maybe_class = handle_possible_posix(pRExC_state,
                                                RExC_parse,
                                                &not_posix_region_end,
                                                NULL,
                                                TRUE );
        if (maybe_class >= OOB_NAMEDCLASS && do_posix_warnings) {
            ckWARN4reg(not_posix_region_end,
                    "POSIX syntax [%c %c] belongs inside character classes%s",
                    *RExC_parse, *RExC_parse,
                    (maybe_class == OOB_NAMEDCLASS)
                    ? ((POSIXCC_NOTYET(*RExC_parse))
                        ? " (but this one isn't implemented)"
                        : " (but this one isn't fully valid)")
                    : ""
                    );
        }
    }

    if (stop_at_1 && RExC_end > RExC_parse) {
        stop_ptr = RExC_parse + 1;
    }

    if (UCHARAT(RExC_parse) == ']')
	goto charclassloop;

    while (1) {

        if (   posix_warnings
            && av_tindex_skip_len_mg(posix_warnings) >= 0
            && RExC_parse > not_posix_region_end)
        {

            output_posix_warnings(pRExC_state, posix_warnings);
        }

        if  (RExC_parse >= stop_ptr) {
            break;
        }

        SKIP_BRACKETED_WHITE_SPACE(skip_white, RExC_parse);

        if  (UCHARAT(RExC_parse) == ']') {
            break;
        }

      charclassloop:

	namedclass = OOB_NAMEDCLASS;
        save_value = value;
        save_prevvalue = prevvalue;

	if (!range) {
	    rangebegin = RExC_parse;
	    element_count++;
            non_portable_endpoint = 0;
	}
	if (UTF && ! UTF8_IS_INVARIANT(* RExC_parse)) {
	    value = utf8n_to_uvchr((U8*)RExC_parse,
				   RExC_end - RExC_parse,
				   &numlen, UTF8_ALLOW_DEFAULT);
	    RExC_parse += numlen;
	}
	else
	    value = UCHARAT(RExC_parse++);

        if (value == '[') {
            char * posix_class_end;
            namedclass = handle_possible_posix(pRExC_state,
                                               RExC_parse,
                                               &posix_class_end,
                                               do_posix_warnings ? &posix_warnings : NULL,
                                               FALSE    );
            if (namedclass > OOB_NAMEDCLASS) {

                if (   posix_warnings
                    && av_tindex_skip_len_mg(posix_warnings) >= 0
                    && not_posix_region_end >= RExC_parse
                    && not_posix_region_end <= posix_class_end)
                {
                    av_undef(posix_warnings);
                }

                RExC_parse = posix_class_end;
            }
            else if (namedclass == OOB_NAMEDCLASS) {
                not_posix_region_end = posix_class_end;
            }
            else {
                namedclass = OOB_NAMEDCLASS;
            }
        }
        else if (   RExC_parse - 1 > not_posix_region_end
                 && MAYBE_POSIXCC(value))
        {
            (void) handle_possible_posix(
                        pRExC_state,
                        RExC_parse - 1,
                        &not_posix_region_end,
                        do_posix_warnings ? &posix_warnings : NULL,
                        TRUE );
        }
        else if (  strict && ! skip_white
                 && (   _generic_isCC(value, _CC_VERTSPACE)
                     || is_VERTWS_cp_high(value)))
        {
            vFAIL("Literal vertical space in [] is illegal except under /x");
        }
        else if (value == '\\') {

            if (RExC_parse >= RExC_end) {
                vFAIL("Unmatched [");
            }

	    if (UTF && ! UTF8_IS_INVARIANT(UCHARAT(RExC_parse))) {
		value = utf8n_to_uvchr((U8*)RExC_parse,
				   RExC_end - RExC_parse,
				   &numlen, UTF8_ALLOW_DEFAULT);
		RExC_parse += numlen;
	    }
	    else
		value = UCHARAT(RExC_parse++);

            if (! skip_white || ! isBLANK_A(value)) switch ((I32)value) {

	    case 'w':	namedclass = ANYOF_WORDCHAR;	break;
	    case 'W':	namedclass = ANYOF_NWORDCHAR;	break;
	    case 's':	namedclass = ANYOF_SPACE;	break;
	    case 'S':	namedclass = ANYOF_NSPACE;	break;
	    case 'd':	namedclass = ANYOF_DIGIT;	break;
	    case 'D':	namedclass = ANYOF_NDIGIT;	break;
	    case 'v':	namedclass = ANYOF_VERTWS;	break;
	    case 'V':	namedclass = ANYOF_NVERTWS;	break;
	    case 'h':	namedclass = ANYOF_HORIZWS;	break;
	    case 'H':	namedclass = ANYOF_NHORIZWS;	break;
            case 'N':
                {
                    const char * const backslash_N_beg = RExC_parse - 2;
                    int cp_count;

                    if (! grok_bslash_N(pRExC_state,
                                        NULL,
                                        &value,
                                        &cp_count,
                                        flagp,
                                        strict,
                                        depth)
                    ) {

                        if (*flagp & NEED_UTF8)
                            FAIL("panic: grok_bslash_N set NEED_UTF8");

                        RETURN_FAIL_ON_RESTART_FLAGP(flagp);

                        if (cp_count < 0) {
                            vFAIL("\\N in a character class must be a named character: \\N{...}");
                        }
                        else if (cp_count == 0) {
                            ckWARNreg(RExC_parse,
                              "Ignoring zero length \\N{} in character class");
                        }
                        else {
                            assert(cp_count > 1);
                            if (! RExC_in_multi_char_class) {
                                if ( ! allow_mutiple_chars
                                    || invert
                                    || range
                                    || *RExC_parse == '-')
                                {
                                    if (strict) {
                                        RExC_parse--;
                                        vFAIL("\\N{} in inverted character class or as a range end-point is restricted to one character");
                                    }
                                    ckWARNreg(RExC_parse, "Using just the first character returned by \\N{} in character class");
                                    break;
                                }
                                else {
                                    SV * multi_char_N = newSVpvn(backslash_N_beg,
                                                 RExC_parse - backslash_N_beg);
                                    multi_char_matches
                                        = add_multi_match(multi_char_matches,
                                                          multi_char_N,
                                                          cp_count);
                                }
                            }
                        }

                        element_count--;
                        value = save_value;
                        prevvalue = save_prevvalue;
                        continue;
                    }

                    unicode_range = TRUE;
                }
                break;
	    case 'p':
	    case 'P':
		{
		char *e;

		REQUIRE_UNI_RULES(flagp, 0);

		if (RExC_parse >= RExC_end)
		    vFAIL2("Empty \\%c", (U8)value);
		if (*RExC_parse == '{') {
		    const U8 c = (U8)value;
		    e = (char *) memchr(RExC_parse, '}', RExC_end - RExC_parse);
                    if (!e) {
                        RExC_parse++;
                        vFAIL2("Missing right brace on \\%c{}", c);
                    }

                    RExC_parse++;

                    while (isSPACE(*RExC_parse)) {
                         RExC_parse++;
		    }

		    if (UCHARAT(RExC_parse) == '^') {

                        value ^= 'P' ^ 'p';

                        RExC_parse++;
                        while (isSPACE(*RExC_parse)) {
                            RExC_parse++;
                        }
                    }

                    if (e == RExC_parse)
                        vFAIL2("Empty \\%c{}", c);

		    n = e - RExC_parse;
		    while (isSPACE(*(RExC_parse + n - 1)))
		        n--;

		}
		else if (! isALPHA(*RExC_parse)) {
                    RExC_parse += (UTF)
                                  ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                                  : 1;
                    vFAIL2("Character following \\%c must be '{' or a "
                           "single-character Unicode property name",
                           (U8) value);
                }
                else {
		    e = RExC_parse;
		    n = 1;
		}
		{
                    char* name = RExC_parse;

                    SV* msg = newSVpvs_flags("", SVs_TEMP);

                    bool user_defined = FALSE;

                    SV * prop_definition = parse_uniprop_string(
                                            name, n, UTF, FOLD,
                                            FALSE,

                                            ! cBOOL(ret_invlist),

                                            &user_defined,
                                            msg,
                                            0
                                           );
                    if (SvCUR(msg)) {
                        assert(prop_definition == NULL);
                        RExC_parse = e + 1;
                        if (SvUTF8(msg)) {
                            RExC_utf8 = TRUE;
                        }

                        vFAIL2utf8f("%" UTF8f, UTF8fARG(SvUTF8(msg),
                                    SvCUR(msg), SvPVX(msg)));
                    }

                    if (! is_invlist(prop_definition)) {

                        if (value == 'P') {
                            sv_catpvs(listsv, "!");
                        }
                        else {
                            sv_catpvs(listsv, "+");
                        }
                        sv_catsv(listsv, prop_definition);

                        has_runtime_dependency |= HAS_USER_DEFINED_PROPERTY;

                        anyof_flags |= ANYOF_SHARED_d_UPPER_LATIN1_UTF8_STRING_MATCHES_non_d_RUNTIME_USER_PROP;
                    }
                    else {
                        assert (prop_definition && is_invlist(prop_definition));

                        if (     memEQs(RExC_start, e + 1 - RExC_start,
                                        "foo\\p{Alnum}")
                            && ! hv_common(GvHVn(PL_incgv),
                                           NULL,
                                           "utf8.pm", sizeof("utf8.pm") - 1,
                                           0, HV_FETCH_ISEXISTS, NULL, 0))
                        {
                            require_pv("utf8.pm");
                        }

                        if (! user_defined &&

                            (_invlist_contains_cp(prop_definition, 0x110000)
                                && (! (_invlist_len(prop_definition) == 1
                                       && *invlist_array(prop_definition) == 0))))
                        {
                            warn_super = TRUE;
                        }

                        if (value == 'P') {
			    _invlist_union_complement_2nd(properties,
                                                          prop_definition,
                                                          &properties);
                        }
                        else {
                            _invlist_union(properties, prop_definition, &properties);
			}
                    }
                }

		RExC_parse = e + 1;
                namedclass = ANYOF_UNIPROP;
		}
		break;
	    case 'n':	value = '\n';			break;
	    case 'r':	value = '\r';			break;
	    case 't':	value = '\t';			break;
	    case 'f':	value = '\f';			break;
	    case 'b':	value = '\b';			break;
	    case 'e':	value = ESC_NATIVE;             break;
	    case 'a':	value = '\a';                   break;
	    case 'o':
		RExC_parse--;
		{
		    const char* error_msg;
		    bool valid = grok_bslash_o(&RExC_parse,
                                               RExC_end,
					       &value,
					       &error_msg,
                                               TO_OUTPUT_WARNINGS(RExC_parse),
                                               strict,
                                               silence_non_portable,
                                               UTF);
		    if (! valid) {
			vFAIL(error_msg);
		    }
                    UPDATE_WARNINGS_LOC(RExC_parse - 1);
		}
                non_portable_endpoint++;
		break;
	    case 'x':
		RExC_parse--;
		{
		    const char* error_msg;
		    bool valid = grok_bslash_x(&RExC_parse,
                                               RExC_end,
					       &value,
					       &error_msg,
					       TO_OUTPUT_WARNINGS(RExC_parse),
                                               strict,
                                               silence_non_portable,
                                               UTF);
                    if (! valid) {
			vFAIL(error_msg);
		    }
                    UPDATE_WARNINGS_LOC(RExC_parse - 1);
		}
                non_portable_endpoint++;
		break;
	    case 'c':
		value = grok_bslash_c(*RExC_parse, TO_OUTPUT_WARNINGS(RExC_parse));
                UPDATE_WARNINGS_LOC(RExC_parse);
		RExC_parse++;
                non_portable_endpoint++;
		break;
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7':
		{

		    I32 flags = PERL_SCAN_SILENT_ILLDIGIT;
                    numlen = (strict) ? 4 : 3;
                    value = grok_oct(--RExC_parse, &numlen, &flags, NULL);
		    RExC_parse += numlen;
                    if (numlen != 3) {
                        if (strict) {
                            RExC_parse += (UTF)
                                          ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                                          : 1;
                            vFAIL("Need exactly 3 octal digits");
                        }
                        else if (   numlen < 3
                                 && RExC_parse < RExC_end
                                 && isDIGIT(*RExC_parse)
                                 && ckWARN(WARN_REGEXP))
                        {
                            reg_warn_non_literal_string(
                                 RExC_parse + 1,
                                 form_short_octal_warning(RExC_parse, numlen));
                        }
                    }
                    non_portable_endpoint++;
		    break;
		}
	    default:

		if (isWORDCHAR(value) && value != '_') {
                    if (strict) {
                        vFAIL2("Unrecognized escape \\%c in character class",
                               (int)value);
                    }
                    else {
                        ckWARN2reg(RExC_parse,
                            "Unrecognized escape \\%c in character class passed through",
                            (int)value);
                    }
		}
		break;
	    }
	}

	if (namedclass > OOB_NAMEDCLASS) {
            U8 classnum;

	    if (range) {
                const int w = (RExC_parse >= rangebegin)
                                ? RExC_parse - rangebegin
                                : 0;
                if (strict) {
                    vFAIL2utf8f(
                        "False [] range \"%" UTF8f "\"",
                        UTF8fARG(UTF, w, rangebegin));
                }
                else {
                    ckWARN2reg(RExC_parse,
                        "False [] range \"%" UTF8f "\"",
                        UTF8fARG(UTF, w, rangebegin));
                    cp_list = add_cp_to_invlist(cp_list, '-');
                    cp_foldable_list = add_cp_to_invlist(cp_foldable_list,
                                                            prevvalue);
                }

		range = 0;
                element_count += 2;
	    }

            classnum = namedclass_to_classnum(namedclass);

	    if (LOC && namedclass < ANYOF_POSIXL_MAX
#ifndef HAS_ISASCII
                && classnum != _CC_ASCII
#endif
            ) {
                SV* scratch_list = NULL;

                if (POSIXL_TEST(posixl, namedclass ^ 1)) {
                    cp_list = _add_range_to_invlist(cp_list, 0, UV_MAX);
                    POSIXL_ZERO(posixl);
                    has_runtime_dependency &= ~HAS_L_RUNTIME_DEPENDENCY;
                    anyof_flags &= ~ANYOF_MATCHES_POSIXL;
                    continue;
                }
                else {
                    POSIXL_SET(posixl, namedclass);
                    has_runtime_dependency |= HAS_L_RUNTIME_DEPENDENCY;
                    anyof_flags |= ANYOF_MATCHES_POSIXL;

                    _invlist_intersection_maybe_complement_2nd(PL_AboveLatin1,
                                            PL_XPosix_ptrs[classnum],

                                            namedclass % 2 != 0,
                                            &scratch_list);

                    if (! cp_list) {
                        cp_list = scratch_list;
                    }
                    else {
                        _invlist_union(cp_list, scratch_list, &cp_list);
                        SvREFCNT_dec_NN(scratch_list);
                    }
                    continue;
                }
            }
            else {

                if (namedclass >= ANYOF_POSIXL_MAX) {
                    if (namedclass != ANYOF_UNIPROP) {

                        if (classnum != _CC_VERTSPACE) {
                            assert(   namedclass == ANYOF_HORIZWS
                                   || namedclass == ANYOF_NHORIZWS);

                            classnum = _CC_BLANK;
                        }

                        _invlist_union_maybe_complement_2nd(
                                cp_list,
                                PL_XPosix_ptrs[classnum],
                                namedclass % 2 != 0,
                                &cp_list);
                    }
                }
                else if (   AT_LEAST_UNI_SEMANTICS
                         || classnum == _CC_ASCII
                         || (DEPENDS_SEMANTICS && (   classnum == _CC_DIGIT
                                                   || classnum == _CC_XDIGIT)))
                {

                    _invlist_union_maybe_complement_2nd(
                                                     simple_posixes,
                                                      ((AT_LEAST_ASCII_RESTRICTED)
                                                       ? PL_Posix_ptrs[classnum]
                                                       : PL_XPosix_ptrs[classnum]),
                                                     namedclass % 2 != 0,
                                                     &simple_posixes);
                }
                else {
                    SV** posixes_ptr = namedclass % 2 == 0
                                       ? &posixes
                                       : &nposixes;
                    _invlist_union_maybe_complement_2nd(
                                                     *posixes_ptr,
                                                     PL_XPosix_ptrs[classnum],
                                                     namedclass % 2 != 0,
                                                     posixes_ptr);
                }
	    }
	}

        SKIP_BRACKETED_WHITE_SPACE(skip_white, RExC_parse);

	if (range) {
#ifdef EBCDIC

	    if (unicode_range && prevvalue < 255 && value < 255) {
                if (NATIVE_TO_LATIN1(prevvalue) > NATIVE_TO_LATIN1(value)) {
                    goto backwards_range;
                }
            }
            else
#endif
	    if (prevvalue > value)  {
		int w;
#ifdef EBCDIC
              backwards_range:
#endif
                w = RExC_parse - rangebegin;
                vFAIL2utf8f(
                    "Invalid [] range \"%" UTF8f "\"",
                    UTF8fARG(UTF, w, rangebegin));
                NOT_REACHED;
	    }
	}
	else {
            prevvalue = value;
            if (! stop_at_1
                && *RExC_parse == '-')
            {
                char* next_char_ptr = RExC_parse + 1;

                SKIP_BRACKETED_WHITE_SPACE(skip_white, next_char_ptr);

                if (next_char_ptr < RExC_end && *next_char_ptr != ']') {
                    RExC_parse = next_char_ptr;

                    if (namedclass > OOB_NAMEDCLASS) {
                        if (strict || ckWARN(WARN_REGEXP)) {
                            const int w = RExC_parse >= rangebegin
                                          ?  RExC_parse - rangebegin
                                          : 0;
                            if (strict) {
                                vFAIL4("False [] range \"%*.*s\"",
                                    w, w, rangebegin);
                            }
                            else {
                                vWARN4(RExC_parse,
                                    "False [] range \"%*.*s\"",
                                    w, w, rangebegin);
                            }
                        }
                        cp_list = add_cp_to_invlist(cp_list, '-');
                        element_count++;
                    } else
                        range = 1;
                    continue;
                }
	    }
	}

        if (namedclass > OOB_NAMEDCLASS) {
            continue;
        }

	if (value > 255) {
            REQUIRE_UNI_RULES(flagp, 0);
	}

        if (FOLD && allow_mutiple_chars && value == prevvalue) {
            if (    value == LATIN_SMALL_LETTER_SHARP_S
                || (value > 255 && _invlist_contains_cp(PL_HasMultiCharFold,
                                                        value)))
            {

                U8 foldbuf[UTF8_MAXBYTES_CASE+1];
                STRLEN foldlen;

                UV folded = _to_uni_fold_flags(
                                value,
                                foldbuf,
                                &foldlen,
                                FOLD_FLAGS_FULL | (ASCII_FOLD_RESTRICTED
                                                   ? FOLD_FLAGS_NOMIX_ASCII
                                                   : 0)
                                );

                if (folded != value) {

                    if (! RExC_in_multi_char_class) {
                        STRLEN cp_count = utf8_length(foldbuf,
                                                      foldbuf + foldlen);
                        SV* multi_fold = sv_2mortal(newSVpvs(""));

                        Perl_sv_catpvf(aTHX_ multi_fold, "\\x{%" UVXf "}", value);

                        multi_char_matches
                                        = add_multi_match(multi_char_matches,
                                                          multi_fold,
                                                          cp_count);

                    }

                    element_count--;
                    value = save_value;
                    prevvalue = save_prevvalue;
                    continue;
                }
            }
        }

        if (strict && ckWARN(WARN_REGEXP)) {
            if (range) {

                if (unicode_range && non_portable_endpoint && prevvalue < 256) {
                    vWARN(RExC_parse, "Both or neither range ends should be Unicode");
                }
                else if (prevvalue != value) {

                    if (             (isPRINT_A(prevvalue) || isPRINT_A(value))
                        && (          non_portable_endpoint
                            || ! (   (isDIGIT_A(prevvalue) && isDIGIT_A(value))
                                  || (isLOWER_A(prevvalue) && isLOWER_A(value))
                                  || (isUPPER_A(prevvalue) && isUPPER_A(value))
                    ))) {
                        vWARN(RExC_parse, "Ranges of ASCII printables should"
                                          " be some subset of \"0-9\","
                                          " \"A-Z\", or \"a-z\"");
                    }
                    else if (prevvalue >= FIRST_NON_ASCII_DECIMAL_DIGIT) {
                        SSize_t index_start;
                        SSize_t index_final;

                        if (UNLIKELY(value == 0x19DA && prevvalue >= 0x19D0)) {
                            goto warn_bad_digit_range;
                        }
                        else if (UNLIKELY(   prevvalue >= 0x1D7CE
                                          &&     value <= 0x1D7FF))
                        {

                            if (         value - prevvalue > 9
                                ||    (((    value - 0x1D7CE) % 10)
                                     <= (prevvalue - 0x1D7CE) % 10))
                            {
                                goto warn_bad_digit_range;
                            }
                        }
                        else {

                            index_start = _invlist_search(
                                                    PL_XPosix_ptrs[_CC_DIGIT],
                                                    prevvalue);

                            if (   index_start >= 0
                                && ELEMENT_RANGE_MATCHES_INVLIST(index_start)
                                && (index_final =
                                    _invlist_search(PL_XPosix_ptrs[_CC_DIGIT],
                                                    value)) != index_start
                                && index_final >= 0
                                && ELEMENT_RANGE_MATCHES_INVLIST(index_final))
                            {
                              warn_bad_digit_range:
                                vWARN(RExC_parse, "Ranges of digits should be"
                                                  " from the same group of"
                                                  " 10");
                            }
                        }
                    }
                }
            }
            if ((! range || prevvalue == value) && non_portable_endpoint) {
                if (isPRINT_A(value)) {
                    char literal[3];
                    unsigned d = 0;
                    if (isBACKSLASHED_PUNCT(value)) {
                        literal[d++] = '\\';
                    }
                    literal[d++] = (char) value;
                    literal[d++] = '\0';

                    vWARN4(RExC_parse,
                           "\"%.*s\" is more clearly written simply as \"%s\"",
                           (int) (RExC_parse - rangebegin),
                           rangebegin,
                           literal
                        );
                }
                else if isMNEMONIC_CNTRL(value) {
                    vWARN4(RExC_parse,
                           "\"%.*s\" is more clearly written simply as \"%s\"",
                           (int) (RExC_parse - rangebegin),
                           rangebegin,
                           cntrl_to_mnemonic((U8) value)
                        );
                }
            }
        }

#ifndef EBCDIC
        cp_foldable_list = _add_range_to_invlist(cp_foldable_list,
                                                    prevvalue, value);
#else

        if ((UNLIKELY(prevvalue == 0) && value >= 255)
            || ! (prevvalue < 256
                    && (unicode_range
                        || (! non_portable_endpoint
                            && ((isLOWER_A(prevvalue) && isLOWER_A(value))
                                || (isUPPER_A(prevvalue)
                                    && isUPPER_A(value)))))))
        {
            cp_foldable_list = _add_range_to_invlist(cp_foldable_list,
                                                        prevvalue, value);
        }
        else {

            U8 start = NATIVE_TO_LATIN1(prevvalue);
            unsigned j;
            U8 end = (value < 256) ? NATIVE_TO_LATIN1(value) : 255;
            for (j = start; j <= end; j++) {
                cp_foldable_list = add_cp_to_invlist(cp_foldable_list, LATIN1_TO_NATIVE(j));
            }
            if (value > 255) {
                cp_foldable_list = _add_range_to_invlist(cp_foldable_list,
                                                            256, value);
            }
        }
#endif

	range = 0;
    }

    if (   posix_warnings && av_tindex_skip_len_mg(posix_warnings) >= 0) {
        output_posix_warnings(pRExC_state, posix_warnings);
    }

    if (multi_char_matches) {
	SV * substitute_parse = newSVpvn_flags("?:", 2, SVs_TEMP);
        I32 cp_count;
	STRLEN len;
	char *save_end = RExC_end;
	char *save_parse = RExC_parse;
	char *save_start = RExC_start;
        Size_t constructed_prefix_len = 0;
        bool first_time = TRUE;
        I32 reg_flags;

        assert(! invert);

        assert(RExC_copy_start_in_constructed == RExC_precomp);

#if 0
        if (invert) {
            sv_catpvs(substitute_parse, "(?:");
        }
#endif

        for (cp_count = av_tindex_skip_len_mg(multi_char_matches);
                        cp_count > 0;
                        cp_count--)
        {

            if (av_exists(multi_char_matches, cp_count)) {
                AV** this_array_ptr;
                SV* this_sequence;

                this_array_ptr = (AV**) av_fetch(multi_char_matches,
                                                 cp_count, FALSE);
                while ((this_sequence = av_pop(*this_array_ptr)) !=
                                                                &PL_sv_undef)
                {
                    if (! first_time) {
                        sv_catpvs(substitute_parse, "|");
                    }
                    first_time = FALSE;

                    sv_catpv(substitute_parse, SvPVX(this_sequence));
                }
            }
        }

        if (element_count) {
            sv_catpvs(substitute_parse, "|[");
            constructed_prefix_len = SvCUR(substitute_parse);
            sv_catpvn(substitute_parse, orig_parse, RExC_parse - orig_parse);

            if (RExC_parse < RExC_end) {
                sv_catpvs(substitute_parse, "]");
            }
        }

        sv_catpvs(substitute_parse, ")");
#if 0
        if (invert) {

            sv_catpvs(substitute_parse, "(*THEN)(*SKIP)(*FAIL)|.)");
        }
#endif

        RExC_copy_start_in_input = (char *) orig_parse;
	RExC_start = RExC_parse = SvPV(substitute_parse, len);
        RExC_copy_start_in_constructed = RExC_start + constructed_prefix_len;
	RExC_end = RExC_parse + len;
        RExC_in_multi_char_class = 1;

	ret = reg(pRExC_state, 1, &reg_flags, depth+1);

        *flagp |= reg_flags & (HASWIDTH|SIMPLE|SPSTART|POSTPONED|RESTART_PARSE|NEED_UTF8);

        RExC_parse = save_parse;
	RExC_start = RExC_copy_start_in_constructed = RExC_copy_start_in_input = save_start;
	RExC_end = save_end;
	RExC_in_multi_char_class = 0;
        SvREFCNT_dec_NN(multi_char_matches);
        return ret;
    }

    if (cp_foldable_list) {
        if (FOLD) {
            UV start, end;

            SV* fold_intersection = NULL;
            SV** use_list;

            if (LOC) {
                use_list = &only_utf8_locale_list;
            }
            else {
                use_list = &cp_list;
            }

            _invlist_intersection(PL_in_some_fold, cp_foldable_list,
                                  &fold_intersection);

            invlist_iterinit(fold_intersection);
            while (invlist_iternext(fold_intersection, &start, &end)) {
                UV j;
                UV folded;

                for (j = start; j <= end; j++) {
                    U8 foldbuf[UTF8_MAXBYTES_CASE+1];
                    STRLEN foldlen;
                    unsigned int k;
                    Size_t folds_count;
                    unsigned int first_fold;
                    const unsigned int * remaining_folds;

                    if (j < 256) {

                        if (      IS_IN_SOME_FOLD_L1(j)
                            && ! (LOC && j != MICRO_SIGN))
                        {

                            if (isASCII(j) || ! DEPENDS_SEMANTICS) {
                                *use_list = add_cp_to_invlist(*use_list,
                                                            PL_fold_latin1[j]);
                            }
                            else if (j != PL_fold_latin1[j]) {
                                upper_latin1_only_utf8_matches
                                        = add_cp_to_invlist(
                                                upper_latin1_only_utf8_matches,
                                                PL_fold_latin1[j]);
                            }
                        }

                        if (HAS_NONLATIN1_SIMPLE_FOLD_CLOSURE(j)
                            && (! isASCII(j) || ! ASCII_FOLD_RESTRICTED))
                        {
                            add_above_Latin1_folds(pRExC_state,
                                                   (U8) j,
                                                   use_list);
                        }
                        continue;
                    }

                    folded = _to_uni_fold_flags(j, foldbuf, &foldlen,
                                                        (ASCII_FOLD_RESTRICTED)
                                                        ? FOLD_FLAGS_NOMIX_ASCII
                                                        : 0);

                    folds_count = _inverse_folds(folded, &first_fold,
                                                    &remaining_folds);
                    for (k = 0; k <= folds_count; k++) {
                        UV c = (k == 0)
                                ? folded
                                : (k == 1)
                                   ? first_fold

                                   : remaining_folds[k-2];

                        if ((   ASCII_FOLD_RESTRICTED
                            && (isASCII(c) != isASCII(j))))
                        {
                            continue;
                        }

                        if (c < 256 && LOC) {
                            *use_list = add_cp_to_invlist(*use_list, c);
                            continue;
                        }

                        if (isASCII(c) || c > 255 || AT_LEAST_UNI_SEMANTICS)
                        {
                            cp_list = add_cp_to_invlist(cp_list, c);
                        }
                        else {

                            upper_latin1_only_utf8_matches
                                    = add_cp_to_invlist(
                                                upper_latin1_only_utf8_matches,
                                                c);
                        }
                    }
                }
            }
            SvREFCNT_dec_NN(fold_intersection);
        }

        _invlist_union(cp_list, cp_foldable_list, &cp_list);
	SvREFCNT_dec_NN(cp_foldable_list);
    }

    if (simple_posixes) {
        if (cp_list) {
            _invlist_union(cp_list, simple_posixes, &cp_list);
            SvREFCNT_dec_NN(simple_posixes);
        }
        else {
            cp_list = simple_posixes;
        }
    }
    if (posixes || nposixes) {
        if (! DEPENDS_SEMANTICS) {

            if (posixes) {
                if (cp_list) {
                    _invlist_union(cp_list, posixes, &cp_list);
                    SvREFCNT_dec_NN(posixes);
                }
                else {
                    cp_list = posixes;
                }
            }
            if (nposixes) {
                if (cp_list) {
                    _invlist_union(cp_list, nposixes, &cp_list);
                    SvREFCNT_dec_NN(nposixes);
                }
                else {
                    cp_list = nposixes;
                }
            }
        }
        else {

            if (nposixes) {
                SV* only_non_utf8_list = invlist_clone(PL_UpperLatin1, NULL);

                if (cp_list) {
                    _invlist_union(cp_list, nposixes, &cp_list);
                    SvREFCNT_dec_NN(nposixes);
                    nposixes = NULL;
                }
                else {
                    cp_list = nposixes;
                }

                _invlist_union(posixes, cp_list, &cp_list);
                SvREFCNT_dec(posixes);

                if (upper_latin1_only_utf8_matches) {
                    _invlist_union(cp_list,
                                   upper_latin1_only_utf8_matches,
                                   &cp_list);
                    SvREFCNT_dec_NN(upper_latin1_only_utf8_matches);
                    upper_latin1_only_utf8_matches = NULL;
                }

                _invlist_subtract(only_non_utf8_list, cp_list,
                                  &only_non_utf8_list);
                if (_invlist_len(only_non_utf8_list) != 0) {
                    anyof_flags |= ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER;
                }
                SvREFCNT_dec_NN(only_non_utf8_list);
            }
            else {

                SV* nonascii_but_latin1_properties = NULL;
                _invlist_intersection(posixes, PL_UpperLatin1,
                                      &nonascii_but_latin1_properties);

                _invlist_union(upper_latin1_only_utf8_matches,
                               nonascii_but_latin1_properties,
                               &upper_latin1_only_utf8_matches);

                _invlist_subtract(posixes, nonascii_but_latin1_properties,
                                  &posixes);

                if (cp_list) {
                    _invlist_union(cp_list, posixes, &cp_list);
                    SvREFCNT_dec_NN(posixes);
                    posixes = NULL;
                }
                else {
                    cp_list = posixes;
                }

                SvREFCNT_dec(nonascii_but_latin1_properties);

                _invlist_subtract(upper_latin1_only_utf8_matches,
                                  cp_list,
                                  &upper_latin1_only_utf8_matches);
                if (_invlist_len(upper_latin1_only_utf8_matches) == 0) {
                    SvREFCNT_dec_NN(upper_latin1_only_utf8_matches);
                    upper_latin1_only_utf8_matches = NULL;
                }
            }
        }
    }

    if (properties) {
        if (cp_list) {

            if (warn_super) {
                warn_super = ! (invert
                               ^ (invlist_highest(cp_list) > PERL_UNICODE_MAX));
            }

            _invlist_union(properties, cp_list, &cp_list);
            SvREFCNT_dec_NN(properties);
        }
        else {
            cp_list = properties;
        }

        if (warn_super) {
            anyof_flags
             |= ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER;

            optimizable = FALSE;
        }
    }

    if (LOC && FOLD) {

        if (only_utf8_locale_list && cp_list) {
            _invlist_subtract(only_utf8_locale_list, cp_list,
                              &only_utf8_locale_list);

            if (_invlist_len(only_utf8_locale_list) == 0) {
                SvREFCNT_dec_NN(only_utf8_locale_list);
                only_utf8_locale_list = NULL;
            }
        }
        if (    only_utf8_locale_list
            || (cp_list && (   _invlist_contains_cp(cp_list, LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE)
                            || _invlist_contains_cp(cp_list, LATIN_SMALL_LETTER_DOTLESS_I))))
        {
            has_runtime_dependency |= HAS_L_RUNTIME_DEPENDENCY;
            anyof_flags
                 |= ANYOFL_FOLD
                 |  ANYOFL_SHARED_UTF8_LOCALE_fold_HAS_MATCHES_nonfold_REQD;
        }
        else if (cp_list) {
            UV start, end;
            invlist_iterinit(cp_list);
            if (invlist_iternext(cp_list, &start, &end) && start < 256) {
                anyof_flags |= ANYOFL_FOLD;
                has_runtime_dependency |= HAS_L_RUNTIME_DEPENDENCY;
            }
            invlist_iterfinish(cp_list);
        }
    }
    else if (   DEPENDS_SEMANTICS
             && (    upper_latin1_only_utf8_matches
                 || (anyof_flags & ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER)))
    {
        RExC_seen_d_op = TRUE;
        has_runtime_dependency |= HAS_D_RUNTIME_DEPENDENCY;
    }

    if (     cp_list
        &&   invert
        && ! has_runtime_dependency)
    {
        _invlist_invert(cp_list);

	invert = FALSE;
    }

    if (ret_invlist) {
        *ret_invlist = cp_list;

        return RExC_emit;
    }

    *flagp |= HASWIDTH|SIMPLE;

    if (anyof_flags & ANYOF_LOCALE_FLAGS) {
        RExC_contains_locale = 1;
    }

    if (optimizable) {
        PERL_UINT_FAST8_T i;
        Size_t partial_cp_count = 0;
        UV start[MAX_FOLD_FROMS+1] = { 0 };
        UV   end[MAX_FOLD_FROMS+1] = { 0 };

        if (cp_list) {

            invlist_iterinit(cp_list);
            for (i = 0; i <= MAX_FOLD_FROMS; i++) {
                if (! invlist_iternext(cp_list, &start[i], &end[i])) {
                    break;
                }
                partial_cp_count += end[i] - start[i] + 1;
            }

            invlist_iterfinish(cp_list);
        }

        if (start[0] == 0 && end[0] == UV_MAX) {
            if (invert) {
                ret = reganode(pRExC_state, OPFAIL, 0);
            }
            else {
                ret = reg_node(pRExC_state, SANY);
                MARK_NAUGHTY(1);
            }
            goto not_anyof;
        }

        if (posixl) {
            for (namedclass = 0; namedclass < ANYOF_POSIXL_MAX;
                                                        namedclass += 2)
            {
                if (   POSIXL_TEST(posixl, namedclass)
                    && POSIXL_TEST(posixl, namedclass + 1))
                {
                    if (invert) {
                        ret = reganode(pRExC_state, OPFAIL, 0);
                    }
                    else {
                        ret = reg_node(pRExC_state, SANY);
                        MARK_NAUGHTY(1);
                    }
                    goto not_anyof;
                }
            }

#define isSINGLE_BIT_SET(n) isPOWER_OF_2(n)

            if (    isSINGLE_BIT_SET(posixl)
                && (partial_cp_count == 0 || start[0] > 255))
            {
                U8 classnum;
                SV * class_above_latin1 = NULL;
                bool already_inverted;
                bool are_equivalent;

                static const int MultiplyDeBruijnBitPosition2[32] =
                    {
                    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
                    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
                    };

                namedclass = MultiplyDeBruijnBitPosition2[(posixl
                                                          * 0x077CB531U) >> 27];
                classnum = namedclass_to_classnum(namedclass);

                already_inverted = namedclass
                                 - classnum_to_namedclass(classnum);

                _invlist_intersection_maybe_complement_2nd(
                                                    PL_AboveLatin1,
                                                    PL_XPosix_ptrs[classnum],
                                                    already_inverted,
                                                    &class_above_latin1);
                are_equivalent = _invlistEQ(class_above_latin1, cp_list,
                                                                        FALSE);
                SvREFCNT_dec_NN(class_above_latin1);

                if (are_equivalent) {

                    invert = invert ^ already_inverted;

                    ret = reg_node(pRExC_state,
                                   POSIXL + invert * (NPOSIXL - POSIXL));
                    FLAGS(REGNODE_p(ret)) = classnum;
                    goto not_anyof;
                }
            }
        }

        if (has_runtime_dependency & HAS_USER_DEFINED_PROPERTY) {
            goto is_anyof;
        }

        if (! has_runtime_dependency) {

            if (partial_cp_count == 0) {
                if (invert) {
                    ret = reg_node(pRExC_state, SANY);
                }
                else {
                    ret = reganode(pRExC_state, OPFAIL, 0);
                }

                goto not_anyof;
            }

            if (   start[0] == 0 && end[0] == '\n' - 1
                && start[1] == '\n' + 1 && end[1] == UV_MAX)
            {
                assert (! invert);
                ret = reg_node(pRExC_state, REG_ANY);
                MARK_NAUGHTY(1);
                goto not_anyof;
            }
        }

        if (   ! posixl
            && ! invert

            &&   partial_cp_count > 0 && partial_cp_count <= MAX_FOLD_FROMS + 1

            && (start[0] < 256 || UTF || FOLD))
        {
            if (partial_cp_count == 1 && ! upper_latin1_only_utf8_matches)
            {

                if (LOC) {

                    op = (FOLD) ? EXACTFL : EXACTL;
                }
                else if (! FOLD) {
                    op = (start[0] < 256) ? EXACT : EXACT_ONLY8;
                }
                else if (start[0] < 256) {

                    op = IS_IN_SOME_FOLD_L1(start[0])
                         ? EXACTFU
                         : EXACT;
                }
                else {
                    op = _invlist_contains_cp(PL_InMultiCharFold,
                                              start[0])
                         ? EXACTFU_ONLY8
                         : EXACT_ONLY8;
                }

                value = start[0];
            }
            else if (  ! (has_runtime_dependency & ~HAS_D_RUNTIME_DEPENDENCY)
                     && _invlist_contains_cp(PL_in_some_fold, start[0]))
            {

                if (partial_cp_count == 2 && isASCII(start[0])) {

                    assert(isALPHA(start[0]));
                    if (   end[0] == start[0]
                        && isALPHA_FOLD_EQ(start[0], start[1]))
                    {

                        if (   ASCII_FOLD_RESTRICTED
                            || HAS_NONLATIN1_SIMPLE_FOLD_CLOSURE(start[0]))
                        {

                            op = EXACTFAA;
                        }
                        else if (HAS_NONLATIN1_FOLD_CLOSURE(start[0])) {

                            op = (FOLD) ? EXACTFU : EXACTFAA;
                        }
                        else {

                            op = EXACTFU;
                        }

                        value = toFOLD(start[0]);
                    }
                }
                else if (  ! upper_latin1_only_utf8_matches
                         || (   _invlist_len(upper_latin1_only_utf8_matches)
                                                                          == 2
                             && PL_fold_latin1[
                               invlist_highest(upper_latin1_only_utf8_matches)]
                             == start[0]))
                {

                    Size_t foldlen;
                    U8 foldbuf[UTF8_MAXBYTES_CASE];
                    UV folded = _to_uni_fold_flags(start[0],
                                                        foldbuf, &foldlen, 0);
                    unsigned int first_fold;
                    const unsigned int * remaining_folds;
                    Size_t folds_to_this_cp_count = _inverse_folds(
                                                            folded,
                                                            &first_fold,
                                                            &remaining_folds);
                    Size_t folds_count = folds_to_this_cp_count + 1;
                    SV * fold_list = _new_invlist(folds_count);
                    unsigned int i;

                    SV * all_cp_list = NULL;
                    SV ** use_this_list = &cp_list;

                    if (upper_latin1_only_utf8_matches) {
                        all_cp_list = _new_invlist(0);
                        use_this_list = &all_cp_list;
                        _invlist_union(cp_list,
                                       upper_latin1_only_utf8_matches,
                                       use_this_list);
                    }

                    fold_list = add_cp_to_invlist(fold_list, start[0]);
                    fold_list = add_cp_to_invlist(fold_list, folded);
                    if (folds_to_this_cp_count > 0) {
                        fold_list = add_cp_to_invlist(fold_list, first_fold);
                        for (i = 0; i + 1 < folds_to_this_cp_count; i++) {
                            fold_list = add_cp_to_invlist(fold_list,
                                                        remaining_folds[i]);
                        }
                    }

                    if (_invlistEQ(*use_this_list, fold_list,
                                   0  )
                    ) {

                        if (start[0] > 255) {
                            if (FOLD || ! _invlist_contains_cp(
                                            PL_InMultiCharFold, folded))
                            {
                                op = (LOC)
                                     ? EXACTFLU8
                                     : (ASCII_FOLD_RESTRICTED)
                                       ? EXACTFAA
                                       : EXACTFU_ONLY8;
                                value = folded;
                            }
                        }
                        else if (    FOLD
                                 &&  folded == 's'
                                 &&  DEPENDS_SEMANTICS)
                        {
                            op = EXACTFU_S_EDGE;
                            value = folded;
                        }
                        else if (    FOLD
                                || ! HAS_NONLATIN1_FOLD_CLOSURE(start[0]))
                        {
                            if (upper_latin1_only_utf8_matches) {
                                op = EXACTF;

                                value = start[0];
                            }
                            else if (     UNLIKELY(start[0] == MICRO_SIGN)
                                     && ! UTF)
                            {
                                op = (ASCII_FOLD_RESTRICTED)
                                     ? EXACTFAA
                                     : EXACTFUP;
                                value = MICRO_SIGN;
                            }
                            else if (     ASCII_FOLD_RESTRICTED
                                     && ! isASCII(start[0]))
                            {
                                op = EXACTFAA;
                                value = folded;
                            }
                            else {
                                op = EXACTFU;
                                value = folded;
                            }
                        }
                    }

                    SvREFCNT_dec_NN(fold_list);
                    SvREFCNT_dec(all_cp_list);
                }
            }

            if (op != END) {

                if (! UTF && value > 255) {
                    SV * in_multis = NULL;

                    assert(FOLD);

                    _invlist_intersection(PL_InMultiCharFold, cp_list, &in_multis);
                    if (UNLIKELY(_invlist_len(in_multis) != 0)) {
                        REQUIRE_UTF8(flagp);
                    }
                    else {
                        op = END;
                    }
                }

                if (op != END) {
                    U8 len = (UTF) ? UVCHR_SKIP(value) : 1;

                    ret = regnode_guts(pRExC_state, op, len, "exact");
                    FILL_NODE(ret, op);
                    RExC_emit += 1 + STR_SZ(len);
                    STR_LEN(REGNODE_p(ret)) = len;
                    if (len == 1) {
                        *STRING(REGNODE_p(ret)) = (U8) value;
                    }
                    else {
                        uvchr_to_utf8((U8 *) STRING(REGNODE_p(ret)), value);
                    }
                    goto not_anyof;
                }
            }
        }

        if (! has_runtime_dependency) {

            PERL_UINT_FAST8_T inverted = 0;
#ifdef EBCDIC
            const PERL_UINT_FAST8_T max_permissible = 0xFF;
#else
            const PERL_UINT_FAST8_T max_permissible = 0x7F;
#endif

            if (invlist_highest(cp_list) > max_permissible) {
                _invlist_invert(cp_list);
                inverted = 1;
            }

            if (invlist_highest(cp_list) <= max_permissible) {
                UV this_start, this_end;
                UV lowest_cp = UV_MAX;
                U8 bits_differing = 0;
                Size_t full_cp_count = 0;
                bool first_time = TRUE;

                invlist_iterinit(cp_list);
                while (invlist_iternext(cp_list, &this_start, &this_end)) {
                    unsigned int i = this_start;

                    if (first_time) {
                        if (! UVCHR_IS_INVARIANT(i)) {
                            goto done_anyofm;
                        }

                        first_time = FALSE;
                        lowest_cp = this_start;

                        i++;
                    }

                    for (; i <= this_end; i++) {
                        if (! UVCHR_IS_INVARIANT(i)) {
                            goto done_anyofm;
                        }

                        bits_differing  |= i ^ lowest_cp;
                    }

                    full_cp_count += this_end - this_start + 1;
                }
                invlist_iterfinish(cp_list);

                if (  (inverted || full_cp_count > 1)
                    && full_cp_count == 1U << PL_bitcount[bits_differing])
                {
                    U8 ANYOFM_mask;

                    op = ANYOFM + inverted;;

                    ANYOFM_mask = ~ bits_differing;

                    ret = reganode(pRExC_state, op, lowest_cp);
                    FLAGS(REGNODE_p(ret)) = ANYOFM_mask;
                }
            }
          done_anyofm:

            if (inverted) {
                _invlist_invert(cp_list);
            }

            if (op != END) {
                goto not_anyof;
            }
        }

        if (! (anyof_flags & ANYOF_LOCALE_FLAGS)) {
            PERL_UINT_FAST8_T type;
            SV * intersection = NULL;
            SV* d_invlist = NULL;

            for (type = POSIXA; type >= POSIXD; type--) {
                int posix_class;

                if (type == POSIXL) {
                    continue;
                }

                for (posix_class = 0;
                     posix_class <= _HIGHEST_REGCOMP_DOT_H_SYNC;
                     posix_class++)
                {
                    SV** our_code_points = &cp_list;
                    SV** official_code_points;
                    int try_inverted;

                    if (type == POSIXA) {
                        official_code_points = &PL_Posix_ptrs[posix_class];
                    }
                    else {
                        official_code_points = &PL_XPosix_ptrs[posix_class];
                    }

                    if (! *official_code_points) {
                        continue;
                    }

                    for (try_inverted = 0; try_inverted < 2; try_inverted++) {
                        bool this_inverted = invert ^ try_inverted;

                        if (type != POSIXD) {

                            if (has_runtime_dependency
                                                    & HAS_D_RUNTIME_DEPENDENCY)
                            {
                                continue;
                            }
                        }
                        else  if (! this_inverted) {

                            _invlist_intersection(cp_list, PL_UpperLatin1,
                                                           &intersection);
                            if (_invlist_len(intersection) != 0) {
                                continue;
                            }

                            SvREFCNT_dec(d_invlist);
                            d_invlist = invlist_clone(cp_list, NULL);

                            if (upper_latin1_only_utf8_matches) {
                                _invlist_union(
                                            d_invlist,
                                            upper_latin1_only_utf8_matches,
                                            &d_invlist);
                            }
                            our_code_points = &d_invlist;
                        }
                        else {
                            if (! (anyof_flags & ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER))
                            {
                                continue;
                            }
                            our_code_points = &cp_list;
                        }

                        if (_invlistEQ(*our_code_points,
                                       *official_code_points,
                                       try_inverted))
                        {

                            ret = reg_node(pRExC_state, (try_inverted)
                                                        ? type + NPOSIXA
                                                                - POSIXA
                                                        : type);
                            FLAGS(REGNODE_p(ret)) = posix_class;
                            SvREFCNT_dec(d_invlist);
                            SvREFCNT_dec(intersection);
                            goto not_anyof;
                        }
                    }
                }
            }
            SvREFCNT_dec(d_invlist);
            SvREFCNT_dec(intersection);
        }

        if (     start[0] >= NUM_ANYOF_CODE_POINTS
            && ! LOC
            && ! upper_latin1_only_utf8_matches
            &&   anyof_flags == 0)
        {
            UV highest_cp = invlist_highest(cp_list);

            if (highest_cp > IV_MAX) {
                anyof_flags = 0;
            }
            else {
                U8 low_utf8[UTF8_MAXBYTES+1];
                U8 high_utf8[UTF8_MAXBYTES+1];

                (void) uvchr_to_utf8(low_utf8, start[0]);
                (void) uvchr_to_utf8(high_utf8, invlist_highest(cp_list));

                anyof_flags = (low_utf8[0] == high_utf8[0])
                            ? low_utf8[0]
                            : 0;
            }

            op = ANYOFH;
        }
    }

  is_anyof:
    if (op != ANYOFH) {
        op = (has_runtime_dependency & HAS_D_RUNTIME_DEPENDENCY)
             ? ANYOFD
             : ((posixl)
                ? ANYOFPOSIXL
                : ((LOC)
                   ? ANYOFL
                   : ANYOF));
    }

    ret = regnode_guts(pRExC_state, op, regarglen[op], "anyof");
    FILL_NODE(ret, op);
    RExC_emit += 1 + regarglen[op];
    ANYOF_FLAGS(REGNODE_p(ret)) = anyof_flags;

    populate_ANYOF_from_invlist(REGNODE_p(ret), &cp_list);

    if (posixl) {
        ANYOF_POSIXL_SET_TO_BITMAP(REGNODE_p(ret), posixl);
    }

    if (invert) {
        ANYOF_FLAGS(REGNODE_p(ret)) |= ANYOF_INVERT;
    }

    if (upper_latin1_only_utf8_matches) {
	if (cp_list) {
	    _invlist_union(cp_list,
                           upper_latin1_only_utf8_matches,
                           &cp_list);
	    SvREFCNT_dec_NN(upper_latin1_only_utf8_matches);
	}
	else {
	    cp_list = upper_latin1_only_utf8_matches;
	}
        ANYOF_FLAGS(REGNODE_p(ret)) |= ANYOF_SHARED_d_UPPER_LATIN1_UTF8_STRING_MATCHES_non_d_RUNTIME_USER_PROP;
    }

    set_ANYOF_arg(pRExC_state, REGNODE_p(ret), cp_list,
                  (HAS_NONLOCALE_RUNTIME_PROPERTY_DEFINITION)
                   ? listsv : NULL,
                  only_utf8_locale_list);
    return ret;

  not_anyof:

    Set_Node_Offset_Length(REGNODE_p(ret), orig_parse - RExC_start,
                                           RExC_parse - orig_parse);;
    SvREFCNT_dec(cp_list);;
    return ret;
}
}
