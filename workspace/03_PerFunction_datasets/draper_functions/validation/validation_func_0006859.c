pixRotateShearIP(PIX       *pixs,
                 l_int32    xcen,
                 l_int32    ycen,
                 l_float32  angle,
                 l_int32    incolor)
{
l_float32  hangle;

    PROCNAME("pixRotateShearIP");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (incolor != L_BRING_IN_WHITE && incolor != L_BRING_IN_BLACK)
        return ERROR_INT("invalid value for incolor", procName, 1);
    if (pixGetColormap(pixs) != NULL)
        return ERROR_INT("pixs is colormapped", procName, 1);

    if (angle == 0.0)
        return 0;
    if (L_ABS(angle) > LIMIT_SHEAR_ANGLE) {
        L_WARNING("%6.2f radians; large angle for in-place 3-shear rotation\n",
                  procName, L_ABS(angle));
    }

    hangle = atan(sin(angle));
    pixHShearIP(pixs, ycen, angle / 2., incolor);
    pixVShearIP(pixs, xcen, hangle, incolor);
    pixHShearIP(pixs, ycen, angle / 2., incolor);
    return 0;
}
