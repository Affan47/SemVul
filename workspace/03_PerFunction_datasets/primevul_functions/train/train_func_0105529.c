STATIC bool
S_put_charclass_bitmap_innards(pTHX_ SV *sv,
                                     char *bitmap,
                                     SV *nonbitmap_invlist,
                                     SV *only_utf8_locale_invlist,
                                     const regnode * const node,
                                     const bool force_as_is_display)
{


    dVAR;
    bool inverting_allowed = ! force_as_is_display;

    int i;
    STRLEN orig_sv_cur = SvCUR(sv);

    SV* invlist;

    SV* only_utf8 = NULL;

    SV* not_utf8 =  NULL;

    SV* posixes = NULL;
    SV* only_utf8_locale = NULL;


    SV* as_is_display;

    SV* inverted_display;

    U8 flags = (node) ? ANYOF_FLAGS(node) : 0;

    bool invert = cBOOL(flags & ANYOF_INVERT);


    const int bias = 5;

    PERL_ARGS_ASSERT_PUT_CHARCLASS_BITMAP_INNARDS;


    if (nonbitmap_invlist) {
        assert(invlist_highest(nonbitmap_invlist) < NUM_ANYOF_CODE_POINTS);
        invlist = invlist_clone(nonbitmap_invlist, NULL);
    }
    else {
        invlist = _new_invlist(NUM_ANYOF_CODE_POINTS / 2);
    }

    if (flags) {
        if (OP(node) == ANYOFD) {


            if (flags & ANYOF_SHARED_d_UPPER_LATIN1_UTF8_STRING_MATCHES_non_d_RUNTIME_USER_PROP)
            {
                _invlist_intersection(invlist, PL_UpperLatin1, &only_utf8);
                _invlist_subtract(invlist, only_utf8, &invlist);
            }


            if (flags & ANYOF_SHARED_d_MATCHES_ALL_NON_UTF8_NON_ASCII_non_d_WARN_SUPER)
            {
                not_utf8 = invlist_clone(PL_UpperLatin1, NULL);
            }
        }
        else if (OP(node) == ANYOFL || OP(node) == ANYOFPOSIXL) {


            if (flags & (ANYOFL_FOLD|ANYOF_MATCHES_POSIXL)) {
                inverting_allowed = FALSE;
            }


            if (ANYOF_POSIXL_TEST_ANY_SET(node)) {
                int i;

                posixes = newSVpvs("");
                for (i = 0; i < ANYOF_POSIXL_MAX; i++) {
                    if (ANYOF_POSIXL_TEST(node, i)) {
                        sv_catpv(posixes, anyofs[i]);
                    }
                }
            }
        }
    }


    if (bitmap) {
        for (i = 0; i < NUM_ANYOF_CODE_POINTS; i++) {
            if (BITMAP_TEST(bitmap, i)) {
                int start = i++;
                for (;
                     i < NUM_ANYOF_CODE_POINTS && BITMAP_TEST(bitmap, i);
                     i++)
                {  }
                invlist = _add_range_to_invlist(invlist, start, i-1);
            }
        }
    }


    if (only_utf8) {
        _invlist_subtract(only_utf8, invlist, &only_utf8);
    }
    if (not_utf8) {
        _invlist_subtract(not_utf8, invlist, &not_utf8);
    }

    if (only_utf8_locale_invlist) {


        only_utf8_locale = invlist_clone(only_utf8_locale_invlist, NULL);

        _invlist_subtract(only_utf8_locale, invlist, &only_utf8_locale);


        if (invlist_highest(only_utf8_locale) >= NUM_ANYOF_CODE_POINTS) {
            inverting_allowed = FALSE;
        }
    }


    as_is_display = put_charclass_bitmap_innards_common(invlist,
                                                    posixes,
                                                    only_utf8,
                                                    not_utf8,
                                                    only_utf8_locale,
                                                    invert);


    if (! inverting_allowed) {
        if (as_is_display) {
            sv_catsv(sv, as_is_display);
            SvREFCNT_dec_NN(as_is_display);
        }
    }
    else {


        int inverted_bias, as_is_bias;


        if (invert) {
            invert = FALSE;
            as_is_bias = bias;
            inverted_bias = 0;
        }
        else {
            invert = TRUE;
            as_is_bias = 0;
            inverted_bias = bias;
        }


        _invlist_union(only_utf8, invlist, &invlist);
        _invlist_union(not_utf8, invlist, &invlist);
        _invlist_union(only_utf8_locale, invlist, &invlist);
        _invlist_invert(invlist);
        _invlist_intersection(invlist, PL_InBitmap, &invlist);

        if (only_utf8) {
            _invlist_invert(only_utf8);
            _invlist_intersection(only_utf8, PL_UpperLatin1, &only_utf8);
        }
        else if (not_utf8) {


            only_utf8 = not_utf8;
            not_utf8 = NULL;
        }

        if (only_utf8_locale) {
            _invlist_invert(only_utf8_locale);
            _invlist_intersection(only_utf8_locale,
                                  PL_InBitmap,
                                  &only_utf8_locale);
        }

        inverted_display = put_charclass_bitmap_innards_common(
                                            invlist,
                                            posixes,
                                            only_utf8,
                                            not_utf8,
                                            only_utf8_locale, invert);


        if (   inverted_display
            && (   ! as_is_display
                || (  SvCUR(inverted_display) + inverted_bias
                    < SvCUR(as_is_display)    + as_is_bias)))
        {
	    sv_catsv(sv, inverted_display);
        }
        else if (as_is_display) {
	    sv_catsv(sv, as_is_display);
        }

        SvREFCNT_dec(as_is_display);
        SvREFCNT_dec(inverted_display);
    }

    SvREFCNT_dec_NN(invlist);
    SvREFCNT_dec(only_utf8);
    SvREFCNT_dec(not_utf8);
    SvREFCNT_dec(posixes);
    SvREFCNT_dec(only_utf8_locale);

    return SvCUR(sv) > orig_sv_cur;
}
