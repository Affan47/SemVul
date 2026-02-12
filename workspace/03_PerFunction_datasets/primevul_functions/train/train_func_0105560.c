STATIC bool
S_is_ssc_worth_it(const RExC_state_t * pRExC_state, const regnode_ssc * ssc)
{


    U32 count = 0;

    UV start, end;

    const U32 max_code_points = (LOC)
                                ?  256
                                : ((  ! UNI_SEMANTICS
                                    ||  invlist_highest(ssc->invlist) < 256)
                                  ? 128
                                  : NON_OTHER_COUNT);
    const U32 max_match = max_code_points / 2;

    PERL_ARGS_ASSERT_IS_SSC_WORTH_IT;

    invlist_iterinit(ssc->invlist);
    while (invlist_iternext(ssc->invlist, &start, &end)) {
        if (start >= max_code_points) {
            break;
        }
        end = MIN(end, max_code_points - 1);
        count += end - start + 1;
        if (count >= max_match) {
            invlist_iterfinish(ssc->invlist);
            return FALSE;
        }
    }

    return TRUE;
}
