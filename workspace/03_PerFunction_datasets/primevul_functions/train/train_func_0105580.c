PERL_STATIC_INLINE void
S_invlist_iterfinish(SV* invlist)
{


    PERL_ARGS_ASSERT_INVLIST_ITERFINISH;

    *get_invlist_iter_addr(invlist) = (STRLEN) UV_MAX;
}
