SSize_t
Perl__invlist_search(SV* const invlist, const UV cp)
{


    IV low = 0;
    IV mid;
    IV high = _invlist_len(invlist);
    const IV highest_element = high - 1;
    const UV* array;

    PERL_ARGS_ASSERT__INVLIST_SEARCH;


    if (high == 0) {
	return -1;
    }


    array = invlist_array(invlist);

    mid = invlist_previous_index(invlist);
    assert(mid >=0);
    if (mid > highest_element) {
        mid = highest_element;
    }


    if (cp >= array[mid]) {
        if (cp >= array[highest_element]) {
            return highest_element;
        }


        if (cp < array[mid + 1]) {
            return mid;
        }
        high--;
        low = mid + 1;
    }
    else {
        if (cp < array[0]) {
            return -1;
        }
        high = mid;
        if (cp >= array[mid - 1]) {
            goto found_entry;
        }
    }


    while (low < high) {
	mid = (low + high) / 2;
        assert(mid <= highest_element);
	if (array[mid] <= cp) {
	    low = mid + 1;


	}
	else {
	    high = mid;
	}
    }

  found_entry:
    high--;
    invlist_set_previous_index(invlist, high);
    return high;
}
