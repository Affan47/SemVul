bmfGetWidth(BMF     *bmf,
            char     chr,
            l_int32  *pw)
{
l_int32  i;
PIX     *pix;
PIXA    *pixa;

    PROCNAME("bmfGetWidth");

    if (!bmf)
        return ERROR_INT("bmf not defined", procName, 1);
    if (!pw)
        return ERROR_INT("&w not defined", procName, 1);
    *pw = -1;
    i = bmf->fonttab[(l_int32)chr];
    if (i == UNDEF)
        return ERROR_INT("no bitmap representation", procName, 1);
    if ((pixa = bmf->pixa) == NULL)
        return ERROR_INT("pixa not found", procName, 1);
    if ((pix = pixaGetPix(pixa, i, L_CLONE)) == NULL)
        return ERROR_INT("pix not found", procName, 1);
    *pw = pixGetWidth(pix);
    pixDestroy(&pix);

    return 0;
}
