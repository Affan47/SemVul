void
Perl__invlist_intersection_maybe_complement_2nd(pTHX_ SV* const a, SV* const b,
                                               const bool complement_b, SV** i)
{


    const UV* array_a;
    const UV* array_b;
    UV len_a;
    UV len_b;

    SV* r;
    UV* array_r;
    UV len_r = 0;

    UV i_a = 0;
    UV i_b = 0;
    UV i_r = 0;


    UV count = 0;

    PERL_ARGS_ASSERT__INVLIST_INTERSECTION_MAYBE_COMPLEMENT_2ND;
    assert(a != b);
    assert(*i == NULL || is_invlist(*i));


    len_a = (a == NULL) ? 0 : _invlist_len(a);
    if ((len_a == 0) || ((len_b = _invlist_len(b)) == 0)) {
        if (len_a != 0 && complement_b) {


            if (*i == a) {
                return;
            }

            if (*i == NULL) {
                *i = invlist_clone(a, NULL);
                return;
            }

            r = invlist_clone(a, NULL);
            invlist_replace_list_destroys_src(*i, r);
            SvREFCNT_dec_NN(r);
            return;
        }


        if (*i == NULL) {
            *i = _new_invlist(0);
            return;
        }

        invlist_clear(*i);
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


    r= _new_invlist(len_a + len_b);


    array_r = _invlist_array_init(r,    len_a > 0 && array_a[0] == 0
                                     && len_b > 0 && array_b[0] == 0);


    while (i_a < len_a && i_b < len_b) {
	UV cp;

	bool cp_in_set;


	if (       array_a[i_a] < array_b[i_b]
	    || (   array_a[i_a] == array_b[i_b]
		&& ! ELEMENT_RANGE_MATCHES_INVLIST(i_a)))
	{
	    cp_in_set = ELEMENT_RANGE_MATCHES_INVLIST(i_a);
	    cp = array_a[i_a++];
	}
	else {
	    cp_in_set = ELEMENT_RANGE_MATCHES_INVLIST(i_b);
	    cp= array_b[i_b++];
	}


	if (cp_in_set) {
	    count++;
	    if (count == 2) {
		array_r[i_r++] = cp;
	    }
	}
	else {
	    if (count == 2) {
		array_r[i_r++] = cp;
	    }
	    count--;
	}

    }


    if (   (i_a == len_a && PREV_RANGE_MATCHES_INVLIST(i_a))
        || (i_b == len_b && PREV_RANGE_MATCHES_INVLIST(i_b)))
    {
	count++;
    }


    if (count < 2) {
        len_r = i_r;
    }
    else {
        IV copy_count = len_a - i_a;
        if (copy_count > 0) {
	    Copy(array_a + i_a, array_r + i_r, copy_count, UV);
        }
        else {
            copy_count = len_b - i_b;
	    Copy(array_b + i_b, array_r + i_r, copy_count, UV);
        }
        len_r = i_r + copy_count;
    }


    if (len_r != _invlist_len(r)) {
	invlist_set_len(r, len_r, *get_invlist_offset_addr(r));
	invlist_trim(r);
	array_r = invlist_array(r);
    }

    if (*i == NULL) {
        *i = r;
    }
    else {


        if (len_r) {
            invlist_replace_list_destroys_src(*i, r);
        }
        else {
            invlist_clear(*i);
        }
        SvREFCNT_dec_NN(r);
    }

    return;
}
