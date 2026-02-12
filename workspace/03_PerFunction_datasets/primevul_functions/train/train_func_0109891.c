pixFillMapHoles(PIX     *pix,
                l_int32  nx,
                l_int32  ny,
                l_int32  filltype)
{
l_int32   w, h, y, nmiss, goodcol, i, j, found, ival, valtest;
l_uint32  val, lastval;
NUMA     *na;

    PROCNAME("pixFillMapHoles");

    if (!pix || pixGetDepth(pix) != 8)
        return ERROR_INT("pix not defined or not 8 bpp", procName, 1);
    if (pixGetColormap(pix))
        return ERROR_INT("pix is colormapped", procName, 1);


    pixGetDimensions(pix, &w, &h, NULL);
    na = numaCreate(0);
    nmiss = 0;
    valtest = (filltype == L_FILL_WHITE) ? 255 : 0;
    for (j = 0; j < nx; j++) {
        found = FALSE;
        for (i = 0; i < ny; i++) {
            pixGetPixel(pix, j, i, &val);
            if (val != valtest) {
                y = i;
                found = TRUE;
                break;
            }
        }
        if (found == FALSE) {
            numaAddNumber(na, 0);
            nmiss++;
        }
        else {
            numaAddNumber(na, 1);
            for (i = y - 1; i >= 0; i--)
                pixSetPixel(pix, j, i, val);
            pixGetPixel(pix, j, 0, &lastval);
            for (i = 1; i < h; i++) {
                pixGetPixel(pix, j, i, &val);
                if (val == valtest)
                    pixSetPixel(pix, j, i, lastval);
                else
                    lastval = val;
            }
        }
    }
    numaAddNumber(na, 0);

    if (nmiss == nx) {
        numaDestroy(&na);
        L_WARNING("no bg found; no data in any column\n", procName);
        return 1;
    }


    if (nmiss > 0) {

        goodcol = 0;
        for (j = 0; j < w; j++) {
            numaGetIValue(na, j, &ival);
            if (ival == 1) {
                goodcol = j;
                break;
            }
        }
        if (goodcol > 0) {
            for (j = goodcol - 1; j >= 0; j--)
                pixRasterop(pix, j, 0, 1, h, PIX_SRC, pix, j + 1, 0);
        }
        for (j = goodcol + 1; j < w; j++) {
            numaGetIValue(na, j, &ival);
            if (ival == 0) {

                pixRasterop(pix, j, 0, 1, h, PIX_SRC, pix, j - 1, 0);
            }
        }
    }
    if (w > nx) {
        for (i = 0; i < h; i++) {
            pixGetPixel(pix, w - 2, i, &val);
            pixSetPixel(pix, w - 1, i, val);
        }
    }

    numaDestroy(&na);
    return 0;
}
