pixGetBackgroundGrayMap(PIX     *pixs,
                        PIX     *pixim,
                        l_int32  sx,
                        l_int32  sy,
                        l_int32  thresh,
                        l_int32  mincount,
                        PIX    **ppixd)
{
l_int32    w, h, wd, hd, wim, him, wpls, wplim, wpld, wplf;
l_int32    xim, yim, delx, nx, ny, i, j, k, m;
l_int32    count, sum, val8;
l_int32    empty, fgpixels;
l_uint32  *datas, *dataim, *datad, *dataf, *lines, *lineim, *lined, *linef;
l_float32  scalex, scaley;
PIX       *pixd, *piximi, *pixb, *pixf, *pixims;

    PROCNAME("pixGetBackgroundGrayMap");

    if (!ppixd)
        return ERROR_INT("&pixd not defined", procName, 1);
    *ppixd = NULL;
    if (!pixs || pixGetDepth(pixs) != 8)
        return ERROR_INT("pixs not defined or not 8 bpp", procName, 1);
    if (pixGetColormap(pixs))
        return ERROR_INT("pixs is colormapped", procName, 1);
    if (pixim && pixGetDepth(pixim) != 1)
        return ERROR_INT("pixim not 1 bpp", procName, 1);
    if (sx < 4 || sy < 4)
        return ERROR_INT("sx and sy must be >= 4", procName, 1);
    if (mincount > sx * sy) {
        L_WARNING("mincount too large for tile size\n", procName);
        mincount = (sx * sy) / 3;
    }


    fgpixels = 0;
    if (pixim) {
        piximi = pixInvert(NULL, pixim);
        pixZero(piximi, &empty);
        pixDestroy(&piximi);
        if (empty)
            return ERROR_INT("pixim all fg; no background", procName, 1);
        pixZero(pixim, &empty);
        if (!empty)
            fgpixels = 1;
    }


    pixb = pixThresholdToBinary(pixs, thresh);
    pixf = pixMorphSequence(pixb, "d7.1 + d1.7", 0);
    pixDestroy(&pixb);


    w = pixGetWidth(pixs);
    h = pixGetHeight(pixs);
    wd = (w + sx - 1) / sx;
    hd = (h + sy - 1) / sy;
    pixd = pixCreate(wd, hd, 8);


    nx = w / sx;
    ny = h / sy;
    wpls = pixGetWpl(pixs);
    datas = pixGetData(pixs);
    wpld = pixGetWpl(pixd);
    datad = pixGetData(pixd);
    wplf = pixGetWpl(pixf);
    dataf = pixGetData(pixf);
    for (i = 0; i < ny; i++) {
        lines = datas + sy * i * wpls;
        linef = dataf + sy * i * wplf;
        lined = datad + i * wpld;
        for (j = 0; j < nx; j++) {
            delx = j * sx;
            sum = 0;
            count = 0;
            for (k = 0; k < sy; k++) {
                for (m = 0; m < sx; m++) {
                    if (GET_DATA_BIT(linef + k * wplf, delx + m) == 0) {
                        sum += GET_DATA_BYTE(lines + k * wpls, delx + m);
                        count++;
                    }
                }
            }
            if (count >= mincount) {
                val8 = sum / count;
                SET_DATA_BYTE(lined, j, val8);
            }
        }
    }
    pixDestroy(&pixf);


    pixims = NULL;
    if (pixim && fgpixels) {
        wim = pixGetWidth(pixim);
        him = pixGetHeight(pixim);
        dataim = pixGetData(pixim);
        wplim = pixGetWpl(pixim);
        for (i = 0; i < ny; i++) {
            yim = i * sy + sy / 2;
            if (yim >= him)
                break;
            lineim = dataim + yim * wplim;
            for (j = 0; j < nx; j++) {
                xim = j * sx + sx / 2;
                if (xim >= wim)
                    break;
                if (GET_DATA_BIT(lineim, xim))
                    pixSetPixel(pixd, j, i, 0);
            }
        }
    }


    if (pixFillMapHoles(pixd, nx, ny, L_FILL_BLACK)) {
        pixDestroy(&pixd);
        L_WARNING("can't make the map\n", procName);
        return 1;
    }


    if (pixim && fgpixels) {
        scalex = 1. / (l_float32)sx;
        scaley = 1. / (l_float32)sy;
        pixims = pixScaleBySampling(pixim, scalex, scaley);
        pixSmoothConnectedRegions(pixd, pixims, 2);
        pixDestroy(&pixims);
    }

    *ppixd = pixd;
    pixCopyResolution(*ppixd, pixs);
    return 0;
}
