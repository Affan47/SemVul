nls_model_fix_sample (MODEL *pmod,
				 nlspec *spec,
				 DATASET *dset)
{
    double *uhat = NULL;
    double *yhat = NULL;

    if (pmod->uhat != NULL) {
	uhat = malloc(dset->n * sizeof *uhat);
	if (uhat == NULL) {
	    return E_ALLOC;
	}
    }

    if (pmod->yhat != NULL) {
	yhat = malloc(dset->n * sizeof *yhat);
	if (yhat == NULL) {
	    free(uhat);
	    return E_ALLOC;
	}
    }

    if (uhat != NULL || yhat != NULL) {
	int t, s = 0;

	for (t=0; t<dset->n; t++) {
	    if (t < spec->real_t1 || t > spec->real_t2 ||
		spec->missmask[t] == '1') {
		if (uhat != NULL) uhat[t] = NADBL;
		if (yhat != NULL) yhat[t] = NADBL;
	    } else {
		if (uhat != NULL) uhat[t] = pmod->uhat[s];
		if (yhat != NULL) yhat[t] = pmod->yhat[s];
		s++;
	    }
	}

	if (uhat != NULL) {
	    free(pmod->uhat);
	    pmod->uhat = uhat;
	}

	if (yhat != NULL) {
	    free(pmod->yhat);
	    pmod->yhat = yhat;
	}
    }

    pmod->full_n = dset->n;
    pmod->t1 = spec->real_t1;
    pmod->t2 = spec->real_t2;

    pmod->missmask = spec->missmask;
    spec->missmask = NULL;

    return 0;
}
