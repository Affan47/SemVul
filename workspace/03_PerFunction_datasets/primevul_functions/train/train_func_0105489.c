STATIC void
S_set_regex_pv(pTHX_ RExC_state_t *pRExC_state, REGEXP *Rx)
{


    bool has_p     = ((RExC_rx->extflags & RXf_PMf_KEEPCOPY) == RXf_PMf_KEEPCOPY);
    bool has_charset = RExC_utf8 || (get_regex_charset(RExC_rx->extflags)
                                                != REGEX_DEPENDS_CHARSET);


    bool has_default =
                (((RExC_rx->extflags & RXf_PMf_STD_PMMOD) != RXf_PMf_STD_PMMOD)
                || ! has_charset);
    bool has_runon = ((RExC_seen & REG_RUN_ON_COMMENT_SEEN)
                                                == REG_RUN_ON_COMMENT_SEEN);
    U8 reganch = (U8)((RExC_rx->extflags & RXf_PMf_STD_PMMOD)
                        >> RXf_PMf_STD_PMMOD_SHIFT);
    const char *fptr = STD_PAT_MODS;
    char *p;
    STRLEN pat_len = RExC_precomp_end - RExC_precomp;


    const STRLEN wraplen = pat_len + has_p + has_runon
        + has_default
        + PL_bitcount[reganch]


        + ((has_charset) ? MAX_CHARSET_NAME_LENGTH : 0)
        + (sizeof("(?:)") - 1);

    PERL_ARGS_ASSERT_SET_REGEX_PV;


    assert(sizeof(STD_PAT_MODS) <= 8);

    p = sv_grow(MUTABLE_SV(Rx), wraplen + 1);
    SvPOK_on(Rx);
    if (RExC_utf8)
        SvFLAGS(Rx) |= SVf_UTF8;
    *p++='('; *p++='?';


    if (has_default) {
        *p++= DEFAULT_PAT_MOD;
    }
    if (has_charset) {
        STRLEN len;
        const char* name;

        name = get_regex_charset_name(RExC_rx->extflags, &len);
        if strEQ(name, DEPENDS_PAT_MODS) {
            assert(RExC_utf8);
            name = UNICODE_PAT_MODS;
            len = sizeof(UNICODE_PAT_MODS) - 1;
        }
        Copy(name, p, len, char);
        p += len;
    }
    if (has_p)
        *p++ = KEEPCOPY_PAT_MOD;
    {
        char ch;
        while((ch = *fptr++)) {
            if(reganch & 1)
                *p++ = ch;
            reganch >>= 1;
        }
    }

    *p++ = ':';
    Copy(RExC_precomp, p, pat_len, char);
    assert ((RX_WRAPPED(Rx) - p) < 16);
    RExC_rx->pre_prefix = p - RX_WRAPPED(Rx);
    p += pat_len;


    if (has_runon)
        *p++ = '\n';
    *p++ = ')';
    *p = 0;
    SvCUR_set(Rx, p - RX_WRAPPED(Rx));
}
