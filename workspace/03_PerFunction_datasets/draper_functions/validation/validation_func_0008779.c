objsetign(mcmcxdef *mctx, objnum objn)
{
    objdef *objptr;
    prpdef *mut;
    prpdef *p;
    int     statcnt;
    int     cnt;
    int     indexed;
    prpdef *p1;

    objptr = (objdef *)mcmlck(mctx, (mcmon)objn);
    p1 = objprp(objptr);
    indexed = objflg(objptr) & OBJFINDEX;


    for (mut = (prpdef *)(objptr + objrst(objptr)),
         cnt = objnprop(objptr) - objstat(objptr) ; cnt ;
         mut = objpnxt(mut), --cnt)
    {
        for (p = p1, statcnt = objstat(objptr) ; statcnt ;
             p = objpnxt(p), --statcnt)
        {

            if (prpprop(p) == prpprop(mut))
            {
                prpflg(p) |= PRPFIGN;
                break;
            }
        }
    }

    mcmtch(mctx, (mcmon)objn);
    mcmunlck(mctx, (mcmon)objn);
    if (indexed) objindx(mctx, objn);
}
