ccbaGenerateStepChains(CCBORDA  *ccba)
{
l_int32  ncc, nb, n, i, j, k;
l_int32  px, py, cx, cy, stepdir;
l_int32  dirtab[][3] = {{1, 2, 3}, {0, -1, 4}, {7, 6, 5}};
CCBORD  *ccb;
NUMA    *na;
NUMAA   *naa;
PTA     *ptal;
PTAA    *ptaal;

    PROCNAME("ccbaGenerateStepChains");

    if (!ccba)
        return ERROR_INT("ccba not defined", procName, 1);

    ncc = ccbaGetCount(ccba);
    for (i = 0; i < ncc; i++) {
        ccb = ccbaGetCcb(ccba, i);


        ptaal = ccb->local;
        nb = ptaaGetCount(ptaal);
        if (ccb->step)
            numaaDestroy(&ccb->step);
        if ((naa = numaaCreate(nb)) == NULL) {
            ccbDestroy(&ccb);
            return ERROR_INT("naa not made", procName, 1);
        }
        ccb->step = naa;


        for (j = 0; j < nb; j++) {
            ptal = ptaaGetPta(ptaal, j, L_CLONE);
            n = ptaGetCount(ptal);
            if (n == 1) {
                na = numaCreate(1);
            } else {
                na = numaCreate(n);
                ptaGetIPt(ptal, 0, &px, &py);
                for (k = 1; k < n; k++) {
                    ptaGetIPt(ptal, k, &cx, &cy);
                    stepdir = dirtab[1 + cy - py][1 + cx - px];
                    numaAddNumber(na, stepdir);
                    px = cx;
                    py = cy;
                }
            }
            numaaAddNuma(naa, na, L_INSERT);
            ptaDestroy(&ptal);
        }
        ccbDestroy(&ccb);
    }

    return 0;
}
