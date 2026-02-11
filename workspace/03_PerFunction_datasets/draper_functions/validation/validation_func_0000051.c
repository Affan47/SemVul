pixHDome(PIX     *pixs,
         l_int32  height,
         l_int32  connectivity)
{
PIX  *pixsd, *pixd;

    PROCNAME("pixHDome");

    if (!pixs)
        return (PIX *)ERROR_PTR("src pix not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8)
        return (PIX *)ERROR_PTR("pixs not 8 bpp", procName, NULL);
    if (height < 0)
        return (PIX *)ERROR_PTR("height not >= 0", procName, NULL);
    if (height == 0)
        return pixCreateTemplate(pixs);

    if ((pixsd = pixCopy(NULL, pixs)) == NULL)
        return (PIX *)ERROR_PTR("pixsd not made", procName, NULL);
    pixAddConstantGray(pixsd, -height);
    pixSeedfillGray(pixsd, pixs, connectivity);
    pixd = pixSubtractGray(NULL, pixs, pixsd);
    pixDestroy(&pixsd);
    return pixd;
}
