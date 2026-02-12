PERL_STATIC_INLINE void
S_invlist_iterinit(SV* invlist)
{
    PERL_ARGS_ASSERT_INVLIST_ITERINIT;

    *get_invlist_iter_addr(invlist) = 0;
}
