PERL_STATIC_INLINE STRLEN*
S_get_invlist_iter_addr(SV* invlist)
{


    PERL_ARGS_ASSERT_GET_INVLIST_ITER_ADDR;

    assert(is_invlist(invlist));

    return &(((XINVLIST*) SvANY(invlist))->iterator);
}
