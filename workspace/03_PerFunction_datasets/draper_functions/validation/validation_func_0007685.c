pixacompReplacePix(PIXAC   *pixac,
                   l_int32  index,
                   PIX     *pix,
                   l_int32  comptype)
{
l_int32  n, aindex;
PIXC    *pixc;

    PROCNAME("pixacompReplacePix");

    if (!pixac)
        return ERROR_INT("pixac not defined", procName, 1);
    n = pixacompGetCount(pixac);
    aindex = index - pixac->offset;
    if (aindex < 0 || aindex >= n)
        return ERROR_INT("array index out of bounds", procName, 1);
    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);
    if (comptype != IFF_DEFAULT && comptype != IFF_TIFF_G4 &&
        comptype != IFF_PNG && comptype != IFF_JFIF_JPEG)
        return ERROR_INT("invalid format", procName, 1);

    pixc = pixcompCreateFromPix(pix, comptype);
    pixacompReplacePixcomp(pixac, index, pixc);
    return 0;
}
