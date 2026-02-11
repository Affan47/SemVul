get_fit_resid (const MODEL *pmod, const DATASET *dset,
			 int *err)
{
    FITRESID *fr;
    int t, dv = -1;

    if (!special_depvar(pmod)) {
	dv = gretl_model_get_depvar(pmod);
	if (dv < 0 || dv >= dset->v) {
	    *err = E_DATA;
	    return NULL;
	}
    }

    fr = fit_resid_new_for_model(pmod, dset, pmod->t1, pmod->t2,
				 0, err);
    if (*err) {
	return NULL;
    }

    if (LIMDEP(pmod->ci)) {
	fr->sigma = NADBL;
    } else if (pmod->ci == GARCH && (pmod->opt & OPT_Z)) {
	fr->sigma = 1.0;
	fr->std = 1;
    } else {
	fr->sigma = gretl_model_get_double(pmod, "sigma_orig");
	if (na(fr->sigma)) {
	    fr->sigma = pmod->sigma;
	}
    }

    for (t=0; t<fr->nobs; t++) {
	if (dv < 0) {
	    if (na(pmod->yhat[t]) || na(pmod->uhat[t])) {
		fr->actual[t] = NADBL;
	    } else {
		fr->actual[t] = pmod->yhat[t] + pmod->uhat[t];
	    }
	} else {
	    fr->actual[t] = dset->Z[dv][t];
	}
	fr->fitted[t] = pmod->yhat[t];
	fr->resid[t] = pmod->uhat[t];
    }

    if (dv < 0) {
	fr->pmax = PMAX_NOT_AVAILABLE;
    } else {
	fit_resid_set_dec_places(fr);
    }

    if (dv < 0) {
	strcpy(fr->depvar, "implicit y");
    } else {
	strcpy(fr->depvar, dset->varname[dv]);
    }

    return fr;
}
