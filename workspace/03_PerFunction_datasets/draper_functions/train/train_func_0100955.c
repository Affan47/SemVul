mprGetListCapacity(MprList *lp)
{
    mprAssert(lp);

    if (lp == 0) {
        return 0;
    }
    return lp->capacity;
}
