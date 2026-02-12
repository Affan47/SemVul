pixContrastNorm(PIX       *pixd,
                PIX       *pixs,
                l_int32    sx,
                l_int32    sy,
                l_int32    mindiff,
                l_int32    smoothx,
                l_int32    smoothy)
{
PIX  *pixmin, *pixmax;

    PROCNAME("pixContrastNorm");

    if (!pixs || pixGetDepth(pixs) != 8)
        return (PIX *)ERROR_PTR("pixs undefined or not 8 bpp", procName, pixd);
    if (pixd && pixd != pixs)
        return (PIX *)ERROR_PTR("pixd not null or == pixs", procName, pixd);
    if (pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("pixs is colormapped", procName, pixd);
    if (sx < 5 || sy < 5)
        return (PIX *)ERROR_PTR("sx and/or sy less than 5", procName, pixd);
    if (smoothx < 0 || smoothy < 0)
        return (PIX *)ERROR_PTR("smooth params less than 0", procName, pixd);
    if (smoothx > 8 || smoothy > 8)
        return (PIX *)ERROR_PTR("smooth params exceed 8", procName, pixd);


    pixMinMaxTiles(pixs, sx, sy, mindiff, smoothx, smoothy, &pixmin, &pixmax);


    pixd = pixLinearTRCTiled(pixd, pixs, sx, sy, pixmin, pixmax);

    pixDestroy(&pixmin);
    pixDestroy(&pixmax);
    return pixd;
}
