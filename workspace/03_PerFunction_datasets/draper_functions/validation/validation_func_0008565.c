pixAddBlackBorder(PIX      *pixs,
                  l_int32   npix)
{
l_int32   d, val;
PIXCMAP  *cmap;

    PROCNAME("pixAddBlackBorder");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (npix == 0)
        return pixClone(pixs);

    if ((cmap = pixGetColormap(pixs)) != NULL)
        pixcmapGetRankIntensity(cmap, 0.0, &val);
    else {
        d = pixGetDepth(pixs);
        val = (d == 1) ? 1 : 0;
    }
    return pixAddBorderGeneral(pixs, npix, npix, npix, npix, val);
}
