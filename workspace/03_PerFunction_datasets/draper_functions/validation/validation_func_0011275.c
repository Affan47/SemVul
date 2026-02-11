pixContrastTRCMasked(PIX       *pixd,
                     PIX       *pixs,
                     PIX       *pixm,
                     l_float32  factor)
{
l_int32  d;
NUMA    *nac;

    PROCNAME("pixContrastTRCMasked");

    if (!pixm)
        return pixContrastTRC(pixd, pixs, factor);

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("invalid: pixs has a colormap", procName, pixd);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd not null or pixs", procName, pixd);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32)
        return (PIX *)ERROR_PTR("depth not 8 or 32 bpp", procName, pixd);

    if (factor < 0.0) {
        L_WARNING("factor must be >= 0.0; using 0.0", procName);
        factor = 0.0;
    }
    if (factor == 0.0)
        return pixClone(pixs);

    if (!pixd)
        pixd = pixCopy(NULL, pixs);

    if ((nac = numaContrastTRC(factor)) == NULL)
        return (PIX *)ERROR_PTR("nac not made", procName, pixd);
    pixTRCMap(pixd, pixm, nac);
    numaDestroy(&nac);

    return pixd;
}
