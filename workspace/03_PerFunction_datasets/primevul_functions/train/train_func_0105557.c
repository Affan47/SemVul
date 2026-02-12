STATIC bool
S_grok_bslash_N(pTHX_ RExC_state_t *pRExC_state,
                regnode_offset * node_p,
                UV * code_point_p,
                int * cp_count,
                I32 * flagp,
                const bool strict,
                const U32 depth
    )
{

    char * endbrace;
    char* p = RExC_parse;

    SV * substitute_parse = NULL;
    char *orig_end;
    char *save_start;
    I32 flags;

    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_GROK_BSLASH_N;

    GET_RE_DEBUG_FLAGS;

    assert(cBOOL(node_p) ^ cBOOL(code_point_p));
    assert(! (node_p && cp_count));

    if (cp_count) {
        *cp_count = 1;
    }

    skip_to_be_ignored_text(pRExC_state, &p,
                            FALSE  );

    if (*p != '{' || regcurly(p)) {
        RExC_parse = p;
        if (cp_count) {
            *cp_count = -1;
        }

        if (! node_p) {
            return FALSE;
        }

        *node_p = reg_node(pRExC_state, REG_ANY);
        *flagp |= HASWIDTH|SIMPLE;
        MARK_NAUGHTY(1);
        Set_Node_Length(REGNODE_p(*(node_p)), 1);
        return TRUE;
    }

    if (*RExC_parse != '{') {
        vFAIL("Missing braces on \\N{}");
    }

    RExC_parse++;

    endbrace = (char *) memchr(RExC_parse, '}', RExC_end - RExC_parse);
    if (! endbrace) {
        vFAIL2("Missing right brace on \\%c{}", 'N');
    }

    REQUIRE_UNI_RULES(flagp, FALSE);

    if (endbrace - RExC_parse == 1 && *RExC_parse == '_') {
        RExC_parse = endbrace;
        if (strict) {
            RExC_parse++;
            vFAIL("Zero length \\N{}");
        }

        if (cp_count) {
            *cp_count = 0;
        }
        nextchar(pRExC_state);
        if (! node_p) {
            return FALSE;
        }

        *node_p = reg_node(pRExC_state, NOTHING);
        return TRUE;
    }

    if (endbrace - RExC_parse < 2 || ! strBEGINs(RExC_parse, "U+")) {

        const STRLEN name_len = endbrace - RExC_parse;
        SV *  value_sv;
        SV ** value_svp;
        const U8 * value;
        STRLEN value_len;

        if (! RExC_unlexed_names) {
            RExC_unlexed_names = newHV();
        }

        if ((value_svp = hv_fetch(RExC_unlexed_names, RExC_parse,
                                                      name_len, 0)))
        {
            value_sv = *value_svp;
        }
        else {
            const char * error_msg = NULL;
            value_sv = get_and_check_backslash_N_name(RExC_parse, endbrace,
                                                      UTF,
                                                      &error_msg);
            if (error_msg) {
                RExC_parse = endbrace;
                vFAIL(error_msg);
            }

            assert (value_sv);

            if (! hv_store(RExC_unlexed_names, RExC_parse, name_len,
                           value_sv, 0))
            {
                Perl_croak(aTHX_ "panic: hv_store() unexpectedly failed");
            }
        }

        value = (U8 *) SvPV(value_sv, value_len);

        if (value_len > 0 && value_len <= (UV) ((SvUTF8(value_sv))
                                               ? UTF8SKIP(value)
                                               : 1))
        {

            if (! code_point_p) {
                RExC_parse = p;
                return FALSE;
            }

            *code_point_p = (SvUTF8(value_sv))
                            ? valid_utf8_to_uvchr(value, NULL)
                            : *value;

            RExC_parse = endbrace;
            nextchar(pRExC_state);
            return TRUE;
        }

        if (cp_count) {
            *cp_count = 0;

            *cp_count = (SvUTF8(value_sv))
                        ? utf8_length(value, value + value_len)
                        : value_len;
        }

        if (! node_p) {
            if (! cp_count) {
                RExC_parse = p;
            }
            return FALSE;
        }

        substitute_parse = newSVpvs("?:");
        sv_catsv(substitute_parse, value_sv);
        sv_catpv(substitute_parse, ")");

#ifdef EBCDIC

        assert(! RExC_recode_x_to_native);
#endif

    }
    else {
        Size_t count = 0;

        RExC_parse += 2;

        do {
            UV cp = 0;
            char * start_digit;
            if (! isXDIGIT(*RExC_parse)) {
                RExC_parse++;
                vFAIL("Invalid hexadecimal number in \\N{U+...}");
            }

            start_digit = RExC_parse;
            count++;

            do {

                if (cp > MAX_LEGAL_CP >> 4) {

                    do {
                        RExC_parse ++;
                    } while (isXDIGIT(*RExC_parse) || *RExC_parse == '_');

                    vFAIL4("Use of code point 0x%.*s is not allowed; the"
                        " permissible max is 0x%" UVxf,
                        (int) (RExC_parse - start_digit), start_digit,
                        MAX_LEGAL_CP);
                }

                cp  = (cp << 4) + READ_XDIGIT(RExC_parse);

                if (*RExC_parse == '_' && isXDIGIT(RExC_parse[1])) {
                    RExC_parse++;
                }
            } while (isXDIGIT(*RExC_parse));

            if (RExC_parse >= endbrace) {
                if (count != 1) {
                    goto do_concat;
                }

                if (! code_point_p) {
                    RExC_parse = p;
                    return FALSE;
                }

                *code_point_p = UNI_TO_NATIVE(cp);
                RExC_parse = endbrace;
                nextchar(pRExC_state);
                return TRUE;
            }

            if (*RExC_parse != '.' || RExC_parse + 1 >= endbrace) {
                RExC_parse += (RExC_orig_utf8)
                                ? UTF8SKIP(RExC_parse)
                                : 1;
                if (RExC_parse >= endbrace) {
                    RExC_parse = endbrace;
                }
                vFAIL("Invalid hexadecimal number in \\N{U+...}");
            }

            if (! node_p && ! cp_count) {
                return FALSE;
            }

            if (node_p && count == 1) {
                substitute_parse = newSVpvs("?:");
            }

          do_concat:

            if (node_p) {

                sv_catpvs(substitute_parse, "\\x{");
                sv_catpvn(substitute_parse, start_digit,
                                            RExC_parse - start_digit);
                sv_catpvs(substitute_parse, "}");
            }

            RExC_parse++;
            count++;

        } while (RExC_parse < endbrace);

        if (! node_p) {
            assert (cp_count);

            *cp_count = count;
            return FALSE;
        }

        sv_catpvs(substitute_parse, ")");

#ifdef EBCDIC

        RExC_recode_x_to_native = 1;
#endif

    }

    save_start = RExC_start;
    orig_end = RExC_end;

    RExC_parse = RExC_start = SvPVX(substitute_parse);
    RExC_end = RExC_parse + SvCUR(substitute_parse);
    TURN_OFF_WARNINGS_IN_SUBSTITUTE_PARSE;

    *node_p = reg(pRExC_state, 1, &flags, depth+1);

    RESTORE_WARNINGS;
    RExC_start = save_start;
    RExC_parse = endbrace;
    RExC_end = orig_end;
#ifdef EBCDIC
    RExC_recode_x_to_native = 0;
#endif

    SvREFCNT_dec_NN(substitute_parse);

    if (! *node_p) {
        RETURN_FAIL_ON_RESTART(flags, flagp);
        FAIL2("panic: reg returned failure to grok_bslash_N, flags=%#" UVxf,
            (UV) flags);
    }
    *flagp |= flags&(HASWIDTH|SPSTART|SIMPLE|POSTPONED);

    nextchar(pRExC_state);

    return TRUE;
}
}
