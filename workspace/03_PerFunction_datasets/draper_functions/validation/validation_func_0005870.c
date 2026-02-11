do_single_equation_test (ExecState *state,
				    gretl_restriction *rset,
				    const DATASET *dset,
				    PRN *prn)
{
    int err = 0;

    if (rset->rows != NULL) {
	err = restriction_set_make_mask(rset);
	if (err) {
	    return err;
	}
    }

    if (rset->opt & OPT_B) {

	MODEL *pmod = rset->obj;

	err = check_bootstrap(pmod, prn);
	if (err) {
	    return err;
	}

	if (is_simple_zero_restriction(rset)) {
	    err = bootstrap_zero_restriction(rset, pmod, dset, prn);
	} else {
	    err = test_restriction_set(rset, prn);
	    if (!err && rset->R->cols != pmod->ncoeff) {
		err = rset_expand_R(rset, pmod->ncoeff);
	    }
	    if (!err) {
		rset->test /= rset->g;
		err = bootstrap_test_restriction(pmod, rset->R, rset->q,
						 rset->test, rset->g,
						 dset, rset->opt, prn);
	    }
	}
    } else {
	err = test_restriction_set(rset, prn);
	if (!err) {
	    print_or_save_result(state, rset, dset, prn);
	}
    }

    return err;
}
