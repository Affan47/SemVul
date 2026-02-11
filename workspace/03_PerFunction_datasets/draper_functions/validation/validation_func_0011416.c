processMorphArgs2(PIX   *pixd,
                  PIX   *pixs,
                  SEL   *sel)
{
l_int32  sx, sy;

    PROCNAME("processMorphArgs2");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (!sel)
        return (PIX *)ERROR_PTR("sel not defined", procName, pixd);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pixs not 1 bpp", procName, pixd);

    selGetParameters(sel, &sx, &sy, NULL, NULL);
    if (sx == 0 || sy == 0)
        return (PIX *)ERROR_PTR("sel of size 0", procName, pixd);

    if (!pixd)
        return pixCreateTemplate(pixs);
    pixResizeImageData(pixd, pixs);
    return pixd;
}
