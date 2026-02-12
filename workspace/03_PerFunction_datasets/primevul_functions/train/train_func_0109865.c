pixGetForegroundGrayMap(PIX     *pixs,
                        PIX     *pixim,
                        l_int32  sx,
                        l_int32  sy,
                        l_int32  thresh,
                        PIX    **ppixd)
{
l_int32  w, h, d, wd, hd;
l_int32  empty, fgpixels;
PIX     *pixd, *piximi, *pixim2, *pixims, *pixs2, *pixb, *pixt1, *pixt2, *pixt3;

    PROCNAME("pixGetForegroundGrayMap");

    if (!ppixd)
        return ERROR_INT("&pixd not defined", procName, 1);
    *ppixd = NULL;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8)
        return ERROR_INT("pixs not 8 bpp", procName, 1);
    if (pixim && pixGetDepth(pixim) != 1)
        return ERROR_INT("pixim not 1 bpp", procName, 1);
    if (sx < 2 || sy < 2)
        return ERROR_INT("sx and sy must be >= 2", procName, 1);


    wd = (w + sx - 1) / sx;
    hd = (h + sy - 1) / sy;
    pixd = pixCreate(wd, hd, 8);
    *ppixd = pixd;


    fgpixels = 0;
    if (pixim) {
        piximi = pixInvert(NULL, pixim);
        pixZero(piximi, &empty);
        pixDestroy(&piximi);
        if (empty)
            return 0;
        pixZero(pixim, &empty);
        if (!empty)
            fgpixels = 1;
    }


    pixs2 = pixScaleBySampling(pixs, 0.5, 0.5);
    if (pixim && fgpixels) {
        pixim2 = pixReduceBinary2(pixim, NULL);
        pixPaintThroughMask(pixs2, pixim2, 0, 0, 255);
        pixDestroy(&pixim2);
    }


    pixt1 = pixScaleGrayMinMax(pixs2, sx, sy, L_CHOOSE_MIN);


    pixb = pixThresholdToBinary(pixt1, thresh);
    pixInvert(pixb, pixb);
    pixPaintThroughMask(pixt1, pixb, 0, 0, 255);
    pixDestroy(&pixb);


    pixt2 = pixExpandReplicate(pixt1, 2);


    pixFillMapHoles(pixt2, w / sx, h / sy, L_FILL_WHITE);


    pixt3 = pixBlockconv(pixt2, 8, 8);
    pixRasterop(pixd, 0, 0, wd, hd, PIX_SRC, pixt3, 0, 0);


    pixims = pixScaleBySampling(pixim, 1. / sx, 1. / sy);
    pixPaintThroughMask(pixd, pixims, 0, 0, 0);

    pixDestroy(&pixs2);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixDestroy(&pixt3);
    return 0;
}
