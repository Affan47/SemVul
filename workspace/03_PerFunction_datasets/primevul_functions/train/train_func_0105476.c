PERL_STATIC_INLINE UV*
S__invlist_array_init(SV* const invlist, const bool will_have_0)
{


    bool* offset = get_invlist_offset_addr(invlist);
    UV* zero_addr = (UV *) SvPVX(invlist);

    PERL_ARGS_ASSERT__INVLIST_ARRAY_INIT;


    assert(! _invlist_len(invlist));

    *zero_addr = 0;


    *offset = 1 ^ will_have_0;
    return zero_addr + *offset;
}
