S__make_exactf_invlist(pTHX_ RExC_state_t *pRExC_state, regnode *node)
{
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
            }
            else {


                invlist = add_cp_to_invlist(invlist, uc);
                if (IS_IN_SOME_FOLD_L1(uc))
                    invlist = add_cp_to_invlist(invlist, PL_fold_latin1[uc]);
            }


            if (HAS_NONLATIN1_SIMPLE_FOLD_CLOSURE(uc)
                && (! isASCII(uc) || (OP(node) != EXACTFA
                                    && OP(node) != EXACTFA_NO_TRIE)))
            {
                add_above_Latin1_folds(pRExC_state, (U8) uc, &invlist);
            }
        }
    }
    else {
        U8 folded[UTF8_MAX_FOLD_CHAR_EXPAND * UTF8_MAXBYTES_CASE + 1] = { '\0' };
        STRLEN foldlen = UTF8SKIP(s);
        const U8* e = s + bytelen;
        SV** listp;

        uc = utf8_to_uvchr_buf(s, s + bytelen, NULL);


        if (OP(node) == EXACTFL && is_PROBLEMATIC_LOCALE_FOLDEDS_START_cp(uc)) {


            U8 *d = folded;
            int i;

            for (i = 0; i < UTF8_MAX_FOLD_CHAR_EXPAND && s < e; i++) {
                if (isASCII(*s)) {
                    *(d++) = (U8) toFOLD(*s);
                    s++;
                }
                else {
                    STRLEN len;
                    toFOLD_utf8_safe(s, e, d, &len);
                    d += len;
                    s += UTF8SKIP(s);
                }
            }


            e = d;
            foldlen = UTF8SKIP(folded);
            s = folded;
        }


        if (is_MULTI_CHAR_FOLD_utf8_safe(s, e)) {
            invlist = _add_range_to_invlist(invlist, 0, UV_MAX);
        }
        else {


            invlist = add_cp_to_invlist(invlist, uc);
            if (! PL_utf8_foldclosures)
                _load_PL_utf8_foldclosures();
            if ((listp = hv_fetch(PL_utf8_foldclosures,
                                (char *) s, foldlen, FALSE)))
            {
                AV* list = (AV*) *listp;
                IV k;
                for (k = 0; k <= av_tindex_skip_len_mg(list); k++) {
                    SV** c_p = av_fetch(list, k, FALSE);
                    UV c;
                    assert(c_p);

                    c = SvUV(*c_p);


                    if ((OP(node) == EXACTFA || OP(node) == EXACTFA_NO_TRIE)
                        && isASCII(c) != isASCII(uc))
                    {
                        continue;
                    }

                    invlist = add_cp_to_invlist(invlist, c);
                }
            }
        }
    }

    return invlist;
}
