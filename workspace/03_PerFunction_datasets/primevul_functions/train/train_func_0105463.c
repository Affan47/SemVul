PERL_STATIC_INLINE UV
S_invlist_max(SV* const invlist)
{


    PERL_ARGS_ASSERT_INVLIST_MAX;

    assert(is_invlist(invlist));


    return SvLEN(invlist) == 0
           ? FROM_INTERNAL_SIZE(SvCUR(invlist)) - 1
           : FROM_INTERNAL_SIZE(SvLEN(invlist)) - 1;
}
