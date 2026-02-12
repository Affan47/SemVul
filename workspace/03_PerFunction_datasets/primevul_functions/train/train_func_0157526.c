Perl__new_invlist(pTHX_ IV initial_size)
{


    SV* new_list;

    if (initial_size < 0) {
	initial_size = 10;
    }


    new_list = newSV_type(SVt_INVLIST);


    SvGROW(new_list, TO_INTERNAL_SIZE(initial_size + 1) + 1);
    invlist_set_len(new_list, 0, 0);


    *get_invlist_iter_addr(new_list) = (STRLEN) UV_MAX;

    *get_invlist_previous_index_addr(new_list) = 0;

    return new_list;
}
