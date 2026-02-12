STATIC void
S_initialize_invlist_guts(pTHX_ SV* invlist, const Size_t initial_size)
{
    PERL_ARGS_ASSERT_INITIALIZE_INVLIST_GUTS;


    SvGROW(invlist, TO_INTERNAL_SIZE(initial_size + 1) + 1);
    invlist_set_len(invlist, 0, 0);


    invlist_iterfinish(invlist);

    *get_invlist_previous_index_addr(invlist) = 0;
}
