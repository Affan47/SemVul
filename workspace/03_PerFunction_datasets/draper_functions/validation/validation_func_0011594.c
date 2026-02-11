fit_resid_head (const FITRESID *fr,
			    const DATASET *dset,
			    int obslen, PRN *prn)
{
    char label[16];
    char obs1[OBSLEN], obs2[OBSLEN];
    int kstep = fr->method == FC_KSTEP;
    int i;

    if (kstep) {
	ntodate(obs1, fr->model_t1, dset);
	pprintf(prn, _("Recursive %d-step ahead forecasts"), fr->k);
	pputs(prn, "\n\n");
	pprintf(prn, _("The forecast for time t is based on (a) coefficients obtained by\n"
		       "estimating the model over the sample %s to t-%d, and (b) the\n"
		       "regressors evaluated at time t."), obs1, fr->k);
	pputs(prn, "\n\n");
	pputs(prn, _("This is truly a forecast only if all the stochastic regressors\n"
		     "are in fact lagged values."));
	pputs(prn, "\n\n");
    } else {
	ntodate(obs1, fr->t1, dset);
	ntodate(obs2, fr->t2, dset);
	pprintf(prn, _("Model estimation range: %s - %s"), obs1, obs2);
	pputc(prn, '\n');

	if (fr->std) {
	    pprintf(prn, "%s\n", _("The residuals are standardized"));
	} else if (!na(fr->sigma)) {
	    pprintf(prn, "%s = %.*g\n", _("Standard error of the regression"),
		    GRETL_DIGITS, fr->sigma);
	}
    }

    pputc(prn, '\n');
    bufspace(obslen, prn);

    for (i=1; i<4; i++) {
	if (i == 1) strcpy(label, fr->depvar);
	if (i == 2) strcpy(label, (kstep)? _("forecast") : _("fitted"));
	if (i == 3) strcpy(label, (kstep)? _("error") : _("residual"));
	pprintf(prn, "%*s", UTF_WIDTH(label, 13), label);
    }

    pputs(prn, "\n\n");
}
