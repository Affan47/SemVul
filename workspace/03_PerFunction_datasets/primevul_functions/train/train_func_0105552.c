SV *
Perl__get_regclass_nonbitmap_data(pTHX_ const regexp *prog,
                                        const regnode* node,
                                        bool doinit,
                                        SV** listsvp,
                                        SV** only_utf8_locale_ptr,
                                        SV** output_invlist)

{


    SV *si  = NULL;
    SV* invlist = NULL;

    RXi_GET_DECL(prog, progi);
    const struct reg_data * const data = prog ? progi->data : NULL;

    PERL_ARGS_ASSERT__GET_REGCLASS_NONBITMAP_DATA;
    assert(! output_invlist || listsvp);

    if (data && data->count) {
	const U32 n = ARG(node);

	if (data->what[n] == 's') {
	    SV * const rv = MUTABLE_SV(data->data[n]);
	    AV * const av = MUTABLE_AV(SvRV(rv));
	    SV **const ary = AvARRAY(av);

            invlist = ary[INVLIST_INDEX];

            if (av_tindex_skip_len_mg(av) >= ONLY_LOCALE_MATCHES_INDEX) {
                *only_utf8_locale_ptr = ary[ONLY_LOCALE_MATCHES_INDEX];
            }

            if (av_tindex_skip_len_mg(av) >= DEFERRED_USER_DEFINED_INDEX) {
                si = ary[DEFERRED_USER_DEFINED_INDEX];
            }

	    if (doinit && (si || invlist)) {
                if (si) {
                    bool user_defined;
                    SV * msg = newSVpvs_flags("", SVs_TEMP);

                    SV * prop_definition = handle_user_defined_property(
                            "", 0, FALSE,
                            SvPVX_const(si)[1] - '0',


                            TRUE,
                            FALSE,
                            si,
                            &user_defined,
                            msg,
                            0
                           );

                    if (SvCUR(msg)) {
                        assert(prop_definition == NULL);

                        Perl_croak(aTHX_ "%" UTF8f,
                                UTF8fARG(SvUTF8(msg), SvCUR(msg), SvPVX(msg)));
                    }

                    if (invlist) {
                        _invlist_union(invlist, prop_definition, &invlist);
                        SvREFCNT_dec_NN(prop_definition);
                    }
                    else {
                        invlist = prop_definition;
                    }

                    STATIC_ASSERT_STMT(ONLY_LOCALE_MATCHES_INDEX == 1 + INVLIST_INDEX);
                    STATIC_ASSERT_STMT(DEFERRED_USER_DEFINED_INDEX == 1 + ONLY_LOCALE_MATCHES_INDEX);

                    av_store(av, INVLIST_INDEX, invlist);
                    av_fill(av, (ary[ONLY_LOCALE_MATCHES_INDEX])
                                 ? ONLY_LOCALE_MATCHES_INDEX:
                                 INVLIST_INDEX);
                    si = NULL;
                }
	    }
	}
    }


    if (listsvp) {
	SV* matches_string = NULL;


	if (si) {


            if (! output_invlist) {
                matches_string = newSVsv(si);
            }
            else {


                const char *si_string = SvPVX(si);
                STRLEN remaining = SvCUR(si);
                UV prev_cp = 0;
                U8 count = 0;


                while (*si_string != '\n' && remaining > 0) {
                    si_string++;
                    remaining--;
                }
                assert(remaining > 0);

                si_string++;
                remaining--;

                while (remaining > 0) {


                    I32 grok_flags =  PERL_SCAN_SILENT_ILLDIGIT
                                     |PERL_SCAN_SILENT_NON_PORTABLE;
                    STRLEN len = remaining;
                    UV cp = grok_hex(si_string, &len, &grok_flags, NULL);


                    if (   *(si_string + len) == '\n') {
                        if (count) {
                            *output_invlist = _add_range_to_invlist(*output_invlist, prev_cp, cp);
                        }
                        else {
                            *output_invlist = add_cp_to_invlist(*output_invlist, cp);
                        }
                        count = 0;
                        goto prepare_for_next_iteration;
                    }


                    if (*(si_string + len) == '\t') {
                        assert(count == 0);

                        prev_cp = cp;
                        count = 1;
                      prepare_for_next_iteration:
                        si_string += len + 1;
                        remaining -= len + 1;
                        continue;
                    }


                    remaining -= len;
                    while (*(si_string + len) != '\n' && remaining > 0) {
                        remaining--;
                        len++;
                    }
                    if (*(si_string + len) == '\n') {
                        len++;
                        remaining--;
                    }
                    if (matches_string) {
                        sv_catpvn(matches_string, si_string, len - 1);
                    }
                    else {
                        matches_string = newSVpvn(si_string, len - 1);
                    }
                    si_string += len;
                    sv_catpvs(matches_string, " ");
                }

                assert(matches_string);
                if (SvCUR(matches_string)) {
                    SvCUR_set(matches_string, SvCUR(matches_string) - 1);
                }
            }
	}


        if (invlist) {


            if (! output_invlist) {
                if ( ! matches_string) {
                    matches_string = newSVpvs("\n");
                }
                sv_catsv(matches_string, invlist_contents(invlist,
                                                  TRUE
                                                  ));
            }
            else if (! *output_invlist) {
                *output_invlist = invlist_clone(invlist, NULL);
            }
            else {
                _invlist_union(*output_invlist, invlist, output_invlist);
            }
        }

	*listsvp = matches_string;
    }

    return invlist;
}
