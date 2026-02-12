Perl__add_range_to_invlist(pTHX_ SV* invlist, UV start, UV end)
{


    UV* array;
    UV len;
    SSize_t i_s;

    SSize_t i_e = 0;
    UV cur_highest;


    if (invlist == NULL) {
	invlist = _new_invlist(2);
        _append_range_to_invlist(invlist, start, end);
        return invlist;
    }


    len = _invlist_len(invlist);
    if (len == 0) {
        _append_range_to_invlist(invlist, start, end);
        return invlist;
    }


    array = invlist_array(invlist);


    cur_highest = invlist_highest(invlist);
    if (end > cur_highest) {


        if (start > cur_highest) {
            _append_range_to_invlist(invlist, start, end);
            return invlist;
        }


        _append_range_to_invlist(invlist, cur_highest + 1, end);


        if (end == UV_MAX) {
            i_e = len;
        }
        else {
            i_e = len - 2;
        }
    }


    if (start < array[0]) {


        if (UNLIKELY(start == 0)) {
            SV* range_invlist;

            range_invlist = _new_invlist(2);
            _append_range_to_invlist(range_invlist, start, end);

            _invlist_union(invlist, range_invlist, &invlist);

            SvREFCNT_dec_NN(range_invlist);

            return invlist;
        }


        if (end < array[0] - 1) {
            i_s = i_e = -1;
            goto splice_in_new_range;
        }


        array[0] = start;


        i_s = 0;
    }
    else {


        i_s = _invlist_search(invlist, start);
    }


    if (i_e == 0) {
        i_e = (start == end)
              ? i_s
              : _invlist_search(invlist, end);
    }


    if ( ! ELEMENT_RANGE_MATCHES_INVLIST(i_s)) {


        const bool extends_the_range_above = (   end == UV_MAX
                                              || end + 1 >= array[i_s+1]);


        if (start == array[i_s]) {


            if (i_e - i_s <= 1) {


                if (extends_the_range_above) {
                    Move(array + i_s + 2, array + i_s, len - i_s - 2, UV);
                    invlist_set_len(invlist,
                                    len - 2,
                                    *(get_invlist_offset_addr(invlist)));
                    return invlist;
                }


                i_e--;
            }


            array[i_s] = (end == UV_MAX) ? UV_MAX : end + 1;
            i_s--;
            start = array[i_s];
        }
        else if (extends_the_range_above) {


            if (i_e == i_s) {
                i_e++;
            }
            i_s++;
            array[i_s] = start;
        }
    }


    if (UNLIKELY(end == UV_MAX)) {
        invlist_set_len(invlist, i_s + 1, *(get_invlist_offset_addr(invlist)));
        return invlist;
    }


    if (! ELEMENT_RANGE_MATCHES_INVLIST(i_e)) {


        if (end + 1 == array[i_e+1]) {
            i_e++;
            array[i_e] = start;
        }
        else if (start <= array[i_e]) {
            array[i_e] = end + 1;
            i_e--;
        }
    }

    if (i_s == i_e) {


        if (ELEMENT_RANGE_MATCHES_INVLIST(i_s)) {
            return invlist;
        }


      splice_in_new_range:

        invlist_extend(invlist, len + 2);
        array = invlist_array(invlist);


        Move(array + i_e + 1, array + i_e + 3, len - i_e - 1, UV);


        array[i_e+1] = start;
        array[i_e+2] = end + 1;
        invlist_set_len(invlist, len + 2, *(get_invlist_offset_addr(invlist)));
        return invlist;
    }


    Move(array + i_e + 1, array + i_s + 1, len - i_e - 1, UV);
    invlist_set_len(invlist,
                    len - i_e + i_s,
                    *(get_invlist_offset_addr(invlist)));

    return invlist;
}
