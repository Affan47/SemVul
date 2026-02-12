S_invlist_max(SV* const invlist)
{


    PERL_ARGS_ASSERT_INVLIST_MAX;

    assert(SvTYPE(invlist) == SVt_INVLIST);


    return SvLEN(invlist) == 0
           ? FROM_INTERNAL_SIZE(SvCUR(invlist)) - 1
           : FROM_INTERNAL_SIZE(SvLEN(invlist)) - 1;
}
