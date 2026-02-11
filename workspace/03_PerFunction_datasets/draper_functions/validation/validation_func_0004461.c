check_add_transform (int ci, int lag, int vnum, const double *x,
		     const char *vname, const char *label,
		     DATASET *dset, int origv)
{
    int t, ret = VAR_ADDED_OK;

    if (vnum < dset->v) {

	int chk = check_vals(x, dset->Z[vnum], dset->n);


	if (chk == VARS_IDENTICAL) {
	    ret = VAR_EXISTS_OK;
	} else if (chk == X_HAS_MISSING) {

	    ret = VAR_EXISTS_OK;
	} else if (chk == Y_HAS_MISSING) {
	    for (t=0; t<dset->n; t++) {
		dset->Z[vnum][t] = x[t];
	    }
	    ret = VAR_EXISTS_OK;
	} else {
	    ret = transform_handle_duplicate(ci, lag, vnum, x, label, dset,
					     origv);
	}
    } else {

	if (dataset_add_series(dset, 1)) {
	    ret = VAR_ADD_FAILED;
	} else {
	    strcpy(dset->varname[vnum], vname);
	    series_set_label(dset, vnum, label);
	    for (t=0; t<dset->n; t++) {
		dset->Z[vnum][t] = x[t];
	    }
	}
    }

    return ret;
}
