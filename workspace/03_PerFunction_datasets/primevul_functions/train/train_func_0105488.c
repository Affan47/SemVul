SV*
Perl__new_invlist(pTHX_ IV initial_size)
{


    SV* new_list;

    if (initial_size < 0) {
	initial_size = 10;
    }

    new_list = newSV_type(SVt_INVLIST);
    initialize_invlist_guts(new_list, initial_size);

    return new_list;
}
