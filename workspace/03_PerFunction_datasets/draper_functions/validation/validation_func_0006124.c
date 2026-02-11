ccbCreate(PIX  *pixs)
{
BOXA    *boxa;
CCBORD  *ccb;
PTA     *start;
PTAA    *local;

    PROCNAME("ccbCreate");

    if (pixs) {
        if (pixGetDepth(pixs) != 1)
            return (CCBORD *)ERROR_PTR("pixs not binary", procName, NULL);
    }

    if ((ccb = (CCBORD *)CALLOC(1, sizeof(CCBORD))) == NULL)
        return (CCBORD *)ERROR_PTR("ccb not made", procName, NULL);
    ccb->refcount++;
    if (pixs)
        ccb->pix = pixClone(pixs);
    if ((boxa = boxaCreate(1)) == NULL)
        return (CCBORD *)ERROR_PTR("boxa not made", procName, NULL);
    ccb->boxa = boxa;
    if ((start = ptaCreate(1)) == NULL)
        return (CCBORD *)ERROR_PTR("start pta not made", procName, NULL);
    ccb->start = start;
    if ((local = ptaaCreate(1)) == NULL)
        return (CCBORD *)ERROR_PTR("local ptaa not made", procName, NULL);
    ccb->local = local;

    return ccb;
}
