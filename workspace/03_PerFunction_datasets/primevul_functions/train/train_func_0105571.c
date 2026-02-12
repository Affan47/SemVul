STATIC regnode_offset
S_handle_regex_sets(pTHX_ RExC_state_t *pRExC_state, SV** return_invlist,
                    I32 *flagp, U32 depth,
                    char * const oregcomp_parse)
{


    U8 curchar;
    UV start, end;
    SV* final = NULL;
    SV* result_string;
    AV* stack;

    AV* fence_stack = NULL;


    volatile IV fence = 0;


    STRLEN len;
    regnode_offset node;

    const bool save_fold = FOLD;
    char *save_end, *save_parse;
    const bool in_locale = LOC;

    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_HANDLE_REGEX_SETS;

    DEBUG_PARSE("xcls");

    if (in_locale) {
        set_regex_charset(&RExC_flags, REGEX_UNICODE_CHARSET);
    }


    REQUIRE_UNI_RULES(flagp, 0);

    ckWARNexperimental(RExC_parse,
                       WARN_EXPERIMENTAL__REGEX_SETS,
                       "The regex_sets feature is experimental");


#define IS_OPERATOR(a) SvIOK(a)
#define IS_OPERAND(a)  (! IS_OPERATOR(a))


    sv_2mortal((SV *)(stack = newAV()));
    sv_2mortal((SV *)(fence_stack = newAV()));

    while (RExC_parse < RExC_end) {
        I32 top_index;
        SV** top_ptr;
        SV* current = NULL;

        SV* only_to_avoid_leaks;

        skip_to_be_ignored_text(pRExC_state, &RExC_parse,
                                TRUE  );
        if (RExC_parse >= RExC_end) {
            break;
        }

        curchar = UCHARAT(RExC_parse);

redo_curchar:

#ifdef ENABLE_REGEX_SETS_DEBUGGING

        DEBUG_U(dump_regex_sets_structures(pRExC_state,
                                           stack, fence, fence_stack));
#endif

        top_index = av_tindex_skip_len_mg(stack);

        switch (curchar) {
            SV** stacked_ptr;
            char stacked_operator;
            SV* lhs;
            SV* rhs;
            SV* fence_ptr;


            case '(':

                if (   RExC_parse < RExC_end - 2
                    && UCHARAT(RExC_parse + 1) == '?'
                    && UCHARAT(RExC_parse + 2) == '^')
                {


                    U32 save_flags = RExC_flags;
                    const char * save_parse;

                    RExC_parse += 2;
                    save_parse = RExC_parse;


                    parse_lparen_question_flags(pRExC_state);

                    if (   RExC_parse >= RExC_end - 4
                        || UCHARAT(RExC_parse) != ':'
                        || UCHARAT(++RExC_parse) != '('
                        || UCHARAT(++RExC_parse) != '?'
                        || UCHARAT(++RExC_parse) != '[')
                    {


                        if (RExC_parse >= RExC_end - 4) {
                            RExC_parse = RExC_end;
                        }
                        else if (RExC_parse != save_parse) {
                            RExC_parse += (UTF)
                                          ? UTF8_SAFE_SKIP(RExC_parse, RExC_end)
                                          : 1;
                        }
                        vFAIL("Expecting '(?flags:(?[...'");
                    }


                    RExC_parse++;
                    if (! handle_regex_sets(pRExC_state, &current, flagp,
                                                    depth+1, oregcomp_parse))
                    {
                        RETURN_FAIL_ON_RESTART(*flagp, flagp);
                    }


                    RExC_parse++;
                    if (UCHARAT(RExC_parse) != ')')
                        vFAIL("Expecting close paren for nested extended charclass");


                    RExC_parse++;
                    if (UCHARAT(RExC_parse) != ')')
                        vFAIL("Expecting close paren for wrapper for nested extended charclass");

                    RExC_flags = save_flags;
                    goto handle_operand;
                }


                if (top_index - fence >= 0) {


                    if (   ! (top_ptr = av_fetch(stack, top_index, FALSE))
                        || (IS_OPERATOR(*top_ptr) && SvUV(*top_ptr) != '!')
                        || (   IS_OPERAND(*top_ptr)
                            && (   top_index - fence < 1
                                || ! (stacked_ptr = av_fetch(stack,
                                                             top_index - 1,
                                                             FALSE))
                                || ! IS_OPERATOR(*stacked_ptr))))
                    {
                        RExC_parse++;
                        vFAIL("Unexpected '(' with no preceding operator");
                    }
                }


                av_push(fence_stack, newSViv(fence));
                fence = top_index + 1;
                break;

            case '\\':


                if (!regclass(pRExC_state, flagp, depth+1,
                              TRUE,
                              FALSE,
                              FALSE,
                              TRUE,
                              FALSE,
                              &current))
                {
                    RETURN_FAIL_ON_RESTART(*flagp, flagp);
                    goto regclass_failed;
                }


                RExC_parse--;
                goto handle_operand;

            case '[':
            {

                bool is_posix_class = (OOB_NAMEDCLASS
                            < handle_possible_posix(pRExC_state,
                                                RExC_parse + 1,
                                                NULL,
                                                NULL,
                                                TRUE ));


                if (! is_posix_class) {
                    RExC_parse++;
                }


                if (!regclass(pRExC_state, flagp, depth+1,
                                is_posix_class,


                                FALSE,
                                TRUE,
                                TRUE,
                                FALSE,
                                &current))
                {
                    RETURN_FAIL_ON_RESTART(*flagp, flagp);
                    goto regclass_failed;
                }

                if (! current) {
                    break;
                }


                if (is_posix_class) {
                    RExC_parse--;
                }

                goto handle_operand;
            }

            case ']':
                if (top_index >= 1) {
                    goto join_operators;
                }


                goto done;

            case ')':
                if (av_tindex_skip_len_mg(fence_stack) < 0) {
                    if (UCHARAT(RExC_parse - 1) == ']')  {
                        break;
                    }
                    RExC_parse++;
                    vFAIL("Unexpected ')'");
                }


                if (top_index - fence < 0) {
                    RExC_parse++;
                    goto bad_syntax;
                }


                if (top_index - fence >= 1) {
                    goto join_operators;
                }


                fence_ptr = av_pop(fence_stack);
                assert(fence_ptr);
                fence = SvIV(fence_ptr);
                SvREFCNT_dec_NN(fence_ptr);
                fence_ptr = NULL;

                if (fence < 0) {
                    fence = 0;
                }


                current = av_pop(stack);
                if (IS_OPERAND(current)) {
                    goto handle_operand;
                }

                RExC_parse++;
                goto bad_syntax;

            case '&':
            case '|':
            case '+':
            case '-':
            case '^':


                if (   top_index - fence < 0
                    || top_index - fence == 1
                    || ( ! (top_ptr = av_fetch(stack, top_index, FALSE)))
                    || ! IS_OPERAND(*top_ptr))
                {
                    goto unexpected_binary;
                }


                if (top_index - fence < 2) {


                    SV* lhs = av_pop(stack);
                    av_push(stack, newSVuv(curchar));
                    av_push(stack, lhs);
                    break;
                }


             join_operators:


                if (   ! (stacked_ptr = av_fetch(stack, top_index - 2, FALSE))
                    || IS_OPERAND(*stacked_ptr))
                {


                    if (curchar == ']') {
                        goto done;
                    }

                  unexpected_binary:
                    RExC_parse++;
                    vFAIL2("Unexpected binary operator '%c' with no "
                           "preceding operand", curchar);
                }
                stacked_operator = (char) SvUV(*stacked_ptr);

                if (regex_set_precedence(curchar)
                    > regex_set_precedence(stacked_operator))
                {


                    lhs = av_pop(stack);
                    assert(IS_OPERAND(lhs));

                    av_push(stack, newSVuv(curchar));
                    av_push(stack, lhs);
                    break;
                }


                rhs = av_pop(stack);
                if (! IS_OPERAND(rhs)) {


                    goto bad_syntax;
                }

                lhs = av_pop(stack);

                if (! IS_OPERAND(lhs)) {


                    goto bad_syntax;
                }

                switch (stacked_operator) {
                    case '&':
                        _invlist_intersection(lhs, rhs, &rhs);
                        break;

                    case '|':
                    case '+':
                        _invlist_union(lhs, rhs, &rhs);
                        break;

                    case '-':
                        _invlist_subtract(lhs, rhs, &rhs);
                        break;

                    case '^':
                    {
                        SV* i = NULL;
                        SV* u = NULL;

                        _invlist_union(lhs, rhs, &u);
                        _invlist_intersection(lhs, rhs, &i);
                        _invlist_subtract(u, i, &rhs);
                        SvREFCNT_dec_NN(i);
                        SvREFCNT_dec_NN(u);
                        break;
                    }
                }
                SvREFCNT_dec(lhs);


                only_to_avoid_leaks = av_pop(stack);
                SvREFCNT_dec(only_to_avoid_leaks);
                av_push(stack, rhs);
                goto redo_curchar;

            case '!':


                if (   (top_ptr = av_fetch(stack, top_index, FALSE))
                    && (IS_OPERATOR(*top_ptr) && SvUV(*top_ptr) == '!'))
                {
                    only_to_avoid_leaks = av_pop(stack);
                    SvREFCNT_dec(only_to_avoid_leaks);
                }
                else {

                    av_push(stack, newSVuv(curchar));
                }
                break;

            default:
                RExC_parse += (UTF) ? UTF8SKIP(RExC_parse) : 1;
                if (RExC_parse >= RExC_end) {
                    break;
                }
                vFAIL("Unexpected character");

          handle_operand:


            top_index = av_tindex_skip_len_mg(stack);
            if (top_index - fence >= 0) {


                top_ptr = av_fetch(stack, top_index, FALSE);
                assert(top_ptr);
                if (IS_OPERATOR(*top_ptr)) {


                    curchar = (char) SvUV(*top_ptr);
                    if (curchar != '!') {
                        SvREFCNT_dec(current);
                        vFAIL2("Unexpected binary operator '%c' with no "
                                "preceding operand", curchar);
                    }

                    _invlist_invert(current);

                    only_to_avoid_leaks = av_pop(stack);
                    SvREFCNT_dec(only_to_avoid_leaks);


                    goto handle_operand;
                }


                else if ((top_index - fence == 0 && curchar != ')')
                         || (top_index - fence > 0
                             && (! (stacked_ptr = av_fetch(stack,
                                                           top_index - 1,
                                                           FALSE))
                                 || IS_OPERAND(*stacked_ptr))))
                {
                    SvREFCNT_dec(current);
                    vFAIL("Operand with no preceding operator");
                }
            }


            av_push(stack, current);

        }

        RExC_parse += (UTF) ? UTF8SKIP(RExC_parse) : 1;
    }

    vFAIL("Syntax error in (?[...])");

  done:

    if (RExC_parse >= RExC_end || RExC_parse[1] != ')') {
        if (RExC_parse < RExC_end) {
            RExC_parse++;
        }

        vFAIL("Unexpected ']' with no following ')' in (?[...");
    }

    if (av_tindex_skip_len_mg(fence_stack) >= 0) {
        vFAIL("Unmatched (");
    }

    if (av_tindex_skip_len_mg(stack) < 0
        || ((final = av_pop(stack)) == NULL)
        || ! IS_OPERAND(final)
        || ! is_invlist(final)
        || av_tindex_skip_len_mg(stack) >= 0)
    {
      bad_syntax:
        SvREFCNT_dec(final);
        vFAIL("Incomplete expression within '(?[ ])'");
    }


    if (return_invlist) {
        *return_invlist = final;
        return END;
    }


    invlist_iterinit(final);
    result_string = newSVpvs("");
    while (invlist_iternext(final, &start, &end)) {
        if (start == end) {
            Perl_sv_catpvf(aTHX_ result_string, "\\x{%" UVXf "}", start);
        }
        else {
            Perl_sv_catpvf(aTHX_ result_string, "\\x{%" UVXf "}-\\x{%" UVXf "}",
                                                     start,          end);
        }
    }


    save_parse = RExC_parse;
    RExC_parse = SvPV(result_string, len);
    save_end = RExC_end;
    RExC_end = RExC_parse + len;
    TURN_OFF_WARNINGS_IN_SUBSTITUTE_PARSE;


    RExC_flags &= ~RXf_PMf_FOLD;


    node = regclass(pRExC_state, flagp, depth+1,
                    FALSE,
                    FALSE,
                    TRUE,


                    FALSE,
                    FALSE,
                    NULL
                );

    RESTORE_WARNINGS;
    RExC_parse = save_parse + 1;
    RExC_end = save_end;
    SvREFCNT_dec_NN(final);
    SvREFCNT_dec_NN(result_string);

    if (save_fold) {
        RExC_flags |= RXf_PMf_FOLD;
    }

    if (!node) {
        RETURN_FAIL_ON_RESTART(*flagp, flagp);
        goto regclass_failed;
    }


    if (in_locale) {
        set_regex_charset(&RExC_flags, REGEX_LOCALE_CHARSET);

        assert(OP(REGNODE_p(node)) == ANYOF);

        OP(REGNODE_p(node)) = ANYOFL;
        ANYOF_FLAGS(REGNODE_p(node))
                |= ANYOFL_SHARED_UTF8_LOCALE_fold_HAS_MATCHES_nonfold_REQD;
    }

    nextchar(pRExC_state);
    Set_Node_Length(REGNODE_p(node), RExC_parse - oregcomp_parse + 1);
    return node;

  regclass_failed:
    FAIL2("panic: regclass returned failure to handle_sets, " "flags=%#" UVxf,
                                                                (UV) *flagp);
}
