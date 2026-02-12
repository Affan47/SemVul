PERL_STATIC_INLINE void
S_invlist_trim(SV* invlist)
{


    const UV min_size = TO_INTERNAL_SIZE(1) + 1;

    PERL_ARGS_ASSERT_INVLIST_TRIM;

    assert(is_invlist(invlist));

    SvPV_renew(invlist, MAX(min_size, SvCUR(invlist) + 1));
}
