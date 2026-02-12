pixOctreeColorQuantGeneral(PIX       *pixs,
                           l_int32    colors,
                           l_int32    ditherflag,
                           l_float32  validthresh,
                           l_float32  colorthresh)
{
l_int32    w, h, minside, factor, index, rval, gval, bval;
l_float32  scalefactor;
l_float32  pixfract;
l_float32  colorfract;
CQCELL  ***cqcaa;
PIX       *pixd, *pixsub;
PIXCMAP   *cmap;

    PROCNAME("pixOctreeColorQuantGeneral");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs not 32 bpp", procName, NULL);
    if (colors < 128 || colors > 240)
        return (PIX *)ERROR_PTR("colors must be in [128, 240]", procName, NULL);


    pixGetDimensions(pixs, &w, &h, NULL);
    if (validthresh > 0.0 && colorthresh > 0.0) {
        minside = L_MIN(w, h);
        factor = L_MAX(1, minside / 400);
        pixColorFraction(pixs, 20, 244, 20, factor, &pixfract, &colorfract);
        if (pixfract * colorfract < validthresh * colorthresh) {
            L_INFO("\n  Pixel fraction neither white nor black = %6.3f"
                   "\n  Color fraction of those pixels = %6.3f"
                   "\n  Quantizing to 8 bpp gray\n",
                   procName, pixfract, colorfract);
            return pixConvertTo8(pixs, 1);
        }
    } else {
        L_INFO("\n  Process in color by default\n", procName);
    }


    if (w > TreeGenWidth) {
        scalefactor = (l_float32)TreeGenWidth / (l_float32)w;
        pixsub = pixScaleBySampling(pixs, scalefactor, scalefactor);
    } else {
        pixsub = pixClone(pixs);
    }


    if (w < MinDitherSize && h < MinDitherSize)
        colors = L_MIN(colors, 220);


    cqcaa = octreeGenerateAndPrune(pixsub, colors, CqReservedColors, &cmap);
    if (!cqcaa) {
        pixDestroy(&pixsub);
        return (PIX *)ERROR_PTR("tree not made", procName, NULL);
    }
#if DEBUG_COLORQUANT
    L_INFO(" Colors requested = %d\n", procName, colors);
    L_INFO(" Actual colors = %d\n", procName, cmap->n);
#endif


    if (w < MinDitherSize && h < MinDitherSize && ditherflag == 1) {
        L_INFO("Small image: dithering turned off\n", procName);
        ditherflag = 0;
    }


    if ((pixd = pixOctreeQuantizePixels(pixs, cqcaa, ditherflag)) == NULL) {
        pixDestroy(&pixsub);
        cqcellTreeDestroy(&cqcaa);
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    }


    pixSetColormap(pixd, cmap);
    pixCopyResolution(pixd, pixs);
    pixCopyInputFormat(pixd, pixs);


    pixcmapGetRankIntensity(cmap, 0.0, &index);
    pixcmapGetColor(cmap, index, &rval, &gval, &bval);
    if (rval < 5 && gval < 5 && bval < 5)
        pixcmapResetColor(cmap, index, 0, 0, 0);


    pixcmapGetRankIntensity(cmap, 1.0, &index);
    pixcmapGetColor(cmap, index, &rval, &gval, &bval);
    if (rval > 251 && gval > 251 && bval > 251)
        pixcmapResetColor(cmap, index, 255, 255, 255);

    cqcellTreeDestroy(&cqcaa);
    pixDestroy(&pixsub);
    return pixd;
}
