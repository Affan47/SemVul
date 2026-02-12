STATIC SV*
S__make_exactf_invlist(pTHX_ RExC_state_t *pRExC_state, regnode *node)
{
    dVAR;
    const U8 * s = (U8*)STRING(node);
    SSize_t bytelen = STR_LEN(node);
    UV uc;

    SV* invlist = _new_invlist(4);

    PERL_ARGS_ASSERT__MAKE_EXACTF_INVLIST;

    if (! UTF) {
        uc = *s;


        if (is_MULTI_CHAR_FOLD_latin1_safe(s, s + bytelen)) {
            invlist = _add_range_to_invlist(invlist, 0, UV_MAX);
        }
        else {


            if (OP(node) == EXACTFL) {
                _invlist_union(invlist, PL_Latin1, &invlist);
                invlist = add_cp_to_invlist(invlist,
                                                LATIN_SMALL_LETTER_DOTLESS_I);
                invlist = add_cp_to_invlist(invlist,
                                        LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE);
            }
            else {


                invlist = add_cp_to_invlist(invlist, uc);
                if (IS_IN_SOME_FOLD_L1(uc))
                    invlist = add_cp_to_invlist(invlist, PL_fold_latin1[uc]);
            }


            if (HAS_NONLATIN1_SIMPLE_FOLD_CLOSURE(uc)
                && (! isASCII(uc) || (OP(node) != EXACTFAA
                                    && OP(node) != EXACTFAA_NO_TRIE)))
            {
                add_above_Latin1_folds(pRExC_state, (U8) uc, &invlist);
            }
        }
    }
    else {
        U8 folded[UTF8_MAX_FOLD_CHAR_EXPAND * UTF8_MAXBYTES_CASE + 1] = { '\0' };
        const U8* e = s + bytelen;
        IV fc;

        fc = uc = utf8_to_uvchr_buf(s, s + bytelen, NULL);


        if (OP(node) == EXACTFL && is_PROBLEMATIC_LOCALE_FOLDEDS_START_cp(uc)) {


            U8 *d = folded;
            int i;

            fc = -1;
            for (i = 0; i < UTF8_MAX_FOLD_CHAR_EXPAND && s < e; i++) {
                if (isASCII(*s)) {
                    *(d++) = (U8) toFOLD(*s);
                    if (fc < 0) {
                        fc = *(d-1);
                    }
                    s++;
                }
                else {
                    STRLEN len;
                    UV fold = toFOLD_utf8_safe(s, e, d, &len);
                    if (fc < 0) {
                        fc = fold;
                    }
                    d += len;
                    s += UTF8SKIP(s);
                }
            }


            e = d;
            s = folded;
        }


        if (is_MULTI_CHAR_FOLD_utf8_safe(s, e)) {
            invlist = _add_range_to_invlist(invlist, 0, UV_MAX);
        }
        else {
            unsigned int k;
            unsigned int first_fold;
            const unsigned int * remaining_folds;
            Size_t folds_count;


            invlist = add_cp_to_invlist(invlist, fc);


            folds_count = _inverse_folds(fc, &first_fold,
                                                &remaining_folds);
            for (k = 0; k < folds_count; k++) {
                UV c = (k == 0) ? first_fold : remaining_folds[k-1];


                if (   (OP(node) == EXACTFAA || OP(node) == EXACTFAA_NO_TRIE)
                    && isASCII(c) != isASCII(fc))
                {
                    continue;
                }

                invlist = add_cp_to_invlist(invlist, c);
            }

            if (OP(node) == EXACTFL) {


                if (isALPHA_FOLD_EQ(fc, 'I')) {
                    invlist = add_cp_to_invlist(invlist,
                                                LATIN_SMALL_LETTER_DOTLESS_I);
                    invlist = add_cp_to_invlist(invlist,
                                        LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE);
                }
                else if (fc == LATIN_SMALL_LETTER_DOTLESS_I) {
                    invlist = add_cp_to_invlist(invlist, 'I');
                }
                else if (fc == LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE) {
                    invlist = add_cp_to_invlist(invlist, 'i');
                }
            }
        }
    }

    return invlist;
}
