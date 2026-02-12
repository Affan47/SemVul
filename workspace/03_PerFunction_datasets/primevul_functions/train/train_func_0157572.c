Perl__invlist_populate_swatch(SV* const invlist,
                              const UV start, const UV end, U8* swatch)
{


    UV current = start;
    const IV len = _invlist_len(invlist);
    IV i;
    const UV * array;

    PERL_ARGS_ASSERT__INVLIST_POPULATE_SWATCH;

    if (len == 0) {
        return;
    }

    array = invlist_array(invlist);


    i = _invlist_search(invlist, start);


    while (current < end) {
        UV upper;


        if (i == -1 || ! ELEMENT_RANGE_MATCHES_INVLIST(i)) {
            i++;
            if (i >= len) {
                return;
            }
            current = array[i];
	    if (current >= end) {

                if (LIKELY(end < UV_MAX)) {
                    return;
                }


                i = len;
                goto join_end_of_list;
            }
        }
        assert(current >= start);


        i++;
        upper = (i < len && array[i] < end) ? array[i] : end;


        for (; current < upper; current++) {
            const STRLEN offset = (STRLEN)(current - start);
            swatch[offset >> 3] |= 1 << (offset & 7);
        }

      join_end_of_list:


        if (i >= len) {


            if (UNLIKELY(end == UV_MAX && ELEMENT_RANGE_MATCHES_INVLIST(len-1)))
	    {
                const STRLEN offset = (STRLEN)(end - start);
                swatch[offset >> 3] |= 1 << (offset & 7);
            }
            return;
        }


        current = array[i];
    }

    return;
}
