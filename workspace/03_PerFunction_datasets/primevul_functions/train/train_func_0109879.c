pixThresholdSpreadNorm(PIX       *pixs,
                       l_int32    filtertype,
                       l_int32    edgethresh,
                       l_int32    smoothx,
                       l_int32    smoothy,
                       l_float32  gamma,
                       l_int32    minval,
                       l_int32    maxval,
                       l_int32    targetthresh,
                       PIX      **ppixth,
                       PIX      **ppixb,
                       PIX      **ppixd)
{
PIX  *pixe, *pixet, *pixsd, *pixg1, *pixg2, *pixth;

    PROCNAME("pixThresholdSpreadNorm");

    if (ppixth) *ppixth = NULL;
    if (ppixb) *ppixb = NULL;
    if (ppixd) *ppixd = NULL;
    if (!pixs || pixGetDepth(pixs) != 8)
        return ERROR_INT("pixs not defined or not 8 bpp", procName, 1);
    if (pixGetColormap(pixs))
        return ERROR_INT("pixs is colormapped", procName, 1);
    if (!ppixth && !ppixb && !ppixd)
        return ERROR_INT("no output requested", procName, 1);
    if (filtertype != L_SOBEL_EDGE && filtertype != L_TWO_SIDED_EDGE)
        return ERROR_INT("invalid filter type", procName, 1);


    if (filtertype == L_SOBEL_EDGE)
        pixe = pixSobelEdgeFilter(pixs, L_VERTICAL_EDGES);
    else
        pixe = pixTwoSidedEdgeFilter(pixs, L_VERTICAL_EDGES);
    pixet = pixThresholdToBinary(pixe, edgethresh);
    pixInvert(pixet, pixet);


    pixsd = pixCreateTemplate(pixs);
    pixCombineMasked(pixsd, pixs, pixet);


    pixg1 = pixSeedspread(pixsd, 4);
    pixg2 = pixBlockconv(pixg1, smoothx, smoothy);


    pixth = pixGammaTRC(NULL, pixg2, gamma, minval, maxval);


    if (ppixd) {
        *ppixd = pixApplyVariableGrayMap(pixs, pixth, targetthresh);
        if (ppixb)
            *ppixb = pixThresholdToBinary(*ppixd, targetthresh);
    }
    else if (ppixb)
        *ppixb = pixVarThresholdToBinary(pixs, pixth);

    if (ppixth)
        *ppixth = pixth;
    else
        pixDestroy(&pixth);

    pixDestroy(&pixe);
    pixDestroy(&pixet);
    pixDestroy(&pixsd);
    pixDestroy(&pixg1);
    pixDestroy(&pixg2);
    return 0;
}
