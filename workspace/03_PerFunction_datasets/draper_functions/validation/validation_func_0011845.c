linearInterpolatePixelFloat(l_float32  *datas,
                            l_int32     w,
                            l_int32     h,
                            l_float32   x,
                            l_float32   y,
                            l_float32   inval,
                            l_float32  *pval)
{
l_int32     xpm, ypm, xp, yp, xf, yf;
l_float32   v00, v01, v10, v11;
l_float32  *lines;

    PROCNAME("linearInterpolatePixelFloat");

    if (!pval)
        return ERROR_INT("&val not defined", procName, 1);
    *pval = inval;
    if (!datas)
        return ERROR_INT("datas not defined", procName, 1);


    if (x < 0.0 || y < 0.0 || x > w - 2.0 || y > h - 2.0)
        return 0;

    xpm = (l_int32)(16.0 * x + 0.5);
    ypm = (l_int32)(16.0 * y + 0.5);
    xp = xpm >> 4;
    yp = ypm >> 4;
    xf = xpm & 0x0f;
    yf = ypm & 0x0f;

#if  DEBUG
    if (xf < 0 || yf < 0)
        fprintf(stderr, "xp = %d, yp = %d, xf = %d, yf = %d\n", xp, yp, xf, yf);
#endif


    lines = datas + yp * w;
    v00 = (16.0 - xf) * (16.0 - yf) * (*(lines + xp));
    v10 = xf * (16.0 - yf) * (*(lines + xp + 1));
    v01 = (16.0 - xf) * yf * (*(lines + w + xp));
    v11 = xf * yf * (*(lines + w + xp + 1));
    *pval = (v00 + v01 + v10 + v11) / 256.0;
    return 0;
}
