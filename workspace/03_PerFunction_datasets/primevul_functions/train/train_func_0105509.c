STATIC void
S_invlist_extend(pTHX_ SV* const invlist, const UV new_max)
{


    PERL_ARGS_ASSERT_INVLIST_EXTEND;

    assert(is_invlist(invlist));


    SvGROW((SV *)invlist, TO_INTERNAL_SIZE(new_max + 1));
}
