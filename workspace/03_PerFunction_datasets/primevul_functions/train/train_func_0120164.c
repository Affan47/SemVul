ccbaGenerateSinglePath(CCBORDA  *ccba)
{
l_int32   i, j, k, ncc, nb, ncut, npt, dir, len, state, lostholes;
l_int32   x, y, xl, yl, xf, yf;
BOX      *boxinner;
BOXA     *boxa;
CCBORD   *ccb;
PTA      *pta, *ptac, *ptah;
PTA      *ptahc;
PTA      *ptas;
PTA      *ptaf;
PTA      *ptal;
PTA      *ptap, *ptarp;
PTAA     *ptaa;
PTAA     *ptaap;

    PROCNAME("ccbaGenerateSinglePath");

    if (!ccba)
        return ERROR_INT("ccba not defined", procName, 1);

    ncc = ccbaGetCount(ccba);
    lostholes = 0;
    for (i = 0; i < ncc; i++) {
        ccb = ccbaGetCcb(ccba, i);
        if ((ptaa = ccb->local) == NULL) {
            L_WARNING("local pixel loc array not found\n", procName);
            continue;
        }
        nb = ptaaGetCount(ptaa);


        if (ccb->splocal)
            ptaDestroy(&ccb->splocal);
        ptas = ptaCreate(0);
        ccb->splocal = ptas;


        pta = ptaaGetPta(ptaa, 0, L_CLONE);
        if (nb == 1 || nb > NMAX_HOLES + 1) {
            ptaJoin(ptas, pta, 0, -1);
            ptaDestroy(&pta);
            ccbDestroy(&ccb);
            continue;
        }


        boxa = ccb->boxa;
        ptaap = ptaaCreate(nb - 1);
        ptaf = ptaCreate(nb - 1);
        ptal = ptaCreate(nb - 1);
        for (j = 1; j < nb; j++) {
            boxinner = boxaGetBox(boxa, j, L_CLONE);


            ptac = getCutPathForHole(ccb->pix, pta, boxinner, &dir, &len);
            if (len == 0) {
                lostholes++;

            }
            ptaaAddPta(ptaap, ptac, L_INSERT);


            ncut = ptaGetCount(ptac);
            if (ncut == 0) {
                ptaAddPt(ptaf, -1, -1);
                ptaAddPt(ptal, -1, -1);
            } else {
                ptaGetIPt(ptac, 0, &x, &y);
                ptaAddPt(ptaf, x, y);
                ptaGetIPt(ptac, ncut - 1, &x, &y);
                ptaAddPt(ptal, x, y);
            }
            boxDestroy(&boxinner);
        }


        npt = ptaGetCount(pta);
        for (k = 0; k < npt; k++) {
            ptaGetIPt(pta, k, &x, &y);
            if (k == 0) {

                ptaAddPt(ptas, x, y);
                continue;
            }
            state = L_NOT_FOUND;
            for (j = 0; j < nb - 1; j++) {
                ptaGetIPt(ptal, j, &xl, &yl);
                if (x == xl && y == yl) {
                    state = L_FOUND;
                    ptap = ptaaGetPta(ptaap, j, L_CLONE);
                    ptarp = ptaReverse(ptap, 1);

                    ptaGetIPt(ptaf, j, &xf, &yf);

                    ptah = ptaaGetPta(ptaa, j + 1, L_CLONE);
                    ptahc = ptaCyclicPerm(ptah, xf, yf);

                    ptaJoin(ptas, ptarp, 0, -1);
                    ptaJoin(ptas, ptahc, 0, -1);
                    ptaJoin(ptas, ptap, 0, -1);
                    ptaDestroy(&ptap);
                    ptaDestroy(&ptarp);
                    ptaDestroy(&ptah);
                    ptaDestroy(&ptahc);
                    break;
                }
            }
            if (state == L_NOT_FOUND)
                ptaAddPt(ptas, x, y);
        }


        ptaaDestroy(&ptaap);
        ptaDestroy(&ptaf);
        ptaDestroy(&ptal);
        ptaDestroy(&pta);
        ccbDestroy(&ccb);
    }

    if (lostholes > 0)
        L_WARNING("***** %d lost holes *****\n", procName, lostholes);

    return 0;
}
