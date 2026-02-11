pixGetMaxValueInRect(PIX       *pixs,
                     BOX       *box,
                     l_uint32  *pmaxval,
                     l_int32   *pxmax,
                     l_int32   *pymax)
{
l_int32    i, j, w, h, d, wpl, bw, bh;
l_int32    xstart, ystart, xend, yend, xmax, ymax;
l_uint32   val, maxval;
l_uint32  *data, *line;

    PROCNAME("pixGetMaxValueInRect");

    if (pmaxval) *pmaxval = 0;
    if (pxmax) *pxmax = 0;
    if (pymax) *pymax = 0;
    if (!pmaxval && !pxmax && !pymax)
        return ERROR_INT("nothing to do", procName, 1);
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (pixGetColormap(pixs) != NULL)
        return ERROR_INT("pixs has colormap", procName, 1);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8 && d != 32)
        return ERROR_INT("pixs not 8 or 32 bpp", procName, 1);

    xstart = ystart = 0;
    xend = w - 1;
    yend = h - 1;
    if (box) {
        boxGetGeometry(box, &xstart, &ystart, &bw, &bh);
        xend = xstart + bw - 1;
        yend = ystart + bh - 1;
    }

    data = pixGetData(pixs);
    wpl = pixGetWpl(pixs);
    maxval = 0;
    xmax = ymax = 0;
    for (i = ystart; i <= yend; i++) {
        line = data + i * wpl;
        for (j = xstart; j <= xend; j++) {
            if (d == 8)
                val = GET_DATA_BYTE(line, j);
            else
                val = line[j];
            if (val > maxval) {
                maxval = val;
                xmax = j;
                ymax = i;
            }
        }
    }
    if (maxval == 0) {
        xmax = (xstart + xend) / 2;
        ymax = (ystart + yend) / 2;
    }

    if (pmaxval) *pmaxval = maxval;
    if (pxmax) *pxmax = xmax;
    if (pymax) *pymax = ymax;
    return 0;
}
