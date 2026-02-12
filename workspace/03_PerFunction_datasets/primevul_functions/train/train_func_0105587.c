STATIC void
S_set_ANYOF_arg(pTHX_ RExC_state_t* const pRExC_state,
                regnode* const node,
                SV* const cp_list,
                SV* const runtime_defns,
                SV* const only_utf8_locale_list)
{


    UV n;

    PERL_ARGS_ASSERT_SET_ANYOF_ARG;

    if (! cp_list && ! runtime_defns && ! only_utf8_locale_list) {
        assert(! (ANYOF_FLAGS(node)
                & ANYOF_SHARED_d_UPPER_LATIN1_UTF8_STRING_MATCHES_non_d_RUNTIME_USER_PROP));
	ARG_SET(node, ANYOF_ONLY_HAS_BITMAP);
    }
    else {
	AV * const av = newAV();
	SV *rv;

        if (cp_list) {
            av_store(av, INVLIST_INDEX, cp_list);
        }

        if (only_utf8_locale_list) {
            av_store(av, ONLY_LOCALE_MATCHES_INDEX, only_utf8_locale_list);
        }

        if (runtime_defns) {
            av_store(av, DEFERRED_USER_DEFINED_INDEX, SvREFCNT_inc(runtime_defns));
        }

	rv = newRV_noinc(MUTABLE_SV(av));
	n = add_data(pRExC_state, STR_WITH_LEN("s"));
	RExC_rxi->data->data[n] = (void*)rv;
	ARG_SET(node, n);
    }
}
