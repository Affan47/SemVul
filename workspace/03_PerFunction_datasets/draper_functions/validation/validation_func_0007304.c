c_plscmap1n(PLINT ncol1)
{
    int ncol, size;


    if (ncol1 > 0 && plsc->ncol1 == ncol1)
	return;


    if (plsc->ncol1 <= 0 && ncol1 <= 0)
	ncol = 128;
    else if (ncol1 <= 0)
	ncol = plsc->ncol1;
    else
        ncol = ncol1;

    size = ncol * sizeof(PLColor);


    if (plsc->ncol1 > 0)
	plsc->cmap1 = (PLColor *) realloc(plsc->cmap1, size);
    else
	plsc->cmap1 = (PLColor *) calloc(ncol, sizeof(PLColor));


    plsc->ncol1 = ncol;
    if (plsc->ncp1 == 0)
	plcmap1_def();
    else
	plcmap1_calc();
}
