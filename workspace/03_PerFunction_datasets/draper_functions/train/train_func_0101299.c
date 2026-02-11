HtmlStyleCounters(pTree, zName, aValue, nValue)
    HtmlTree *pTree;
    const char *zName;
    int *aValue;
    int nValue;
{
    int ii;
    StyleApply *p = (StyleApply *)(pTree->pStyleApply);

    int n = 0;

    for (ii = 0; ii < p->nCounter && n < nValue; ii++) {
        if (0 == strcmp(zName, p->apCounter[ii]->zName)) {
            aValue[n] = p->apCounter[ii]->iValue;
            n++;
        }
    }

    if (n == 0) {
        n = 1;
        aValue[0] = 0;
    }

    return n;
}
