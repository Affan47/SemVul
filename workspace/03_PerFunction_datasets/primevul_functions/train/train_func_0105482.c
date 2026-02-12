void
Perl__invlist_union_maybe_complement_2nd(pTHX_ SV* const a, SV* const b,
                                         const bool complement_b, SV** output)
{


    const UV* array_a;
    const UV* array_b;
    UV len_a;
    UV len_b;

    SV* u;
    UV* array_u;
    UV len_u = 0;

    UV i_a = 0;
    UV i_b = 0;
    UV i_u = 0;


    UV count = 0;

    PERL_ARGS_ASSERT__INVLIST_UNION_MAYBE_COMPLEMENT_2ND;
    assert(a != b);
    assert(*output == NULL || is_invlist(*output));

    len_b = _invlist_len(b);
    if (len_b == 0) {


        if (complement_b) {
            SV* everything = _add_range_to_invlist(NULL, 0, UV_MAX);

            if (*output == NULL) {

                *output = everything;
            }
            else {
                invlist_replace_list_destroys_src(*output, everything);
                SvREFCNT_dec_NN(everything);
            }

            return;
        }


        if (a == NULL || _invlist_len(a) == 0) {
            if (*output == NULL) {
                *output = _new_invlist(0);
            }
            else {
                invlist_clear(*output);
            }
            return;
        }


        if (*output == NULL) {
            *output = invlist_clone(a, NULL);
            return;
        }


        if (*output == a) {
            return;
        }


        u = invlist_clone(a, NULL);
        invlist_replace_list_destroys_src(*output, u);
        SvREFCNT_dec_NN(u);

        return;
    }


    if (a == NULL || ((len_a = _invlist_len(a)) == 0)) {


        SV ** dest = (*output == NULL) ? output : &u;
        *dest = invlist_clone(b, NULL);
        if (complement_b) {
            _invlist_invert(*dest);
        }

        if (dest == &u) {
            invlist_replace_list_destroys_src(*output, u);
            SvREFCNT_dec_NN(u);
        }

	return;
    }


    array_a = invlist_array(a);
    array_b = invlist_array(b);


    if (complement_b) {


        if (array_b[0] == 0) {
            array_b++;
            len_b--;
        }
        else {


            array_b--;
            len_b++;
        }
    }


    u = _new_invlist(len_a + len_b);


    array_u = _invlist_array_init(u, (    len_a > 0 && array_a[0] == 0)
                                      || (len_b > 0 && array_b[0] == 0));


    while (i_a < len_a && i_b < len_b) {
	UV cp;
	bool cp_in_set;


	if (       array_a[i_a] < array_b[i_b]
	    || (   array_a[i_a] == array_b[i_b]
		&& ELEMENT_RANGE_MATCHES_INVLIST(i_a)))
	{
	    cp_in_set = ELEMENT_RANGE_MATCHES_INVLIST(i_a);
	    cp = array_a[i_a++];
	}
	else {
	    cp_in_set = ELEMENT_RANGE_MATCHES_INVLIST(i_b);
	    cp = array_b[i_b++];
	}


	if (cp_in_set) {
	    if (count == 0) {
		array_u[i_u++] = cp;
	    }
	    count++;
	}
	else {
	    count--;
	    if (count == 0) {
		array_u[i_u++] = cp;
	    }
	}
    }


    if (   (i_a != len_a && PREV_RANGE_MATCHES_INVLIST(i_a))
	|| (i_b != len_b && PREV_RANGE_MATCHES_INVLIST(i_b)))
    {
	count--;
    }


    if (count != 0) {
        len_u = i_u;
    }
    else {
        IV copy_count = len_a - i_a;
        if (copy_count > 0) {
	    Copy(array_a + i_a, array_u + i_u, copy_count, UV);
        }
        else {
            copy_count = len_b - i_b;
	    Copy(array_b + i_b, array_u + i_u, copy_count, UV);
        }
        len_u = i_u + copy_count;
    }


    if (len_u != _invlist_len(u)) {
	invlist_set_len(u, len_u, *get_invlist_offset_addr(u));
	invlist_trim(u);
	array_u = invlist_array(u);
    }

    if (*output == NULL) {
        *output = u;
    }
    else {


        invlist_replace_list_destroys_src(*output, u);
        SvREFCNT_dec_NN(u);
    }

    return;
}
