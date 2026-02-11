vecm_restriction_check (gretl_restriction *rset)
{
    int r = gretl_VECM_rank(rset->obj);
    int err;

    err = vecm_ab_check(rset);

    if (!err && (rset->vecm & VECM_B)) {
	err = vecm_x_check(rset, 'b');
    }

    if (!err && (rset->vecm & VECM_A)) {
	err = vecm_x_check(rset, 'a');
    }

    if (!err && (rset->vecm & VECM_B)) {
	rset->bcols = gretl_VECM_n_beta(rset->obj);
	if (rset->bmulti) {
	    rset->bcols *= r;
	}
    }

    if (!err && (rset->vecm & VECM_A)) {
	rset->acols = gretl_VECM_n_alpha(rset->obj);
	if (rset->amulti) {
	    rset->acols *= r;
	}
    }

    if (!err) {
	if (rset->gb > rset->bcols) {
	    gretl_errmsg_set("Too many restrictions");
	    err = E_NONCONF;
	} else if (rset->ga > rset->acols) {
	    fprintf(stderr, "rset->ga = %d, rset->acols = %d\n",
		    rset->ga, rset->acols);
	    gretl_errmsg_set("Too many restrictions");
	    err = E_NONCONF;
	}
    }

    return err;
}
