boxaPermutePseudorandom(BOXA  *boxas)
{
l_int32  n;
NUMA    *na;
BOXA    *boxad;

    PROCNAME("boxaPermutePseudorandom");

    if (!boxas)
        return (BOXA *)ERROR_PTR("boxa not defined", procName, NULL);

    n = boxaGetCount(boxas);
    na = numaPseudorandomSequence(n, 0);
    boxad = boxaSortByIndex(boxas, na);
    numaDestroy(&na);
    return boxad;
}
