STATIC void
S__append_range_to_invlist(pTHX_ SV* const invlist,
                                 const UV start, const UV end)
{


    UV* array;
    UV max = invlist_max(invlist);
    UV len = _invlist_len(invlist);
    bool offset;

    PERL_ARGS_ASSERT__APPEND_RANGE_TO_INVLIST;

    if (len == 0) {
        offset = start != 0;
        array = _invlist_array_init(invlist, ! offset);
    }
    else {


	UV final_element = len - 1;
	array = invlist_array(invlist);
	if (   array[final_element] > start
	    || ELEMENT_RANGE_MATCHES_INVLIST(final_element))
	{
	    Perl_croak(aTHX_ "panic: attempting to append to an inversion list, but wasn't at the end of the list, final=%" UVuf ", start=%" UVuf ", match=%c",
		     array[final_element], start,
		     ELEMENT_RANGE_MATCHES_INVLIST(final_element) ? 't' : 'f');
	}


        offset = *get_invlist_offset_addr(invlist);
	if (array[final_element] == start) {
	    if (end != UV_MAX) {
		array[final_element] = end + 1;
	    }
	    else {


		invlist_set_len(invlist, len - 1, offset);
	    }
	    return;
	}
    }


    len += 2;


    if (max < len) {
	invlist_extend(invlist, len);


        invlist_set_len(invlist, len, offset);

	array = invlist_array(invlist);
    }
    else {
	invlist_set_len(invlist, len, offset);
    }


    array[len - 2] = start;
    if (end != UV_MAX) {
	array[len - 1] = end + 1;
    }
    else {


	invlist_set_len(invlist, len - 1, offset);
    }
}
