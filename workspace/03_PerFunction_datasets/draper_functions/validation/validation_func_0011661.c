dsc_parse_viewing_orientation(CDSC *dsc, CDSCCTM **pctm)
{
    CDSCCTM ctm;
    unsigned int i, n;

    if (*pctm != NULL) {
	dsc_memfree(dsc, *pctm);
	*pctm = NULL;
    }

    n = IS_DSC(dsc->line, "%%+") ? 3 : 21;
    while (IS_WHITE(dsc->line[n]))
	n++;

     ctm.xy = ctm.yx = ctm.yy = 0.0;
    ctm.xx = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
    n += i;
    if (i)
        ctm.xy = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
    n += i;
    if (i)
        ctm.yx = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
    n += i;
    if (i)
        ctm.yy = dsc_get_real(dsc->line+n, dsc->line_length-n, &i);
    if (i==0) {
	dsc_unknown(dsc);
    }
    else {
	*pctm = (CDSCCTM *)dsc_memalloc(dsc, sizeof(CDSCCTM));
	if (*pctm == NULL)
	    return CDSC_ERROR;
	**pctm = ctm;
    }
    return CDSC_OK;
}
