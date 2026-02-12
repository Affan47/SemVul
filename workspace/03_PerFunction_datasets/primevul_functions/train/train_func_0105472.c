STATIC SV*
S_get_ANYOF_cp_list_for_ssc(pTHX_ const RExC_state_t *pRExC_state,
                               const regnode_charclass* const node)
{


    dVAR;
    SV* invlist = NULL;
    SV* only_utf8_locale_invlist = NULL;
    unsigned int i;
    const U32 n = ARG(node);
    bool new_node_has_latin1 = FALSE;
    const U8 flags = OP(node) == ANYOFH ? 0 : ANYOF_FLAGS(node);

    PERL_ARGS_ASSERT_GET_ANYOF_CP_LIST_FOR_SSC;


    if (n != ANYOF_ONLY_HAS_BITMAP) {
        SV * const rv = MUTABLE_SV(RExC_rxi->data->data[n]);
        AV * const av = MUTABLE_AV(SvRV(rv));
        SV **const ary = AvARRAY(av);
        assert(RExC_rxi->data->what[n] == 's');

        if (av_tindex_skip_len_mg(av) >= DEFERRED_USER_DEFINED_INDEX) {


            invlist = sv_2mortal(_new_invlist(1));
            return _add_range_to_invlist(invlist, 0, UV_MAX);
        }
        else if (ary[INVLIST_INDEX]) {


            invlist = sv_2mortal(invlist_clone(ary[INVLIST_INDEX], NULL));
        }


        if (   (flags & ANYOFL_FOLD)
            &&  av_tindex_skip_len_mg(av) >= ONLY_LOCALE_MATCHES_INDEX)
        {
            only_utf8_locale_invlist = ary[ONLY_LOCALE_MATCHES_INDEX];
        }
    }

    if (! invlist) {
        invlist = sv_2mortal(_new_invlist(0));
    }


    if (flags & ANYOF_INVERT) {
        _invlist_intersection_complement_2nd(invlist,
                                             PL_UpperLatin1,
                                             &invlist);
    }


    if (OP(node) != ANYOFH) {
        for (i = 0; i < NUM_ANYOF_CODE_POINTS; i++) {
            if (ANYOF_BITMAP_TEST(node, i)) {
                unsigned int start = i++;

                for (;    i < NUM_ANYOF_CODE_POINTS
                       && ANYOF_BITMAP_TEST(node, i); ++i)
                {

                }
                invlist = _add_range_to_invlist(invlist, start, i-1);
                new_node_has_latin1 = TRUE;
            }
        }
    }


    if (! (flags & ANYOF_INVERT) && OP(node) == ANYOFD
        && (flags & ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER))
    {
        _invlist_union(invlist, PL_UpperLatin1, &invlist);
    }


    if (flags & ANYOF_MATCHES_ALL_ABOVE_BITMAP) {
        _invlist_union_complement_2nd(invlist, PL_InBitmap, &invlist);
    }

    if (flags & ANYOF_INVERT) {
        _invlist_invert(invlist);
    }
    else if (flags & ANYOFL_FOLD) {
        if (new_node_has_latin1) {


            _invlist_union(invlist, PL_Latin1, &invlist);

            invlist = add_cp_to_invlist(invlist, LATIN_SMALL_LETTER_DOTLESS_I);
            invlist = add_cp_to_invlist(invlist, LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE);
        }
        else {
            if (_invlist_contains_cp(invlist, LATIN_SMALL_LETTER_DOTLESS_I)) {
                invlist = add_cp_to_invlist(invlist, 'I');
            }
            if (_invlist_contains_cp(invlist,
                                        LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE))
            {
                invlist = add_cp_to_invlist(invlist, 'i');
            }
        }
    }


    if (only_utf8_locale_invlist) {
        _invlist_union_maybe_complement_2nd(invlist,
                                            only_utf8_locale_invlist,
                                            flags & ANYOF_INVERT,
                                            &invlist);
    }

    return invlist;
}
