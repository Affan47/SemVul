ccbaDisplayImage2(CCBORDA  *ccba)
{
l_int32  ncc, nb, n, i, j, k, x, y, xul, yul, w, h;
l_int32  fpx, fpy, spx, spy, xs, ys;
BOXA    *boxa;
CCBORD  *ccb;
PIX     *pixd, *pixc, *pixs;
PTAA    *ptaa;
PTA     *pta;

    PROCNAME("ccbaDisplayImage2");

    if (!ccba)
        return (PIX *)ERROR_PTR("ccba not defined", procName, NULL);

    if ((pixd = pixCreate(ccba->w, ccba->h, 1)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    ncc = ccbaGetCount(ccba);
    for (i = 0; i < ncc; i++) {


        ccb = ccbaGetCcb(ccba, i);
        if ((boxa = ccb->boxa) == NULL) {
            pixDestroy(&pixd);
            ccbDestroy(&ccb);
            return (PIX *)ERROR_PTR("boxa not found", procName, NULL);
        }
        if (boxaGetBoxGeometry(boxa, 0, &xul, &yul, &w, &h)) {
            pixDestroy(&pixd);
            ccbDestroy(&ccb);
            return (PIX *)ERROR_PTR("b. box not found", procName, NULL);
        }
        pixc = pixCreate(w + 2, h + 2, 1);
        pixs = pixCreateTemplate(pixc);

        if ((ptaa = ccb->local) == NULL) {
            pixDestroy(&pixc);
            pixDestroy(&pixs);
            ccbDestroy(&ccb);
            L_WARNING("local chain array not found\n", procName);
            continue;
        }
        nb = ptaaGetCount(ptaa);
        for (j = 0; j < nb; j++) {
            pta = ptaaGetPta(ptaa, j, L_CLONE);
            n = ptaGetCount(pta);


            for (k = 0; k < n; k++) {
                ptaGetIPt(pta, k, &x, &y);
                pixSetPixel(pixc, x + 1, y + 1, 1);
                if (k == 0) {
                    fpx = x + 1;
                    fpy = y + 1;
                } else if (k == 1) {
                    spx = x + 1;
                    spy = y + 1;
                }
            }


            if (n > 1)
                locateOutsideSeedPixel(fpx, fpy, spx, spy, &xs, &ys);
            else
                xs = ys = 0;
            pixSetPixel(pixs, xs, ys, 1);
            ptaDestroy(&pta);
        }


        pixInvert(pixc, pixc);
        pixSeedfillBinary(pixs, pixs, pixc, 4);
        pixInvert(pixs, pixs);


        pixRasterop(pixd, xul, yul, w, h, PIX_XOR, pixs, 1, 1);

        pixDestroy(&pixc);
        pixDestroy(&pixs);
        ccbDestroy(&ccb);
    }
    return pixd;
}
