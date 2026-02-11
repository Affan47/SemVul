pixFillPolygon(PIX     *pixs,
               PTA     *pta,
               l_int32  xmin,
               l_int32  ymin)
{
l_int32   w, h, i, n, inside, found;
l_int32  *xstart, *xend;
PIX      *pixi, *pixd;

    PROCNAME("pixFillPolygon");

    if (!pixs || (pixGetDepth(pixs) != 1))
        return (PIX *)ERROR_PTR("pixs undefined or not 1 bpp", procName, NULL);
    if (!pta)
        return (PIX *)ERROR_PTR("pta not defined", procName, NULL);

    pixGetDimensions(pixs, &w, &h, NULL);
    xstart = (l_int32 *)CALLOC(w / 2, sizeof(l_int32));
    xend = (l_int32 *)CALLOC(w / 2, sizeof(l_int32));


    found = FALSE;
    for (i = ymin + 1; i < h; i++) {
        pixFindHorizontalRuns(pixs, i, xstart, xend, &n);
        if (n > 1) {
            ptaPtInsidePolygon(pta, xend[0] + 1, i, &inside);
            if (inside) {
                found = TRUE;
                break;
            }
        }
    }
    if (!found) {
        L_WARNING("nothing found to fill\n", procName);
        FREE(xstart);
        FREE(xend);
        return 0;
    }


    pixd = pixCreateTemplate(pixs);
    pixSetPixel(pixd, xend[0] + 1, i, 1);


    pixi = pixInvert(NULL, pixs);
    pixSeedfillBinary(pixd, pixd, pixi, 4);


    pixOr(pixd, pixd, pixs);

    pixDestroy(&pixi);
    FREE(xstart);
    FREE(xend);
    return pixd;
}
