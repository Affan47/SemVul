S_setup_longest(pTHX_ RExC_state_t *pRExC_state,
                      struct reg_substr_datum  *rsd,
                      struct scan_data_substrs *sub,
                      STRLEN longest_length)
{


    I32 t;
    SSize_t ml;
    bool eol  = cBOOL(sub->flags & SF_BEFORE_EOL);
    bool meol = cBOOL(sub->flags & SF_BEFORE_MEOL);

    if (! (longest_length
           || (eol
               && (! meol || (RExC_flags & RXf_PMf_MULTILINE)))
          )

        || (RExC_seen & REG_UNFOLDED_MULTI_SEEN))
    {
        return FALSE;
    }


    if (SvUTF8(sub->str)) {
        rsd->substr      = NULL;
        rsd->utf8_substr = sub->str;
    } else {
        rsd->substr      = sub->str;
        rsd->utf8_substr = NULL;
    }


    ml = sub->minlenp ? *(sub->minlenp) : (SSize_t)longest_length;
    rsd->end_shift = ml - sub->min_offset
        - longest_length


        + sub->lookbehind;

    t = (eol
         && (! meol || (RExC_flags & RXf_PMf_MULTILINE)));
    fbm_compile(sub->str, t ? FBMcf_TAIL : 0);

    return TRUE;
}
