ccbaDisplayImage1(CCBORDA  *ccba)
{
l_int32  ncc, i, nb, n, j, k, x, y, xul, yul, xoff, yoff, w, h;
l_int32  fpx, fpy, spx, spy, xs, ys;
BOX     *box;
BOXA    *boxa;
CCBORD  *ccb;
PIX     *pixd, *pixt, *pixh;
PTAA    *ptaa;
PTA     *pta;

    PROCNAME("ccbaDisplayImage1");

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


        if ((ptaa = ccb->local) == NULL) {
            L_WARNING("local chain array not found\n", procName);
            ccbDestroy(&ccb);
            continue;
        }

        nb = ptaaGetCount(ptaa);
        for (j = 0; j < nb; j++) {
            if ((box = boxaGetBox(boxa, j, L_CLONE)) == NULL) {
                pixDestroy(&pixd);
                ccbDestroy(&ccb);
                return (PIX *)ERROR_PTR("b. box not found", procName, NULL);
            }
            if (j == 0) {
                boxGetGeometry(box, &xul, &yul, &w, &h);
                xoff = yoff = 0;
            } else {
                boxGetGeometry(box, &xoff, &yoff, &w, &h);
            }
            boxDestroy(&box);


            if ((pixt = pixCreate(w, h, 1)) == NULL) {
                pixDestroy(&pixd);
                ccbDestroy(&ccb);
                return (PIX *)ERROR_PTR("pixt not made", procName, NULL);
            }
            pta = ptaaGetPta(ptaa, j, L_CLONE);
            n = ptaGetCount(pta);
            for (k = 0; k < n; k++) {
                ptaGetIPt(pta, k, &x, &y);
                pixSetPixel(pixt, x - xoff, y - yoff, 1);
                if (j > 0) {
                    if (k == 0) {
                        fpx = x - xoff;
                        fpy = y - yoff;
                    }
                    if (k == 1) {
                        spx = x - xoff;
                        spy = y - yoff;
                    }
                }
            }
            ptaDestroy(&pta);


            if (j == 0) {
                if ((pixh = pixFillClosedBorders(pixt, 4)) == NULL) {
                    pixDestroy(&pixd);
                    pixDestroy(&pixt);
                    ccbDestroy(&ccb);
                    return (PIX *)ERROR_PTR("pixh not made", procName, NULL);
                }
            } else {

                locateOutsideSeedPixel(fpx, fpy, spx, spy, &xs, &ys);


                pixh = pixCreateTemplate(pixt);
                pixSetPixel(pixh, xs, ys, 1);
                pixInvert(pixt, pixt);
                pixSeedfillBinary(pixh, pixh, pixt, 4);
            }


            pixRasterop(pixd, xul + xoff, yul + yoff, w, h, PIX_XOR,
                        pixh, 0, 0);
            pixDestroy(&pixt);
            pixDestroy(&pixh);
        }
        ccbDestroy(&ccb);
    }
    return pixd;
}
