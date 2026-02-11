mprCreateList(int size, int flags)
{
    MprList     *lp;

    if ((lp = mprAllocObj(MprList, manageList)) == 0) {
        return 0;
    }
    lp->maxSize = MAXINT;
    lp->flags = flags;
    lp->mutex = mprCreateLock();
    if (size != 0) {
        mprSetListLimits(lp, size, -1);
    }
    return lp;
}
