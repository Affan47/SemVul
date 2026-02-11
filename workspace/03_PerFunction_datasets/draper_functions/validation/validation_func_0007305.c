pixSeedfillMorph(PIX     *pixs,
                 PIX     *pixm,
                 l_int32  connectivity)
{
l_int32  same, iter;
PIX     *pixt1, *pixd, *temp;
SEL     *sel_3;

    PROCNAME("pixSeedfillMorph");

    if (!pixs)
        return (PIX *)ERROR_PTR("seed pix not defined", procName, NULL);
    if (!pixm)
        return (PIX *)ERROR_PTR("mask pix not defined", procName, NULL);
    if (connectivity != 4 && connectivity != 8)
        return (PIX *)ERROR_PTR("connectivity not in {4,8}", procName, NULL);

    if (pixSizesEqual(pixs, pixm) == 0)
        return (PIX *)ERROR_PTR("pix sizes unequal", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pix not binary", procName, NULL);

    if ((sel_3 = selCreateBrick(3, 3, 1, 1, 1)) == NULL)
        return (PIX *)ERROR_PTR("sel_3 not made", procName, NULL);
    if (connectivity == 4) {
        selSetElement(sel_3, 0, 0, SEL_DONT_CARE);
        selSetElement(sel_3, 2, 2, SEL_DONT_CARE);
        selSetElement(sel_3, 2, 0, SEL_DONT_CARE);
        selSetElement(sel_3, 0, 2, SEL_DONT_CARE);
    }

    if ((pixt1 = pixCopy(NULL, pixs)) == NULL)
        return (PIX *)ERROR_PTR("pixt1 not made", procName, NULL);
    if ((pixd = pixCreateTemplate(pixs)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);

    iter = 0;
    while (1) {
        iter++;
        pixDilate(pixd, pixt1, sel_3);
        pixAnd(pixd, pixd, pixm);
        pixEqual(pixd, pixt1, &same);
        if (same)
            break;
        else
            SWAP(pixt1, pixd);
    }
    fprintf(stderr, " Num iters in binary reconstruction = %d\n", iter);

    pixDestroy(&pixt1);
    selDestroy(&sel_3);

    return pixd;
}
