Perl__invlistEQ(pTHX_ SV* const a, SV* const b, const bool complement_b)
{


    const UV* array_a = invlist_array(a);
    const UV* array_b = invlist_array(b);
    UV len_a = _invlist_len(a);
    UV len_b = _invlist_len(b);

    PERL_ARGS_ASSERT__INVLISTEQ;


    if (complement_b) {


        if (len_b == 0) {
            return (len_a == 1 && array_a[0] == 0);
        }
        else if (array_b[0] == 0) {


            array_b++;
            len_b--;
        }
        else {


            array_b--;
            len_b++;
        }
    }

    return    len_a == len_b
           && memEQ(array_a, array_b, len_a * sizeof(array_a[0]));

}
