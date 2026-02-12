STATIC SV*
S_get_ANYOFM_contents(pTHX_ const regnode * n) {


    SV * cp_list = _new_invlist(-1);
    const U8 lowest = (U8) ARG(n);
    unsigned int i;
    U8 count = 0;
    U8 needed = 1U << PL_bitcount[ (U8) ~ FLAGS(n)];

    PERL_ARGS_ASSERT_GET_ANYOFM_CONTENTS;


    for (i = lowest; i <= 0xFF; i++) {
        if ((i & FLAGS(n)) == ARG(n)) {
            cp_list = add_cp_to_invlist(cp_list, i);
            count++;


            if (count >= needed) break;
        }
    }

    if (OP(n) == NANYOFM) {
        _invlist_invert(cp_list);
    }
    return cp_list;
}
