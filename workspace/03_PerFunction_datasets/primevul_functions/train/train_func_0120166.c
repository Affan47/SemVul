pixGetCCBorders(PIX      *pixs,
                BOX      *box)
{
l_int32   allzero, i, x, xh, w, nh;
l_int32   xs, ys;
l_uint32  val;
BOX      *boxt, *boxe;
BOXA     *boxa;
CCBORD   *ccb;
PIX      *pixh;
PIX      *pixt;
PIXA     *pixa;

    PROCNAME("pixGetCCBorders");

    if (!pixs)
        return (CCBORD *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!box)
        return (CCBORD *)ERROR_PTR("box not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (CCBORD *)ERROR_PTR("pixs not binary", procName, NULL);

    pixZero(pixs, &allzero);
    if (allzero)
        return (CCBORD *)ERROR_PTR("pixs all 0", procName, NULL);

    if ((ccb = ccbCreate(pixs)) == NULL)
        return (CCBORD *)ERROR_PTR("ccb not made", procName, NULL);


    pixGetOuterBorder(ccb, pixs, box);


    if ((pixh = pixHolesByFilling(pixs, 4)) == NULL) {
        ccbDestroy(&ccb);
        return (CCBORD *)ERROR_PTR("pixh not made", procName, NULL);
    }
    pixZero(pixh, &allzero);
    if (allzero) {
        pixDestroy(&pixh);
        return ccb;
    }


    if ((boxa = pixConnComp(pixh, &pixa, 4)) == NULL) {
        ccbDestroy(&ccb);
        pixDestroy(&pixh);
        return (CCBORD *)ERROR_PTR("boxa not made", procName, NULL);
    }
    nh = boxaGetCount(boxa);


    w = pixGetWidth(pixs);
    for (i = 0; i < nh; i++) {
        boxt = boxaGetBox(boxa, i, L_CLONE);
        pixt = pixaGetPix(pixa, i, L_CLONE);
        ys = boxt->y;
        for (x = 0; x < boxt->w; x++) {
            pixGetPixel(pixt, x, 0, &val);
            if (val == 1) {
                xh = x;
                break;
            }
        }
        if (x == boxt->w) {
            L_WARNING("no hole pixel found!\n", procName);
            continue;
        }
        for (x = xh + boxt->x; x < w; x++) {
            pixGetPixel(pixs, x, ys, &val);
            if (val == 1) {
                xs = x;
                break;
            }
        }
        boxe = boxCreate(boxt->x - 1, boxt->y - 1, boxt->w + 2, boxt->h + 2);
#if  DEBUG_PRINT
        boxPrintStreamInfo(stderr, box);
        boxPrintStreamInfo(stderr, boxe);
        lept_stderr("xs = %d, ys = %d\n", xs, ys);
#endif
        pixGetHoleBorder(ccb, pixs, boxe, xs, ys);
        boxDestroy(&boxt);
        boxDestroy(&boxe);
        pixDestroy(&pixt);
    }

    boxaDestroy(&boxa);
    pixaDestroy(&pixa);
    pixDestroy(&pixh);
    return ccb;
}
