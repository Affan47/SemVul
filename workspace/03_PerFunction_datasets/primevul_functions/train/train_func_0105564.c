SV*
Perl__new_invlist_C_array(pTHX_ const UV* const list)
{


    const STRLEN length = (STRLEN) list[0];
    const UV version_id =          list[1];
    const bool offset   =    cBOOL(list[2]);
#define HEADER_LENGTH 3


#define INVLIST_VERSION_ID 148565664


    SV* invlist = newSV_type(SVt_INVLIST);

    PERL_ARGS_ASSERT__NEW_INVLIST_C_ARRAY;

    if (version_id != INVLIST_VERSION_ID) {
        Perl_croak(aTHX_ "panic: Incorrect version for previously generated inversion list");
    }


    SvPV_set(invlist, (char *) (list + HEADER_LENGTH));

    SvLEN_set(invlist, 0);


    *(get_invlist_offset_addr(invlist)) = offset;


    invlist_set_len(invlist, length  - offset, offset);

    invlist_set_previous_index(invlist, 0);


    invlist_iterfinish(invlist);

    SvREADONLY_on(invlist);

    return invlist;
}
