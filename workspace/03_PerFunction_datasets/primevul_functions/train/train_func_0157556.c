S_invlist_replace_list_destroys_src(pTHX_ SV * dest, SV * src)
{


    const UV src_len          = _invlist_len(src);
    const bool src_offset     = *get_invlist_offset_addr(src);
    const STRLEN src_byte_len = SvLEN(src);
    char * array              = SvPVX(src);

    const int oldtainted = TAINT_get;

    PERL_ARGS_ASSERT_INVLIST_REPLACE_LIST_DESTROYS_SRC;

    assert(SvTYPE(src) == SVt_INVLIST);
    assert(SvTYPE(dest) == SVt_INVLIST);
    assert(! invlist_is_iterating(src));
    assert(SvCUR(src) == 0 || SvCUR(src) < SvLEN(src));


    array[src_byte_len - 1] = '\0';

    TAINT_NOT;
    sv_usepvn_flags(dest,
                    (char *) array,
                    src_byte_len - 1,


                    SV_HAS_TRAILING_NUL);
    TAINT_set(oldtainted);
    SvPV_set(src, 0);
    SvLEN_set(src, 0);
    SvCUR_set(src, 0);


    *get_invlist_offset_addr(dest) = src_offset;
    invlist_set_len(dest, src_len, src_offset);
    *get_invlist_previous_index_addr(dest) = 0;
    invlist_iterfinish(dest);
}
