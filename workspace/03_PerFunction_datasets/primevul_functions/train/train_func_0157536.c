S_get_ANYOF_cp_list_for_ssc(pTHX_ const RExC_state_t *pRExC_state,
                               const regnode_charclass* const node)
{


    SV* invlist = NULL;
    SV* only_utf8_locale_invlist = NULL;
    unsigned int i;
    const U32 n = ARG(node);
    bool new_node_has_latin1 = FALSE;

    PERL_ARGS_ASSERT_GET_ANYOF_CP_LIST_FOR_SSC;


    if (n != ANYOF_ONLY_HAS_BITMAP) {
        SV * const rv = MUTABLE_SV(RExC_rxi->data->data[n]);
        AV * const av = MUTABLE_AV(SvRV(rv));
        SV **const ary = AvARRAY(av);
        assert(RExC_rxi->data->what[n] == 's');

        if (ary[1] && ary[1] != &PL_sv_undef) {
            invlist = sv_2mortal(invlist_clone(_get_swash_invlist(ary[1])));
        }
        else if (ary[0] && ary[0] != &PL_sv_undef) {


            invlist = sv_2mortal(_new_invlist(1));
            return _add_range_to_invlist(invlist, 0, UV_MAX);
        }
        else if (ary[3] && ary[3] != &PL_sv_undef) {


            invlist = sv_2mortal(invlist_clone(ary[3]));
        }


        if ((ANYOF_FLAGS(node) & ANYOFL_FOLD)
            && ary[2] && ary[2] != &PL_sv_undef)
        {
            only_utf8_locale_invlist = ary[2];
        }
    }

    if (! invlist) {
        invlist = sv_2mortal(_new_invlist(0));
    }


    if (ANYOF_FLAGS(node) & ANYOF_INVERT) {
        _invlist_intersection_complement_2nd(invlist,
                                             PL_UpperLatin1,
                                             &invlist);
    }


    for (i = 0; i < NUM_ANYOF_CODE_POINTS; i++) {
        if (ANYOF_BITMAP_TEST(node, i)) {
            unsigned int start = i++;

            for (; i < NUM_ANYOF_CODE_POINTS && ANYOF_BITMAP_TEST(node, i); ++i) {

            }
            invlist = _add_range_to_invlist(invlist, start, i-1);
            new_node_has_latin1 = TRUE;
        }
    }


    if (! (ANYOF_FLAGS(node) & ANYOF_INVERT) && OP(node) == ANYOFD
        && (ANYOF_FLAGS(node) & ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER))
    {
        _invlist_union(invlist, PL_UpperLatin1, &invlist);
    }


    if (ANYOF_FLAGS(node) & ANYOF_MATCHES_ALL_ABOVE_BITMAP) {
        _invlist_union_complement_2nd(invlist, PL_InBitmap, &invlist);
    }

    if (ANYOF_FLAGS(node) & ANYOF_INVERT) {
        _invlist_invert(invlist);
    }
    else if (new_node_has_latin1 && ANYOF_FLAGS(node) & ANYOFL_FOLD) {


        _invlist_union(invlist, PL_Latin1, &invlist);
    }


    if (only_utf8_locale_invlist) {
        _invlist_union_maybe_complement_2nd(invlist,
                                            only_utf8_locale_invlist,
                                            ANYOF_FLAGS(node) & ANYOF_INVERT,
                                            &invlist);
    }

    return invlist;
}
