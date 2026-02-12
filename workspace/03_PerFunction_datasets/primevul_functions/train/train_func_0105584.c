STATIC void
S_populate_ANYOF_from_invlist(pTHX_ regnode *node, SV** invlist_ptr)
{


    dVAR;

    PERL_ARGS_ASSERT_POPULATE_ANYOF_FROM_INVLIST;
    assert(PL_regkind[OP(node)] == ANYOF);


    if (OP(node) == ANYOFH) {
        return;
    }

    ANYOF_BITMAP_ZERO(node);
    if (*invlist_ptr) {


	bool change_invlist = FALSE;

	UV start, end;


	invlist_iterinit(*invlist_ptr);
	while (invlist_iternext(*invlist_ptr, &start, &end)) {
	    UV high;
	    int i;

            if (end == UV_MAX && start <= NUM_ANYOF_CODE_POINTS) {
                ANYOF_FLAGS(node) |= ANYOF_MATCHES_ALL_ABOVE_BITMAP;
            }


	    if (start >= NUM_ANYOF_CODE_POINTS) {
		break;
	    }

	    change_invlist = TRUE;


	    high = (end < NUM_ANYOF_CODE_POINTS - 1)
                   ? end
                   : NUM_ANYOF_CODE_POINTS - 1;
	    for (i = start; i <= (int) high; i++) {
		if (! ANYOF_BITMAP_TEST(node, i)) {
		    ANYOF_BITMAP_SET(node, i);
		}
	    }
	}
	invlist_iterfinish(*invlist_ptr);


	if (change_invlist) {
	    _invlist_subtract(*invlist_ptr, PL_InBitmap, invlist_ptr);
	}
        if (ANYOF_FLAGS(node) & ANYOF_MATCHES_ALL_ABOVE_BITMAP) {
	    _invlist_intersection(*invlist_ptr, PL_InBitmap, invlist_ptr);
	}


	if (_invlist_len(*invlist_ptr) == 0) {
	    SvREFCNT_dec_NN(*invlist_ptr);
	    *invlist_ptr = NULL;
	}
    }
}
